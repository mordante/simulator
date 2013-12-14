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

#include "modules/simulation/detail/state.hpp"

#include "lib/exception/throw.tpp"
#include "modules/unit/quantity/stream.hpp"
#include "modules/logger/logger.hpp"

#include <boost/property_tree/ptree.hpp>

REGISTER_LOGGER_MODULE("/modules/simulator")

namespace simulation
{
namespace detail
{

tstate::tstate(unit::ttime time__) : time{time__}
{
	TRACE_PARAMETERS(time__);
}

tstate::tstate(const boost::property_tree::ptree& state)
	: time{state.get<unit::ttime::type>("time")}
{
	TRACE;

	boost::property_tree::ptree sun_tree{state.get_child("suns")};
	for(const auto& sun : sun_tree) {
		/* Note no manual tempering test. */
		suns.push_back(tsun::load(sun.second));
	}
	boost::property_tree::ptree moon_tree{state.get_child("moons")};
	for(const auto& moon : moon_tree) {
		/* Note no manual tempering test. */
		moons.push_back(tmoon::load(moon.second));
	}
}

tstate tstate::load(const boost::property_tree::ptree& state)
{
	TRACE;

	switch(const int version{state.get<int>("version")}) {
		case 1:
			return tstate{state};

		default:
			THROW_F(load_invalid_version,
					"Failed to load a simulator state object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree tstate::store() const
{
	TRACE;

	boost::property_tree::ptree result;

	result.put("version", 1);
	result.put("time", time.value);

	boost::property_tree::ptree sun_tree;
	for(const auto& sun : suns) {
		sun_tree.push_back(
				boost::property_tree::ptree::value_type{"sun", sun.store()});
	}
	result.push_back(boost::property_tree::ptree::value_type{"suns", sun_tree});

	boost::property_tree::ptree moon_tree;
	for(const auto& moon : moons) {
		moon_tree.push_back(
				boost::property_tree::ptree::value_type{"moon", moon.store()});
	}
	result.push_back(
			boost::property_tree::ptree::value_type{"moons", moon_tree});

	return result;
}

} // namespace detail
} // namespace simulation
