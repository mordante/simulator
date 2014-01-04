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

#include "modules/simulation/detail/moon.hpp"

#include "lib/exception/throw.tpp"
#include "modules/geometry/stream.hpp"
#include "modules/logger/logger.hpp"

#include <boost/property_tree/ptree.hpp>

REGISTER_LOGGER_MODULE("/modules/simulator")

namespace simulation
{
namespace detail
{

tmoon::tmoon(std::string id__, geometry::tcartesian position__)
	: id{std::move(id__)}, position{std::move(position__)}
{
	TRACE_PARAMETERS(id, position);
}

tmoon::tmoon(const boost::property_tree::ptree& moon)
	: tmoon{moon.get<std::string>("id"),
			geometry::tcartesian::load(moon.get_child("position"))}
{
	TRACE;
}

tmoon tmoon::load(const boost::property_tree::ptree& moon)
{
	TRACE;

	switch(const int version{moon.get<int>("version")}) {
		case 1:
			return tmoon{moon};

		default:
			THROW_F(load_invalid_version,
					"Failed to load a simulator moon object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree tmoon::store() const
{
	TRACE;

	boost::property_tree::ptree result;

	result.put("version", 1);
	result.put("id", id);
	result.push_back(boost::property_tree::ptree::value_type{"position",
															 position.store()});

	return result;
}

} // namespace detail
} // namespace simulation
