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

#include "modules/geometry/polar.hpp"

#include "lib/exception/throw.tpp"
#include "modules/geometry/cartesian.hpp"
#include "modules/logger/logger.hpp"
#include "modules/unit/ptree.tpp"
#include "modules/unit/quantity/arithmetic.tpp"
#include "modules/unit/quantity/trigonometry.tpp"

REGISTER_LOGGER_MODULE("/modules/unit")

namespace geometry
{

tpolar::tpolar(const boost::property_tree::ptree& polar)
	: tpolar(polar.get<unit::tlength>("r"), polar.get<unit::tangle>("theta"),
			 polar.get<unit::tangle>("phi"))
{
	TRACE;
}

tpolar tpolar::load(const boost::property_tree::ptree& polar)
{
	TRACE;

	switch(const int version{polar.get<int>("version")}) {
		case 1:
			return tpolar{polar};

		default:
			THROW_F(load_invalid_version,
					"Failed to load a polar object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree tpolar::store() const
{
	TRACE;

	boost::property_tree::ptree result;

	result.put("version", 1);
	result.put("r", r);
	result.put("theta", theta);
	result.put("phi", phi);

	return result;
}

tpolar::operator tcartesian() const
{
	TRACE;

	return tcartesian{r * cos(theta) * sin(phi), r * sin(theta) * sin(phi),
					  r * cos(phi)};
}

} // namespace geometry
