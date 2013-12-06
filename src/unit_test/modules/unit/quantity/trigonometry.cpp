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

#include "modules/unit/quantity/trigonometry.tpp"

#include "modules/logger/logger.hpp"
#include "modules/unit/quantity/arithmetic.tpp"
#include "modules/unit/quantity/comparison.tpp"
#include "modules/unit/quantity/stream.hpp"
#include "modules/unit/types.tpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/unit")

using namespace unit;

#define EXECUTE(function)                                                      \
	do {                                                                       \
		function<double>();                                                    \
		function<unit::tfloat>();                                              \
	} while(0)

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static void sine()
{
	TRACE;

	/* BOOST_CHECK_CLOSE fails. */
	for(int i = 0; i <= 360; ++i) {
		const T rad{i* M_PI / 180.};
		const tquantity<RAD, T> q{rad};
		const tquantity<NONE, T> r{sin(rad)};
		const tquantity<NONE, T> d{1e-6};

		BOOST_CHECK_LE(abs(sin(q) - r), d);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static void cosine()
{
	TRACE;

	/* BOOST_CHECK_CLOSE fails. */
	for(int i = 0; i <= 360; ++i) {
		const T rad{i* M_PI / 180.};
		const tquantity<RAD, T> q{rad};
		const tquantity<NONE, T> r{cos(rad)};
		const tquantity<NONE, T> d{1e-6};

		BOOST_CHECK_LE(abs(cos(q) - r), d);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static void tangent()
{
	TRACE;

	/* BOOST_CHECK_CLOSE fails. */
	for(int i = 0; i <= 360; ++i) {
		if(i == 90 || i == 270) {
			continue;
		}
		const T rad{i* M_PI / 180.};
		const tquantity<RAD, T> q{rad};
		const tquantity<NONE, T> r{tan(rad)};
		const tquantity<NONE, T> d{1e-6};

		BOOST_CHECK_LE(abs(tan(q) - r), d);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static void arcsine()
{
	TRACE;

	/* BOOST_CHECK_CLOSE fails. */
	for(int i = 0; i <= 360; ++i) {
		const T rad{sin(i * M_PI / 180.)};
		const tquantity<NONE, T> q{rad};
		const tquantity<RAD, T> r{asin(rad)};
		const tquantity<RAD, T> d{1e-6};

		BOOST_CHECK_LE(abs(asin(q) - r), d);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static void arccosine()
{
	TRACE;

	/* BOOST_CHECK_CLOSE fails. */
	for(int i = 0; i <= 360; ++i) {
		const T rad{cos(i * M_PI / 180.)};
		const tquantity<NONE, T> q{rad};
		const tquantity<RAD, T> r{acos(rad)};
		const tquantity<RAD, T> d{1e-6};

		BOOST_CHECK_LE(abs(acos(q) - r), d);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static void arctangent()
{
	TRACE;

	/* BOOST_CHECK_CLOSE fails. */
	for(int i = 0; i <= 360; ++i) {
		if(i == 90 || i == 270) {
			continue;
		}
		const T rad{tan(i * M_PI / 180.)};
		const tquantity<NONE, T> q{rad};
		const tquantity<RAD, T> r{atan(rad)};
		const tquantity<RAD, T> d{1e-6};

		BOOST_CHECK_LE(abs(atan(q) - r), d);
	}

	for(int y = -18; y < 0; ++y) {
		for(int x = -18; x < 0; ++x) {
			const tquantity<RAD, T> d{1e-6};
			{
				const tquantity<NONE, T> Y{static_cast<T>(y)};
				const tquantity<NONE, T> X{static_cast<T>(x)};
				const tquantity<RAD, T> r{atan2(y, x)};

				BOOST_CHECK_LE(abs(atan(Y, X) - r), d);
			}
			{
				const tquantity<NONE, T> Y{static_cast<T>(-y)};
				const tquantity<NONE, T> X{static_cast<T>(x)};
				const tquantity<RAD, T> r{atan2(-y, x)};

				BOOST_CHECK_LE(abs(atan(Y, X) - r), d);
			}
			{
				const tquantity<NONE, T> Y{static_cast<T>(y)};
				const tquantity<NONE, T> X{static_cast<T>(-x)};
				const tquantity<RAD, T> r{atan2(y, -x)};

				BOOST_CHECK_LE(abs(atan(Y, X) - r), d);
			}
			{
				const tquantity<NONE, T> Y{static_cast<T>(-y)};
				const tquantity<NONE, T> X{static_cast<T>(-x)};
				const tquantity<RAD, T> r{atan2(-y, -x)};

				BOOST_CHECK_LE(abs(atan(Y, X) - r), d);
			}
		}
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static void constant_pi()
{
	TRACE;

	tquantity<RAD, T> r{boost::math::constants::pi<T>()};
	BOOST_CHECK_EQUAL(r, pi<T>());

	r *= 2;
	BOOST_CHECK_EQUAL(r, pi<T>(2));

	r *= 2;
	BOOST_CHECK_EQUAL(r, pi<T>(4));
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_unit_trigonometry)
{
	TRACE;

	EXECUTE(sine);
	EXECUTE(cosine);
	EXECUTE(tangent);

	EXECUTE(arcsine);
	EXECUTE(arccosine);
	EXECUTE(arctangent);

	EXECUTE(constant_pi);
}
