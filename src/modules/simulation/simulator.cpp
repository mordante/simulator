/*
 * Copyright (C) 2013 - 2014 by Mark de Wever <koraq@xs4all.nl>
 * Part of the simulator project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 *
 * See the COPYING file for more details.
 */

#include "modules/simulation/simulator.hpp"

#include "lib/exception/throw.tpp"
#include "lib/exception/validate.tpp"
#include "modules/logger/logger.hpp"
#include "modules/unit/quantity/comparison.tpp"
#include "modules/unit/quantity/stream.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

REGISTER_LOGGER_MODULE("/modules/simulator")

namespace simulation
{

tsimulator::tsimulator(celestial::tuniverse&& universe__)
	: universe_{std::move(universe__)}
{
	TRACE;
}

tsimulator::tsimulator(const boost::property_tree::ptree& simulator)
	: universe_{celestial::tuniverse::load(simulator.get_child("universe"))}
	, collided_{simulator.get<bool>("collided")}
{
	TRACE;

	boost::property_tree::ptree states{simulator.get_child("states")};
	for(const auto& state : states) {
		detail::tstate s{detail::tstate::load(state.second)};
		if(s.time.value != static_cast<int>(states_.size())) {
			THROW_F(invalid_value,
					"The time »",
					s.time.value,
					"« of the state does not have the expected value of »",
					states_.size(),
					"«.");
		}
		states_.push_back(std::move(s));
	}
}

tsimulator tsimulator::load(const boost::property_tree::ptree& simulator)
{
	TRACE;

	switch(const int version{simulator.get<int>("version")}) {
		case 1:
			return tsimulator(simulator);

		default:
			THROW_F(load_invalid_version,
					"Failed to load a simulator object, version »",
					version,
					"« is not supported.");
	}
}

tsimulator tsimulator::load(const std::string& filename)
{
	TRACE_PARAMETERS(filename);

	boost::property_tree::ptree xml;
	boost::property_tree::read_xml(filename, xml);

	return load(xml.get_child("simulation"));
}

boost::property_tree::ptree tsimulator::store() const
{
	TRACE;

	boost::property_tree::ptree result;

	result.put("version", 1);
	result.push_back(boost::property_tree::ptree::value_type{
			"universe", universe_.store()});

	result.put("collided", collided_);
	boost::property_tree::ptree states;
	for(const auto& state : states_) {
		states.push_back(boost::property_tree::ptree::value_type{
				"state", state.store()});
	}
	result.push_back(boost::property_tree::ptree::value_type{"states", states});

	return result;
}

void tsimulator::store(const std::string& filename) const
{
	TRACE_PARAMETERS(filename);

	boost::property_tree::ptree xml;
	boost::property_tree::xml_writer_settings<char> settings{' ', 4};

	xml.push_back(
			boost::property_tree::ptree::value_type{"simulation", store()});

	boost::property_tree::write_xml(filename, xml, std::locale(), settings);
}

void tsimulator::run(const unit::ttime seconds)
{
	TRACE_PARAMETERS(seconds);

	if(collided_) {
		throw tcollision{};
	}

	if(states_.empty()) {
		update_positions();
	}

	for(unit::ttime i{0_s}; i < seconds; ++i) {
		update_positions();
	}
}

void tsimulator::update_positions()
{
	TRACE;

	/* Create a new state. */
	detail::tstate state{
			unit::ttime{static_cast<unit::ttime::type>(states_.size())}};

	/* Update the positions of all celestial bodies. */
	for(const auto& sun : universe_.suns()) {
		state.suns.emplace_back(sun.id(), sun.position(state.time));
		sun_positions_[sun.id()] = sun.grid(state.time);
	}
	for(const auto& moon : universe_.moons()) {
		state.moons.emplace_back(moon.id(), moon.position(state.time));
		moon_positions_[moon.id()] = moon.grid(state.time);
	}

	/* Add the state to the list of states. */
	states_.push_back(std::move(state));

	check_collisions();
}

void tsimulator::check_collisions()
{
	TRACE;

	VALIDATE(universe_.suns().size() == sun_positions_.size());
	VALIDATE(universe_.moons().size() == moon_positions_.size());

	/*
	 * Test all suns against other suns and all moons.
	 *
	 * The algorithm tries to make the minimum of comparisions:
	 * - Iterate over all suns.
	 *   - Test them against the other suns after us in the collection.
	 *   - Test against all moons.
	 */
	for(auto s_itor = universe_.suns().begin(), end = universe_.suns().end();
		s_itor != end;
		++s_itor) {

		const auto& sun = sun_positions_.at(s_itor->id());
		for(auto t_itor = s_itor + 1; t_itor != end; ++t_itor) {

			const auto& test = sun_positions_.at(t_itor->id());
			if(grid::intersects(sun, test)) {
				collided_ = true;
				throw tcollision{};
			}
		}

		for(const auto& moon : universe_.moons()) {
			const auto& test = moon_positions_.at(moon.id());
			if(grid::intersects(sun, test)) {
				collided_ = true;
				throw tcollision{};
			}
		}
	}

	/*
	 * Test all moons against other moons.
	 *
	 * The algorithm tries to make the minimum of comparisions:
	 * - Iterate over all moons.
	 *   - Test them against the other moons after us in the collection.
	 */
	for(auto m_itor = universe_.moons().begin(), end = universe_.moons().end();
		m_itor != end;
		++m_itor) {

		const auto& moon = moon_positions_.at(m_itor->id());
		for(auto t_itor = m_itor + 1; t_itor != end; ++t_itor) {

			const auto& test = moon_positions_.at(t_itor->id());
			if(grid::intersects(moon, test)) {
				collided_ = true;
				throw tcollision{};
			}
		}
	}
}

} // namespace simulation
