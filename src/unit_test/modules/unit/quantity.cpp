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

#include "modules/unit/quantity.tpp"

#include "modules/logger/logger.hpp"
#include "modules/unit/types.tpp"
#include "modules/unit/unit.tpp"

#include <boost/test/unit_test.hpp>

#include <limits>
#include <type_traits>

REGISTER_LOGGER_MODULE("/unit_test/modules/unit")

using namespace unit;

#define EXECUTE(function)                                                      \
	do {                                                                       \
		function<int>();                                                       \
		function<double>();                                                    \
		function<unit::tinteger>();                                            \
		function<unit::tfloat>();                                              \
	} while(0)

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
ctor()
{
	TRACE;

	const tquantity<NONE, T> quantity{1.5};
	BOOST_CHECK_EQUAL(quantity.value, 1.5);
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
ctor()
{
	TRACE;

	const tquantity<NONE, T> quantity{1};
	BOOST_CHECK_EQUAL(quantity.value, 1);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_unit_quantity)
{
	TRACE;

	EXECUTE(ctor);
}
