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

#include "modules/grid/point.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/grid")

using namespace grid;

static void test_ctor()
{
	TRACE;

	const tpoint input{1, 2, 3};

	BOOST_CHECK_EQUAL(input.x, 1);
	BOOST_CHECK_EQUAL(input.y, 2);
	BOOST_CHECK_EQUAL(input.z, 3);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void test_comparison()
{
	TRACE;

	{
		const tpoint input{1, 2, 3};
		BOOST_CHECK_EQUAL((input == input), true);
	}

	{
		const tpoint input{1, 2, 3};
		BOOST_CHECK_EQUAL((input != tpoint{9, 2, 3}), true);
		BOOST_CHECK_EQUAL((input != tpoint{1, 9, 3}), true);
		BOOST_CHECK_EQUAL((input != tpoint{1, 2, 9}), true);
	}

	{
		const tpoint input{1, 2, 3};
		BOOST_CHECK_EQUAL((input < tpoint{2, 2, 3}), true);
		BOOST_CHECK_EQUAL((input < tpoint{1, 3, 3}), true);
		BOOST_CHECK_EQUAL((input < tpoint{1, 2, 4}), true);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void test_arithmetic()
{
	TRACE;

	{
		tpoint input{1, 2, 3};
		input += tpoint{1, 2, 3};
		BOOST_CHECK_EQUAL(input, (tpoint{2, 4, 6}));
	}

	{
		std::vector<tpoint> input{tpoint{1, 2, 3}, tpoint{2, 3, 4},
								  tpoint{3, 4, 5}, tpoint{4, 5, 6},
								  tpoint{5, 6, 7}};
		input += tpoint{1, 2, 3};
		BOOST_CHECK_EQUAL(input[0], (tpoint{2, 4, 6}));
		BOOST_CHECK_EQUAL(input[1], (tpoint{3, 5, 7}));
		BOOST_CHECK_EQUAL(input[2], (tpoint{4, 6, 8}));
		BOOST_CHECK_EQUAL(input[3], (tpoint{5, 7, 9}));
		BOOST_CHECK_EQUAL(input[4], (tpoint{6, 8, 10}));
	}

	{
		{
			BOOST_CHECK_EQUAL((tpoint { 1, 2, 3 } + tpoint{1, 2, 3}),
							  (tpoint{2, 4, 6}));
		}
	}

	{
		const std::vector<tpoint> input{tpoint{1, 2, 3}, tpoint{2, 3, 4},
										tpoint{3, 4, 5}, tpoint{4, 5, 6},
										tpoint{5, 6, 7}};

		const std::vector<tpoint> output{input + tpoint{1, 2, 3}};
		BOOST_CHECK_EQUAL(output[0], (tpoint{2, 4, 6}));
		BOOST_CHECK_EQUAL(output[1], (tpoint{3, 5, 7}));
		BOOST_CHECK_EQUAL(output[2], (tpoint{4, 6, 8}));
		BOOST_CHECK_EQUAL(output[3], (tpoint{5, 7, 9}));
		BOOST_CHECK_EQUAL(output[4], (tpoint{6, 8, 10}));
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void test_intersection()
{
	TRACE;

	const std::vector<tpoint> lhs{tpoint{1, 2, 3}, tpoint{2, 3, 4},
								  tpoint{3, 4, 5}, tpoint{4, 5, 6},
								  tpoint{5, 6, 7}};

	const std::vector<tpoint> zero_matches{tpoint{2, 2, 3}, tpoint{3, 3, 4},
										   tpoint{4, 4, 5}, tpoint{5, 5, 6},
										   tpoint{6, 6, 7}};

	const std::vector<tpoint> one_match{tpoint{2, 2, 3}, tpoint{3, 3, 4},
										tpoint{3, 4, 5}, tpoint{5, 5, 6},
										tpoint{6, 6, 7}};

	const std::vector<tpoint> two_matches{tpoint{2, 2, 3}, tpoint{2, 3, 4},
										  tpoint{4, 4, 5}, tpoint{4, 5, 6},
										  tpoint{6, 6, 7}};

	BOOST_CHECK_EQUAL(intersects(lhs, zero_matches), false);
	BOOST_CHECK_EQUAL(intersects(lhs, one_match), true);
	BOOST_CHECK_EQUAL(intersects(lhs, two_matches), true);

	{
		const std::vector<tpoint> result = intersection(lhs, zero_matches);

		BOOST_REQUIRE_EQUAL(result.empty(), true);
	}

	{
		const std::vector<tpoint> result = intersection(lhs, one_match);
		const std::vector<tpoint> match{tpoint{3, 4, 5}};

		BOOST_REQUIRE_EQUAL(result.size(), 1);
		BOOST_CHECK_EQUAL(result[0], match[0]);
	}

	{
		const std::vector<tpoint> result = intersection(lhs, two_matches);
		const std::vector<tpoint> match{tpoint{2, 3, 4}, tpoint{4, 5, 6}};

		BOOST_REQUIRE_EQUAL(result.size(), 2);
		BOOST_CHECK_EQUAL(result[0], match[0]);
		BOOST_CHECK_EQUAL(result[1], match[1]);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_grid_point)
{
	TRACE;

	test_ctor();
	test_comparison();
	test_arithmetic();
	test_intersection();
}
