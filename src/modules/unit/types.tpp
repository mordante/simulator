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

#ifndef MODULES_UNIT_TYPES_TPP_INCLUDED
#define MODULES_UNIT_TYPES_TPP_INCLUDED

/**
 * @file
 * Contains the basic types for the quantity library.
 *
 * The types are using the boost multiprecision library. These types are not
 * used yet, but might be enabled in the future.
 *
 * See @ref unit_module for more information.
 */

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace unit
{

/** The basic integral type. */
using tinteger = boost::multiprecision::
		number<boost::multiprecision::cpp_int_backend<64, true>>;

/** The basic floating point type. */
using tfloat = boost::multiprecision::
		number<boost::multiprecision::cpp_dec_float<50>>;

} // namespace unit

#endif
