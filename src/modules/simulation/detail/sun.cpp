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

#include "modules/simulation/detail/sun.hpp"

#include "lib/exception/throw.tpp"
#include "modules/geometry/stream.hpp"
#include "modules/logger/logger.hpp"

#include <boost/property_tree/ptree.hpp>

REGISTER_LOGGER_MODULE("/modules/simulator")

namespace simulation
{
namespace detail
{

tsun::tsun(std::string id__, geometry::tcartesian position__)
	: id{std::move(id__)}, position{std::move(position__)}
{
	TRACE_PARAMETERS(id__, position__);
}

tsun::tsun(const boost::property_tree::ptree& sun)
	: tsun{sun.get<std::string>("id"),
		   geometry::tcartesian::load(sun.get_child("position"))}
{
	TRACE;
}

tsun tsun::load(const boost::property_tree::ptree& sun)
{
	TRACE;

	switch(const int version{sun.get<int>("version")}) {
		case 1:
			return tsun{sun};

		default:
			THROW_F(load_invalid_version,
					"Failed to load a simulator sun object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree tsun::store() const
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
