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

#include "modules/celestial/planet.hpp"

#include "lib/exception/throw.tpp"
#include "modules/geometry/stream.hpp"
#include "modules/logger/logger.hpp"
#include "modules/unit/ptree.tpp"
#include "modules/unit/quantity/stream.hpp"

REGISTER_LOGGER_MODULE("/modules/celestial")

namespace celestial
{

tplanet::tplanet(std::string id__,
				 geometry::tcartesian origin__,
				 unit::tlength length__,
				 unit::tlength width__)
	: id_{std::move(id__)}
	, origin_{std::move(origin__)}
	, length_{length__}
	, width_{width__}
{
	TRACE_PARAMETERS(id_, origin_, length_, width_);
}

tplanet::tplanet(const boost::property_tree::ptree& planet)
	: tplanet{planet.get<std::string>("id"),
			  geometry::tcartesian::load(planet.get_child("origin")),
			  planet.get<unit::tlength>("length"),
			  planet.get<unit::tlength>("width")}
{
	TRACE;
}

tplanet tplanet::load(const boost::property_tree::ptree& planet)
{
	TRACE;

	switch(const int version{planet.get<int>("version")}) {
		case 1:
			return tplanet(planet);

		default:
			THROW_F(load_invalid_version,
					"Failed to load a planet object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree tplanet::store() const
{
	TRACE;

	boost::property_tree::ptree result;

	result.put("version", 1);
	result.put("id", id_);
	result.push_back(
			boost::property_tree::ptree::value_type{"origin", origin_.store()});
	result.put("length", length_);
	result.put("width", width_);

	return result;
}

const std::string& tplanet::id() const
{
	return id_;
}

} // namespace celestial
