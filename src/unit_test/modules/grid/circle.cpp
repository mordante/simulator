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

#include "modules/grid/circle.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

#include <boost/test/unit_test.hpp>

#include <set>

REGISTER_LOGGER_MODULE("/unit_test/modules/grid")

using namespace grid;

static void test_circle_1(const tint radius)
{
	TRACE_PARAMETERS(radius);

	const std::vector<tpoint> unique{circle(radius, false)};
	const std::vector<tpoint> fast{circle_raw(radius)};

	BOOST_REQUIRE_LT(unique.size(), fast.size());

	std::set<tpoint> u;
	std::copy(unique.begin(), unique.end(), std::inserter(u, u.begin()));

	BOOST_CHECK_EQUAL(unique.size(), u.size());


	std::set<tpoint> f;
	std::copy(fast.begin(), fast.end(), std::inserter(f, f.begin()));

	BOOST_CHECK_LT(f.size(), fast.size());
	BOOST_CHECK_EQUAL(f.size(), u.size());
	BOOST_CHECK_EQUAL_COLLECTIONS(f.begin(), f.end(), u.begin(), u.end());
}

static void test_circle_1()
{
	TRACE;

	BOOST_CHECK_EQUAL(circle(0, false).size(), 0);

	for(tint i{1}; i < 42; ++i) {
		test_circle_1(i);
	}
}

BOOST_AUTO_TEST_CASE(test_modules_grid_circle)
{
	TRACE;

	test_circle_1();
}
