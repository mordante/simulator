/*
 * Copyright (C) 2013 by Mark de Wever <koraq@xs4all.nl>
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

#include "modules/celestial/universe.hpp"

#include "lib/exception/throw.tpp"
#include "modules/logger/logger.hpp"
#include "modules/unit/ptree.tpp"

REGISTER_LOGGER_MODULE("/modules/celestial")

namespace celestial
{

tuniverse::tuniverse(const boost::property_tree::ptree& universe)
{
	TRACE;

	boost::property_tree::ptree suns{universe.get_child("suns")};
	for(const auto& sun : suns) {
		add(tsun::load(sun.second));
	}

	boost::property_tree::ptree moons{universe.get_child("moons")};
	for(const auto& moon : moons) {
		add(tmoon::load(moon.second));
	}

	boost::property_tree::ptree planets{universe.get_child("planets")};
	for(const auto& planet : planets) {
		add(tplanet::load(planet.second));
	}
}

tuniverse tuniverse::load(const boost::property_tree::ptree& universe)
{
	TRACE;

	switch(const int version{universe.get<int>("version")}) {
		case 1:
			return tuniverse(universe);

		default:
			THROW_F(load_invalid_version,
					"Failed to load a universe object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree tuniverse::store() const
{
	TRACE;

	boost::property_tree::ptree result;
	result.put("version", "1");

	boost::property_tree::ptree suns;
	for(const auto& sun : suns_) {
		suns.push_back(
				boost::property_tree::ptree::value_type{"sun", sun.store()});
	}
	result.push_back(boost::property_tree::ptree::value_type{"suns", suns});

	boost::property_tree::ptree moons;
	for(const auto& moon : moons_) {
		moons.push_back(
				boost::property_tree::ptree::value_type{"moon", moon.store()});
	}
	result.push_back(boost::property_tree::ptree::value_type{"moons", moons});

	boost::property_tree::ptree planets;
	for(const auto& planet : planets_) {
		planets.push_back(boost::property_tree::ptree::value_type{
				"planet", planet.store()});
	}
	result.push_back(
			boost::property_tree::ptree::value_type{"planets", planets});

	return result;
}

void tuniverse::add(tsun&& sun)
{
	TRACE;

	if(std::any_of(suns_.begin(), suns_.end(), [&sun](const tsun& s) {
		   return s.id() == sun.id();
	   })) {

		THROW_E(invalid_value,
				"Adding duplicates is not allowed. A sun with id »",
				sun.id(),
				"« already exists.");
	}

	suns_.push_back(std::move(sun));
}

void tuniverse::add(tmoon&& moon)
{
	TRACE;

	if(std::any_of(moons_.begin(), moons_.end(), [&moon](const tmoon& m) {
		   return m.id() == moon.id();
	   })) {

		THROW_E(invalid_value,
				"Adding duplicates is not allowed. A moon with id »",
				moon.id(),
				"« already exists.");
	}

	moons_.push_back(std::move(moon));
}

void tuniverse::add(tplanet&& planet)
{
	TRACE;

	if(std::any_of(
			   planets_.begin(), planets_.end(), [&planet](const tplanet& m) {
				   return m.id() == planet.id();
			   })) {

		THROW_E(invalid_value,
				"Adding duplicates is not allowed. A planet with id »",
				planet.id(),
				"« already exists.");
	}

	planets_.push_back(std::move(planet));
}

const std::vector<tsun>& tuniverse::suns() const
{
	TRACE;

	return suns_;
}

const std::vector<tmoon>& tuniverse::moons() const
{
	TRACE;

	return moons_;
}

const std::vector<tplanet>& tuniverse::planets() const
{
	TRACE;

	return planets_;
}

} // namespace celestial
