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

#include "modules/celestial/moon.hpp"

#include "lib/exception/throw.tpp"
#include "modules/geometry/stream.hpp"
#include "modules/logger/logger.hpp"
#include "modules/unit/ptree.tpp"
#include "modules/unit/quantity/stream.hpp"

REGISTER_LOGGER_MODULE("/modules/celestial")

namespace celestial
{

tmoon::tmoon(std::string id__,
			 geometry::tcartesian origin__,
			 geometry::torbit orbit__,
			 unit::tlength radius__)
	: id_{std::move(id__)}
	, origin_{std::move(origin__)}
	, orbit_{std::move(orbit__)}
	, radius_{std::move(radius__)}
{
	TRACE_PARAMETERS(id_, origin_, orbit_, radius_);
}

tmoon::tmoon(const boost::property_tree::ptree& moon)
	: tmoon{moon.get<std::string>("id"),
			geometry::tcartesian::load(moon.get_child("origin")),
			geometry::torbit::load(moon.get_child("orbit")),
			moon.get<unit::tlength>("radius")}
{
	TRACE;
}

tmoon tmoon::load(const boost::property_tree::ptree& moon)
{
	TRACE;

	switch(const int version{moon.get<int>("version")}) {
		case 1:
			return tmoon(moon);

		default:
			THROW_F(load_invalid_version,
					"Failed to load a moon object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree tmoon::store() const
{
	TRACE;

	boost::property_tree::ptree result;

	result.put("version", 1);
	result.put("id", id_);
	result.push_back(
			boost::property_tree::ptree::value_type{"origin", origin_.store()});
	result.push_back(
			boost::property_tree::ptree::value_type{"orbit", orbit_.store()});
	result.put("radius", radius_);

	return result;
}

geometry::tcartesian tmoon::position(const unit::ttime time) const
{
	TRACE_PARAMETERS(time);

	return origin_ + orbit_.position(time);
}

const std::string& tmoon::id() const
{
	TRACE_GETTER(id_);

	return id_;
}

} // namespace celestial
