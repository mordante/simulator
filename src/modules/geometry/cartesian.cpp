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

#include "modules/geometry/cartesian.hpp"

#include "lib/exception/throw.tpp"
#include "modules/geometry/polar.hpp"
#include "modules/logger/logger.hpp"
#include "modules/unit/ptree.tpp"
#include "modules/unit/quantity/trigonometry.tpp"

REGISTER_LOGGER_MODULE("/modules/unit")

namespace geometry
{

tcartesian::tcartesian(const boost::property_tree::ptree& cartesian)
	: tcartesian(cartesian.get<unit::tlength>("x"),
				 cartesian.get<unit::tlength>("y"),
				 cartesian.get<unit::tlength>("z"))
{
	TRACE;
}

tcartesian tcartesian::load(const boost::property_tree::ptree& cartesian)
{
	TRACE;

	switch(const int version{cartesian.get<int>("version")}) {
		case 1:
			return tcartesian(cartesian);

		default:
			THROW_F(load_invalid_version,
					"Failed to load a cartesian object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree tcartesian::store() const
{
	TRACE;

	boost::property_tree::ptree result;

	result.put("version", 1);
	result.put("x", x);
	result.put("y", y);
	result.put("z", z);

	return result;
}

tcartesian::operator tpolar() const
{
	TRACE;

	const unit::tlength l{length()};

	if(l == 0_m) {
		return tpolar{0_m, 0_rad, 0_rad};
	}

	return tpolar{l, atan(y, x), acos(z / l)};
}

} // namespace geometry
