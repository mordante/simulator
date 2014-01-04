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

#include "modules/math/vector/arithmetic.tpp"

#include "modules/logger/logger.hpp"
#include "modules/math/vector/comparison.tpp"
#include "modules/unit/length.tpp"
#include "modules/unit/quantity/arithmetic.tpp"
#include "modules/unit/quantity/comparison.tpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/math")

using namespace math;

BOOST_AUTO_TEST_CASE(test_modules_math_vector_arithmetic)
{
	TRACE;

	/************************************************************************/

	{
		constexpr tvector<int, 3> lhs{{1, 2, 3}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		constexpr tvector<int, 3> result{{2, 4, 6}};
		BOOST_CHECK_EQUAL(lhs + rhs == result, true);
	}

	{
		static_assert(tvector<unit::tlength, 1> {
						  {
							  1_m
						  }
					  } + tvector<unit::tlength, 1>{{1_m}}
					  == tvector<unit::tlength, 1>{{2_m}},
					  "No compile-time constant");
	}

	{
		constexpr tvector<unit::tlength, 3> lhs{{1_m, 2_m, 3_m}};
		constexpr tvector<unit::tlength, 3> rhs{{1_m, 2_m, 3_m}};
		constexpr tvector<unit::tlength, 3> result{{2_m, 4_m, 6_m}};
		BOOST_CHECK_EQUAL(lhs + rhs == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 3> lhs{{2, 4, 6}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		constexpr tvector<int, 3> result{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs - rhs == result, true);
	}

	{
		static_assert(tvector<unit::tlength, 1> {
						  {
							  2_m
						  }
					  } - tvector<unit::tlength, 1>{{1_m}}
					  == tvector<unit::tlength, 1>{{1_m}},
					  "No compile-time constant");
	}

	{
		constexpr tvector<unit::tlength, 3> lhs{{2_m, 4_m, 6_m}};
		constexpr tvector<unit::tlength, 3> rhs{{1_m, 2_m, 3_m}};
		constexpr tvector<unit::tlength, 3> result{{1_m, 2_m, 3_m}};
		BOOST_CHECK_EQUAL(lhs - rhs == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 3> lhs{{1, 2, 3}};
		constexpr tvector<int, 3> result{{3, 6, 9}};
		BOOST_CHECK_EQUAL(lhs * 3 == result, true);
		BOOST_CHECK_EQUAL(3 * lhs == result, true);
	}

	{
		static_assert(tvector<unit::tlength, 1>{{2_m}} * 3.
					  == tvector<unit::tlength, 1>{{6_m}},
					  "No compile-time constant");
		static_assert(3. * tvector<unit::tlength, 1>{{2_m}}
					  == tvector<unit::tlength, 1>{{6_m}},
					  "No compile-time constant");
	}

	{
		constexpr tvector<unit::tlength, 3> lhs{{1_m, 2_m, 3_m}};
		constexpr tvector<unit::tlength, 3> result{{3_m, 6_m, 9_m}};
		BOOST_CHECK_EQUAL(lhs * 3. == result, true);
		BOOST_CHECK_EQUAL(3. * lhs == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 3> lhs{{1, 2, 3}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		constexpr tvector<int, 3> result{{1, 4, 9}};
		BOOST_CHECK_EQUAL(lhs * rhs == result, true);
	}

	{
		using tresult = decltype(unit::tlength{} * unit::tlength{});
		static_assert(tvector<unit::tlength, 1>{{2_m}}
					  * tvector<unit::tlength, 1>{{3_m}}
					  == tvector<tresult, 1>{{tresult{6.}}},
					  "No compile-time constant");
	}

	{
		using tresult = decltype(unit::tlength{} * unit::tlength{});

		constexpr tvector<unit::tlength, 3> lhs{{1_m, 2_m, 3_m}};
		constexpr tvector<unit::tlength, 3> rhs{{1_m, 2_m, 3_m}};
		constexpr tvector<tresult, 3> result{
				{tresult{1}, tresult{4}, tresult{9}}};
		BOOST_CHECK_EQUAL(lhs * rhs == result, true);
	}

	/************************************************************************/

	{
		tvector<int, 3> lhs{{1, 2, 3}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		constexpr tvector<int, 3> result{{1, 4, 9}};
		BOOST_CHECK_EQUAL((lhs *= rhs) == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 3> lhs{{3, 6, 9}};
		constexpr tvector<int, 3> result{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs / 3 == result, true);
	}

	{
		static_assert(tvector<unit::tlength, 1>{{6_m}} / 3.
					  == tvector<unit::tlength, 1>{{2_m}},
					  "No compile-time constant");
	}

	{
		constexpr tvector<unit::tlength, 3> lhs{{3_m, 6_m, 9_m}};
		constexpr tvector<unit::tlength, 3> result{{1_m, 2_m, 3_m}};
		BOOST_CHECK_EQUAL(lhs / 3. == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 3> lhs{{1, 4, 9}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		constexpr tvector<int, 3> result{{1, 2, 3}};
		BOOST_CHECK_EQUAL(lhs / rhs == result, true);
	}

	{
		using tresult = decltype(unit::tlength{} / unit::tlength{});
		static_assert(tvector<unit::tlength, 1>{{6_m}}
					  / tvector<unit::tlength, 1>{{2_m}}
					  == tvector<tresult, 1>{{tresult{3.}}},
					  "No compile-time constant");
	}

	{
		using tresult = decltype(unit::tlength{} / unit::tlength{});

		constexpr tvector<unit::tlength, 3> lhs{{1_m, 4_m, 9_m}};
		constexpr tvector<unit::tlength, 3> rhs{{1_m, 2_m, 3_m}};
		constexpr tvector<tresult, 3> result{
				{tresult{1}, tresult{2}, tresult{3}}};
		BOOST_CHECK_EQUAL(lhs / rhs == result, true);
	}

	/************************************************************************/

	{
		tvector<int, 3> lhs{{1, 4, 9}};
		constexpr tvector<int, 3> rhs{{1, 2, 3}};
		constexpr tvector<int, 3> result{{1, 2, 3}};
		BOOST_CHECK_EQUAL((lhs /= rhs) == result, true);
	}
}
