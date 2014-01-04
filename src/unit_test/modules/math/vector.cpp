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

#include "modules/math/vector.tpp"

#include "modules/logger/logger.hpp"
#include "modules/unit/length.tpp"
#include "modules/unit/quantity/stream.hpp"
#include "modules/unit/quantity/comparison.tpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/math")

using namespace math;

static void test_index()
{
	{
		constexpr tvector<int, 3> vector{{1, 2, 3}};
		BOOST_CHECK_EQUAL(vector[0], 1);
		BOOST_CHECK_EQUAL(vector[1], 2);
		BOOST_CHECK_EQUAL(vector[2], 3);
	}

	{
		static_assert(tvector<unit::tlength, 3> {
						  {
							  1_m, 2_m, 3_m
						  }
					  }[0] == 1_m,
					  "No compile-time constant");
		static_assert(tvector<unit::tlength, 3> {
						  {
							  1_m, 2_m, 3_m
						  }
					  }[1] == 2_m,
					  "No compile-time constant");
		static_assert(tvector<unit::tlength, 3> {
						  {
							  1_m, 2_m, 3_m
						  }
					  }[2] == 3_m,
					  "No compile-time constant");
	}

	{
		constexpr tvector<unit::tlength, 3> vector{{1_m, 2_m, 3_m}};
		BOOST_CHECK_EQUAL(vector[0], 1_m);
		BOOST_CHECK_EQUAL(vector[1], 2_m);
		BOOST_CHECK_EQUAL(vector[2], 3_m);
	}
}

static void test_coordinate()
{
	{
		constexpr tvector<int, 3> vector{{1, 2, 3}};
		BOOST_CHECK_EQUAL(vector.x(), 1);
		BOOST_CHECK_EQUAL(vector.y(), 2);
		BOOST_CHECK_EQUAL(vector.z(), 3);
	}

	{
		static_assert(tvector<unit::tlength, 3>{{1_m, 2_m, 3_m}}.x() == 1_m,
					  "No compile-time constant");
		static_assert(tvector<unit::tlength, 3>{{1_m, 2_m, 3_m}}.y() == 2_m,
					  "No compile-time constant");
		static_assert(tvector<unit::tlength, 3>{{1_m, 2_m, 3_m}}.z() == 3_m,
					  "No compile-time constant");
	}

	{
		constexpr tvector<unit::tlength, 3> vector{{1_m, 2_m, 3_m}};
		BOOST_CHECK_EQUAL(vector.x(), 1_m);
		BOOST_CHECK_EQUAL(vector.y(), 2_m);
		BOOST_CHECK_EQUAL(vector.z(), 3_m);
	}
}

BOOST_AUTO_TEST_CASE(test_modules_math_vector)
{
	TRACE;

	static_assert(std::is_pod<tvector<int, 3>>::value,
				  "No compile-time constant");

	static_assert(std::is_pod<tvector<unit::tlength, 3>>::value,
				  "No compile-time constant");

	test_index();
	test_coordinate();
}
