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

#ifndef MODULES_UNIT_ANGLE_TPP_INCLUDED
#define MODULES_UNIT_ANGLE_TPP_INCLUDED

/**
 * @file
 * Contains the angle specialisation of @ref unit::tunit.
 *
 * @note There are no unit tests for this file.
 *
 * See @ref unit_module for more information.
 */

#include "modules/unit/quantity/trigonometry.tpp"

namespace unit
{

/** The angle type. */
using tangle = tquantity<RAD, double>;

} // namespace unit

/**
 * Conversion operator for »_rad«.
 *
 * @param value                   A value in radians.
 */
inline constexpr unit::tangle operator"" _rad(const long double value)
{
	return unit::tangle{static_cast<unit::tangle::type>(value)};
}

/**
 * Conversion operator for »_rad«.
 *
 * @param value                   A value in radians.
 */
inline constexpr unit::tangle operator"" _rad(const unsigned long long value)
{
	return unit::pi<unit::tangle::type>(value / 180.);
}

/**
 * Conversion operator for »_deg«.
 *
 * The @p value will be converted to radians.
 *
 * @param value                   A value in degrees.
 */
inline constexpr unit::tangle operator"" _deg(const long double value)
{
	return unit::pi<unit::tangle::type>(
			static_cast<unit::tangle::type>(value / 180.));
}

/**
 * Conversion operator for »_deg«.
 *
 * The @p value will be converted to radians.
 *
 * @param value                   A value in degrees.
 */
inline constexpr unit::tangle operator"" _deg(const unsigned long long value)
{
	return unit::pi<unit::tangle::type>(
			static_cast<unit::tangle::type>(value / 180.));
}

#endif
