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

#ifndef MODULES_UNIT_TIME_TPP_INCLUDED
#define MODULES_UNIT_TIME_TPP_INCLUDED

/**
 * @file
 * Contains the time specialisation of @ref unit::tunit.
 *
 * @note There are no unit tests for this file.
 *
 * See @ref unit_module for more information.
 */

#include "modules/unit/quantity.tpp"

namespace unit
{

/** The time value. */
using ttime = tquantity<unit::S, int>;

} // namespace unit

/**
 * Conversion operator for »_s«.
 *
 * @note At the moment time has no fraction seconds so no @c long @c double
 * overload is available.
 *
 * @param value                   A value in seconds.
 */
inline constexpr unit::ttime operator"" _s(const unsigned long long value)
{
	return unit::ttime{static_cast<unit::ttime::type>(value)};
}

#endif
