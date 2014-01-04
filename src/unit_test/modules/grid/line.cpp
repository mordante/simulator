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

#include "modules/grid/line.hpp"
#include "modules/grid/detail/basic.hpp"
#include "modules/grid/detail/template_multiplex.hpp"
#include "modules/grid/detail/template_lookup.hpp"
#include "modules/grid/detail/optimised.hpp"
#include "modules/grid/detail/vector.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/grid")

using namespace grid;

static void neg_x(tpoint& point)
{
	TRACE_PARAMETERS(point);

	point.x = -point.x;
}

static void neg_y(tpoint& point)
{
	TRACE_PARAMETERS(point);

	point.y = -point.y;
}

static void neg_z(tpoint& point)
{
	TRACE_PARAMETERS(point);

	point.z = -point.z;
}

static void rotate(tpoint& point)
{
	TRACE_PARAMETERS(point);

	const tpoint original = point;
	point.x = original.y;
	point.y = original.z;
	point.z = original.x;
}

static void permuate(std::function<void(tpoint&)> functor,
					 tpoint& begin,
					 tpoint& end,
					 std::vector<tpoint>& expected)
{
	TRACE_PARAMETERS(begin, end);

	functor(begin);
	functor(end);
	for(auto& point : expected) {
		functor(point);
	}
}

static void
validate(const std::vector<tpoint>& expected, const std::vector<tpoint>& result)
{
	TRACE;

	BOOST_REQUIRE_EQUAL(result.size(), expected.size());

	for(size_t i = 0; i < result.size(); ++i) {
		BOOST_CHECK_EQUAL(result[i], expected[i]);
	}

	BOOST_CHECK_EQUAL_COLLECTIONS(
			result.begin(), result.end(), expected.begin(), expected.end());
}

static void test_implementations(const bool test_basic,
								 const tpoint& begin,
								 const tpoint& end,
								 const std::vector<tpoint>& expected)
{
	TRACE_PARAMETERS(test_basic, begin, end);

	validate(expected, line(begin, end));
	if(test_basic) {
		validate(expected, detail::line_basic(begin, end));
	}
	validate(expected, detail::line_template_multiplex(begin, end));
	validate(expected, detail::line_template_lookup(begin, end));
	validate(expected, detail::line_optimised(begin, end));
	validate(expected, detail::line_vector(begin, end));
}

static void test(const bool test_basic,
				 tpoint begin,
				 tpoint end,
				 std::vector<tpoint> expected)
{
	TRACE_PARAMETERS(test_basic, begin, end);

	{ // X = X, Y = Y, Z = Z
		test_implementations(test_basic, begin, end, expected);
	}

	{ // X = X, Y = Y, Z = -Z
		permuate(neg_z, begin, end, expected);
		test_implementations(test_basic, begin, end, expected);
		permuate(neg_z, begin, end, expected);
	}

	{ // X = X, Y = -Y, Z = Z
		permuate(neg_y, begin, end, expected);
		test_implementations(test_basic, begin, end, expected);
		permuate(neg_y, begin, end, expected);
	}

	{ // X = X, Y = -Y, Z = -Z
		permuate(neg_z, begin, end, expected);
		permuate(neg_y, begin, end, expected);
		test_implementations(test_basic, begin, end, expected);
		permuate(neg_y, begin, end, expected);
		permuate(neg_z, begin, end, expected);
	}

	{ // X = -X, Y = Y, Z = Z
		permuate(neg_x, begin, end, expected);
		test_implementations(test_basic, begin, end, expected);
		permuate(neg_x, begin, end, expected);
	}

	{ // X = -X, Y = Y, Z = -Z
		permuate(neg_z, begin, end, expected);
		permuate(neg_x, begin, end, expected);
		test_implementations(test_basic, begin, end, expected);
		permuate(neg_x, begin, end, expected);
		permuate(neg_z, begin, end, expected);
	}

	{ // X = -X, Y = -Y, Z = Z
		permuate(neg_y, begin, end, expected);
		permuate(neg_x, begin, end, expected);
		test_implementations(test_basic, begin, end, expected);
		permuate(neg_x, begin, end, expected);
		permuate(neg_y, begin, end, expected);
	}

	{ // X = -X, Y = -Y, Z = -Z
		permuate(neg_z, begin, end, expected);
		permuate(neg_y, begin, end, expected);
		permuate(neg_x, begin, end, expected);
		test_implementations(test_basic, begin, end, expected);
		permuate(neg_x, begin, end, expected);
		permuate(neg_y, begin, end, expected);
		permuate(neg_z, begin, end, expected);
	}
}

static void test(tpoint begin, tpoint end, std::vector<tpoint> expected)
{
	TRACE_PARAMETERS(begin, end);

	{ // X = X, Y = Y, Z = Z
		test(true, begin, end, expected);
	}

	{ // X = Y, Y = Z, Z = X
		permuate(rotate, begin, end, expected);
		test(false, begin, end, expected);
	}

	{ // X = Z, Y = X, Z = Y
		permuate(rotate, begin, end, expected);
		test(false, begin, end, expected);
	}
}

static void test_line()
{
	TRACE;

	test(tpoint{0, 0, 0},
		 tpoint{0, 0, 0},
		 std::vector<tpoint>{tpoint{0, 0, 0}});


	test(tpoint{0, 0, 0},
		 tpoint{1, 1, 1},
		 std::vector<tpoint>{tpoint{0, 0, 0}, tpoint{1, 1, 1}});

	test(tpoint{0, 0, 0},
		 tpoint{4, 1, 1},
		 std::vector<tpoint>{tpoint{0, 0, 0}, tpoint{1, 0, 0}, tpoint{2, 0, 0},
							 tpoint{3, 1, 1}, tpoint{4, 1, 1}});

	test(tpoint{0, 0, 0},
		 tpoint{4, 2, 1},
		 std::vector<tpoint>{tpoint{0, 0, 0}, tpoint{1, 0, 0}, tpoint{2, 1, 0},
							 tpoint{3, 1, 1}, tpoint{4, 2, 1}});


	test(tpoint{1, 1, 1},
		 tpoint{0, 0, 0},
		 std::vector<tpoint>{tpoint{1, 1, 1}, tpoint{0, 0, 0}});

	test(tpoint{4, 1, 1},
		 tpoint{0, 0, 0},
		 std::vector<tpoint>{tpoint{4, 1, 1}, tpoint{3, 1, 1}, tpoint{2, 1, 1},
							 tpoint{1, 0, 0}, tpoint{0, 0, 0}});

	test(tpoint{4, 2, 1},
		 tpoint{0, 0, 0},
		 std::vector<tpoint>{tpoint{4, 2, 1}, tpoint{3, 2, 1}, tpoint{2, 1, 1},
							 tpoint{1, 1, 0}, tpoint{0, 0, 0}});
}

BOOST_AUTO_TEST_CASE(test_modules_grid_line)
{
	TRACE;

	test_line();
}
