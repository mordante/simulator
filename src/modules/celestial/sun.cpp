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

#include "modules/celestial/sun.hpp"

#include "lib/exception/throw.tpp"
#include "modules/geometry/stream.hpp"
#include "modules/logger/logger.hpp"
#include "modules/unit/ptree.tpp"
#include "modules/unit/quantity/stream.hpp"

REGISTER_LOGGER_MODULE("/modules/celestial")

namespace celestial
{

tsun::tsun(std::string id__,
		   geometry::tcartesian origin__,
		   geometry::torbit orbit__,
		   unit::tlength radius__,
		   unit::tenergy energy_output__)
	: id_{std::move(id__)}
	, origin_{std::move(origin__)}
	, orbit_{std::move(orbit__)}
	, radius_{std::move(radius__)}
	, energy_output_{std::move(energy_output__)}
{
	TRACE_PARAMETERS(id_, origin_, orbit_, radius_, energy_output_);
}

tsun::tsun(const boost::property_tree::ptree& sun)
	: tsun{sun.get<std::string>("id"),
		   geometry::tcartesian::load(sun.get_child("origin")),
		   geometry::torbit::load(sun.get_child("orbit")),
		   sun.get<unit::tlength>("radius"),
		   sun.get<unit::tenergy>("energy_output")}
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
					"Failed to load a sun object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree tsun::store() const
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
	result.put("energy_output", energy_output_);

	return result;
}

geometry::tcartesian tsun::position(const unit::ttime time) const
{
	TRACE_PARAMETERS(time);

	return origin_ + orbit_.position(time);
}

const std::string& tsun::id() const
{
	TRACE_GETTER(id_);

	return id_;
}

} // namespace celestial
