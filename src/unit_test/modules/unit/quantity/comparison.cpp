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

#include "modules/unit/quantity/comparison.tpp"

#include "modules/logger/logger.hpp"
#include "modules/unit/quantity/stream.hpp"
#include "modules/unit/types.tpp"

#include <boost/test/unit_test.hpp>

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
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
equality()
{
	TRACE;

	const tquantity<NONE, T> q1(1);
	const tquantity<NONE, T> q2(2);

	BOOST_CHECK_EQUAL(q1, q1);
	BOOST_CHECK_EQUAL(q2, q2);
	BOOST_CHECK_NE(q1, q2);
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
equality()
{
	TRACE;

	const tquantity<NONE, T> q1(1.001);
	const tquantity<NONE, T> q2(1.002);

	BOOST_CHECK_EQUAL(q1, q1);
	BOOST_CHECK_EQUAL(q2, q2);
	BOOST_CHECK_NE(q1, q2);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
less()
{
	TRACE;

	const tquantity<NONE, T> q1(1);
	const tquantity<NONE, T> q2(2);

	BOOST_CHECK_LT(q1, q2);

	BOOST_CHECK_LE(q1, q1);
	BOOST_CHECK_LE(q2, q2);
	BOOST_CHECK_LE(q1, q2);

	BOOST_CHECK_GT(q2, q1);

	BOOST_CHECK_GE(q1, q1);
	BOOST_CHECK_GE(q2, q2);
	BOOST_CHECK_GE(q2, q1);
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
less()
{
	TRACE;

	const tquantity<NONE, T> q1(1.001);
	const tquantity<NONE, T> q2(1.002);

	BOOST_CHECK_LT(q1, q2);

	BOOST_CHECK_LE(q1, q1);
	BOOST_CHECK_LE(q2, q2);
	BOOST_CHECK_LE(q1, q2);

	BOOST_CHECK_GT(q2, q1);

	BOOST_CHECK_GE(q1, q1);
	BOOST_CHECK_GE(q2, q2);
	BOOST_CHECK_GE(q2, q1);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_unit_comparison)
{
	TRACE;

	EXECUTE(equality);
	EXECUTE(less);
}
