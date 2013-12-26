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

#include "modules/math/vector/utility.tpp"

#include "modules/logger/logger.hpp"
#include "modules/unit/length.tpp"
#include "modules/unit/quantity/comparison.tpp"
#include "modules/unit/quantity/arithmetic.tpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/math")

using namespace math;

BOOST_AUTO_TEST_CASE(test_modules_math_vector_utility)
{
	TRACE;

	/************************************************************************/

	{
		constexpr tvector<int, 3> vector{{1, 2, 3}};
		constexpr int result{6};
		BOOST_CHECK_EQUAL(sum(vector) == result, true);
	}

	{
		static_assert(sum(tvector<unit::tlength, 3>{
							  {unit::tlength{1}, unit::tlength{2},
							   unit::tlength{3}}}) == unit::tlength{6.},
					  "No compile-time constant");
	}

	{
		constexpr tvector<unit::tlength, 3> vector{
				{unit::tlength{1}, unit::tlength{2}, unit::tlength{3}}};
		constexpr unit::tlength result{6.};
		BOOST_CHECK_EQUAL(sum(vector) == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 3> vector{{1, 2, 3}};
		constexpr int result{6};
		BOOST_CHECK_EQUAL(pow_sum<1>(vector) == result, true);
	}

	{
		static_assert(pow_sum<1>(tvector<unit::tlength, 3>{
							  {unit::tlength{1}, unit::tlength{2},
							   unit::tlength{3}}}) == unit::tlength{6.},
					  "No compile-time constant");
	}

	{
		constexpr tvector<unit::tlength, 3> vector{
				{unit::tlength{1}, unit::tlength{2}, unit::tlength{3}}};
		constexpr unit::tlength result{6.};
		BOOST_CHECK_EQUAL(pow_sum<1>(vector) == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 3> vector{{1, 2, 3}};
		constexpr int result{14};
		BOOST_CHECK_EQUAL(pow_sum<2>(vector) == result, true);
	}

	{
		using tresult = decltype(unit::tlength{} * unit::tlength{});
		static_assert(pow_sum<2>(tvector<unit::tlength, 3>{
							  {unit::tlength{1}, unit::tlength{2},
							   unit::tlength{3}}}) == tresult{14.},
					  "No compile-time constant");
	}

	{
		using tresult = decltype(unit::tlength{} * unit::tlength{});
		constexpr tvector<unit::tlength, 3> vector{
				{unit::tlength{1}, unit::tlength{2}, unit::tlength{3}}};
		constexpr tresult result{14.};
		BOOST_CHECK_EQUAL(pow_sum<2>(vector) == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 3> vector{{1, 2, 3}};
		constexpr int result{36};
		BOOST_CHECK_EQUAL(pow_sum<3>(vector) == result, true);
	}

	{
		using tresult
				= decltype(unit::tlength{} * unit::tlength{} * unit::tlength{});
		static_assert(pow_sum<3>(tvector<unit::tlength, 3>{
							  {unit::tlength{1}, unit::tlength{2},
							   unit::tlength{3}}}) == tresult{36.},
					  "No compile-time constant");
	}

	{
		using tresult
				= decltype(unit::tlength{} * unit::tlength{} * unit::tlength{});
		constexpr tvector<unit::tlength, 3> vector{
				{unit::tlength{1}, unit::tlength{2}, unit::tlength{3}}};
		constexpr tresult result{36.};
		BOOST_CHECK_EQUAL(pow_sum<3>(vector) == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 3> vector{{1, 2, 3}};
		constexpr int result{98};
		BOOST_CHECK_EQUAL(pow_sum<4>(vector) == result, true);
	}

	{
		using tresult = decltype(unit::tlength{} * unit::tlength{}
								 * unit::tlength{} * unit::tlength{});
		static_assert(pow_sum<4>(tvector<unit::tlength, 3>{
							  {unit::tlength{1}, unit::tlength{2},
							   unit::tlength{3}}}) == tresult{98.},
					  "No compile-time constant");
	}

	{
		using tresult = decltype(unit::tlength{} * unit::tlength{}
								 * unit::tlength{} * unit::tlength{});
		constexpr tvector<unit::tlength, 3> vector{
				{unit::tlength{1}, unit::tlength{2}, unit::tlength{3}}};
		constexpr tresult result{98.};
		BOOST_CHECK_EQUAL(pow_sum<4>(vector) == result, true);
	}

	/************************************************************************/

	{
		constexpr tvector<int, 2> vector{{3, 4}};
		constexpr int result{5};
		BOOST_CHECK_EQUAL(length(vector) == result, true);
	}

	{
		constexpr tvector
				<unit::tlength, 2> vector{{unit::tlength{3}, unit::tlength{4}}};
		constexpr unit::tlength result{unit::tlength{5}};
		BOOST_CHECK_EQUAL(length(vector) == result, true);
	}

	/************************************************************************/
}
