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

#include "modules/math/vector/comparison.tpp"

#include "modules/logger/logger.hpp"
#include "modules/unit/length.tpp"
#include "modules/unit/quantity/comparison.tpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/math")

using namespace math;

BOOST_AUTO_TEST_CASE(test_modules_math_vector_comparison)
{
	TRACE;

	static_assert(tvector<int, 1>{{1}} == tvector<int, 1>{{1}},
				  "No compile-time constant");
	static_assert(tvector<int, 1>{{1}} != tvector<int, 1>{{2}},
				  "No compile-time constant");
	static_assert(tvector<int, 1>{{1}} < tvector<int, 1>{{2}},
				  "No compile-time constant");
	static_assert(tvector<int, 1>{{1}} <= tvector<int, 1>{{2}},
				  "No compile-time constant");
	static_assert(tvector<int, 1>{{3}} > tvector<int, 1>{{2}},
				  "No compile-time constant");
	static_assert(tvector<int, 1>{{3}} >= tvector<int, 1>{{2}},
				  "No compile-time constant");


	static_assert(tvector<unit::tlength, 1>{{1_m}}
				  == tvector<unit::tlength, 1>{{1_m}},
				  "No compile-time constant");
	static_assert(tvector<unit::tlength, 1>{{1_m}}
				  != tvector<unit::tlength, 1>{{2_m}},
				  "No compile-time constant");
	static_assert(tvector<unit::tlength, 1>{{1_m}}
				  < tvector<unit::tlength, 1>{{2_m}},
				  "No compile-time constant");
	static_assert(tvector<unit::tlength, 1>{{1_m}}
				  <= tvector<unit::tlength, 1>{{2_m}},
				  "No compile-time constant");
	static_assert(tvector<unit::tlength, 1>{{3_m}}
				  > tvector<unit::tlength, 1>{{2_m}},
				  "No compile-time constant");
	static_assert(tvector<unit::tlength, 1>{{3_m}}
				  >= tvector<unit::tlength, 1>{{2_m}},
				  "No compile-time constant");

	{
		constexpr tvector<int, 3> lhs{{1, 2, 3}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs == rhs, true);
		BOOST_CHECK_EQUAL(lhs != rhs, false);
		BOOST_CHECK_EQUAL(lhs < rhs, false);
		BOOST_CHECK_EQUAL(lhs <= rhs, true);
		BOOST_CHECK_EQUAL(lhs > rhs, false);
		BOOST_CHECK_EQUAL(lhs >= rhs, true);
	}

	{
		constexpr tvector<int, 3> lhs{{1, 2, 4}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs == rhs, false);
		BOOST_CHECK_EQUAL(lhs != rhs, true);
		BOOST_CHECK_EQUAL(lhs < rhs, false);
		BOOST_CHECK_EQUAL(lhs <= rhs, false);
		BOOST_CHECK_EQUAL(lhs > rhs, true);
		BOOST_CHECK_EQUAL(lhs >= rhs, true);
	}

	{
		constexpr tvector<int, 3> lhs{{1, 3, 3}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs == rhs, false);
		BOOST_CHECK_EQUAL(lhs != rhs, true);
		BOOST_CHECK_EQUAL(lhs < rhs, false);
		BOOST_CHECK_EQUAL(lhs <= rhs, false);
		BOOST_CHECK_EQUAL(lhs > rhs, true);
		BOOST_CHECK_EQUAL(lhs >= rhs, true);
	}

	{
		constexpr tvector<int, 3> lhs{{2, 2, 3}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs == rhs, false);
		BOOST_CHECK_EQUAL(lhs != rhs, true);
		BOOST_CHECK_EQUAL(lhs < rhs, false);
		BOOST_CHECK_EQUAL(lhs <= rhs, false);
		BOOST_CHECK_EQUAL(lhs > rhs, true);
		BOOST_CHECK_EQUAL(lhs >= rhs, true);
	}

	{
		constexpr tvector<int, 3> lhs{{0, 2, 3}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs == rhs, false);
		BOOST_CHECK_EQUAL(lhs != rhs, true);
		BOOST_CHECK_EQUAL(lhs < rhs, true);
		BOOST_CHECK_EQUAL(lhs <= rhs, true);
		BOOST_CHECK_EQUAL(lhs > rhs, false);
		BOOST_CHECK_EQUAL(lhs >= rhs, false);
	}

	{
		constexpr tvector<int, 3> lhs{{1, 1, 3}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs == rhs, false);
		BOOST_CHECK_EQUAL(lhs != rhs, true);
		BOOST_CHECK_EQUAL(lhs < rhs, true);
		BOOST_CHECK_EQUAL(lhs <= rhs, true);
		BOOST_CHECK_EQUAL(lhs > rhs, false);
		BOOST_CHECK_EQUAL(lhs >= rhs, false);
	}

	{
		constexpr tvector<int, 3> lhs{{1, 2, 2}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs == rhs, false);
		BOOST_CHECK_EQUAL(lhs != rhs, true);
		BOOST_CHECK_EQUAL(lhs < rhs, true);
		BOOST_CHECK_EQUAL(lhs <= rhs, true);
		BOOST_CHECK_EQUAL(lhs > rhs, false);
		BOOST_CHECK_EQUAL(lhs >= rhs, false);
	}
}
