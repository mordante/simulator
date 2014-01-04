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

#include "modules/geometry/cartesian.hpp"
#include "modules/geometry/polar.hpp"

#include "modules/geometry/stream.hpp"
#include "modules/unit/quantity/arithmetic.tpp"
#include "modules/unit/quantity/comparison.tpp"
#include "modules/unit/quantity/stream.hpp"
#include "unit_test/exception.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

using namespace geometry;

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void polar_load()
{
	const tpolar result{1.23_m, 2.34_rad, 3.45_rad};

	boost::property_tree::ptree input;
	input.put("version", "1");
	input.put("r", "1.23");
	input.put("theta", "2.34");
	input.put("phi", "3.45");

	BOOST_CHECK_EQUAL(tpolar::load(input), result);

	input.put("version", "100");
	CHECK_EXCEPTION_MESSAGE(
			tpolar::load(input),
			load_invalid_version,
			"Failed to load a polar object, version »100« is not supported.");
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void polar_store()
{
	const tpolar input{1.23_m, 2.34_rad, 3.45_rad};
	const boost::property_tree::ptree output{input.store()};

	BOOST_REQUIRE_EQUAL(output.size(), 4);

	auto itor = output.begin();
	BOOST_CHECK_EQUAL(itor->first, "version");
	BOOST_CHECK_EQUAL(itor->second.data(), "1");
	BOOST_CHECK_EQUAL((++itor)->first, "r");
	BOOST_CHECK_EQUAL(itor->second.data(), "1.23");
	BOOST_CHECK_EQUAL((++itor)->first, "theta");
	BOOST_CHECK_EQUAL(itor->second.data(), "2.34");
	BOOST_CHECK_EQUAL((++itor)->first, "phi");
	BOOST_CHECK_EQUAL(itor->second.data(), "3.45");
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void polar_comparision()
{
	const tpolar input{1.23_m, 2.34_rad, 3.45_rad};

	tpolar output{input};

	BOOST_REQUIRE_EQUAL(input, output);

	output.r = 3.141_m;
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);

	output.theta = 3.141_rad;
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);

	output.phi = 3.141_rad;
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void cartesian_load()
{
	const tcartesian result{1.23_m, 2.34_m, 3.45_m};

	boost::property_tree::ptree input;
	input.put("version", "1");
	input.put("x", "1.23");
	input.put("y", "2.34");
	input.put("z", "3.45");

	BOOST_CHECK_EQUAL(tcartesian::load(input), result);

	input.put("version", "100");
	CHECK_EXCEPTION_MESSAGE(tcartesian::load(input),
							load_invalid_version,
							"Failed to load a cartesian object, version »100« "
							"is not supported.");
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void cartesian_store()
{
	const tcartesian input{1.23_m, 2.34_m, 3.45_m};
	const boost::property_tree::ptree output{input.store()};

	BOOST_REQUIRE_EQUAL(output.size(), 4);

	auto itor = output.begin();
	BOOST_CHECK_EQUAL(itor->first, "version");
	BOOST_CHECK_EQUAL(itor->second.data(), "1");
	BOOST_CHECK_EQUAL((++itor)->first, "x");
	BOOST_CHECK_EQUAL(itor->second.data(), "1.23");
	BOOST_CHECK_EQUAL((++itor)->first, "y");
	BOOST_CHECK_EQUAL(itor->second.data(), "2.34");
	BOOST_CHECK_EQUAL((++itor)->first, "z");
	BOOST_CHECK_EQUAL(itor->second.data(), "3.45");
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void cartesian_length()
{
	{
		const tcartesian input{0_m, 0_m, 0_m};
		const unit::tlength output{0_m};
		BOOST_CHECK_EQUAL(input.length(), output);
	}

	{
		const tcartesian input{1_m, 1_m, 1_m};
		const unit::tlength output{unit::tlength{std::sqrt(3.)}};
		BOOST_CHECK_EQUAL(input.length(), output);
	}

	{
		const tcartesian input{2_m, 2_m, 2_m};
		const unit::tlength output{unit::tlength{std::sqrt(12.)}};
		BOOST_CHECK_EQUAL(input.length(), output);
	}

	{
		const tcartesian input{-2_m, -2_m, -2_m};
		const unit::tlength output{unit::tlength{std::sqrt(12.)}};
		BOOST_CHECK_EQUAL(input.length(), output);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void cartesian_arithmetic()
{
	const tcartesian lhs{1.25_m, 2.50_m, 3.75_m};

	const tcartesian rhs{5.00_m, 6.25_m, 7.50_m};

	const tcartesian add{6.25_m, 8.75_m, 11.25_m};

	BOOST_CHECK_EQUAL(lhs + rhs, add);
	tcartesian add_tmp{lhs};
	BOOST_CHECK_EQUAL(add_tmp += rhs, add);


	const tcartesian sub{-3.75_m, -3.75_m, -3.75_m};

	BOOST_CHECK_EQUAL(lhs - rhs, sub);
	tcartesian sub_tmp{lhs};
	BOOST_CHECK_EQUAL(sub_tmp -= rhs, sub);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void cartesian_comparision()
{
	const tcartesian input{1.23_m, 2.34_m, 3.45_m};

	tcartesian output{input};

	BOOST_REQUIRE_EQUAL(input, output);

	output.x = 3.141_m;
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);

	output.y = 3.141_m;
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);

	output.z = 3.141_m;
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void roundtrip(tcartesian original)
{
	tcartesian result{static_cast<tcartesian>(static_cast<tpolar>(original))};

	BOOST_CHECK_LE(abs(original.x - result.x), 1e-9_m);
	BOOST_CHECK_LE(abs(original.y - result.y), 1e-9_m);
	BOOST_CHECK_LE(abs(original.z - result.z), 1e-9_m);
}

static void roundtrip(tpolar original)
{
	tpolar result{static_cast<tpolar>(static_cast<tcartesian>(original))};

	BOOST_CHECK_LE(abs(original.r - result.r), 1e-9_m);
	BOOST_CHECK_LE(abs(original.theta - result.theta), 1e-9_rad);
	BOOST_CHECK_LE(abs(original.phi - result.phi), 1e-9_rad);
}

static void roundtrip()
{
	/* tcartesian -> tpolar -> tcartesian */
	roundtrip(tcartesian{0_m, 0_m, 0_m});
	roundtrip(tcartesian{0_m, 0_m, 1_m});
	roundtrip(tcartesian{0_m, 1_m, 0_m});
	roundtrip(tcartesian{0_m, 1_m, 1_m});
	roundtrip(tcartesian{1_m, 0_m, 0_m});
	roundtrip(tcartesian{1_m, 0_m, 1_m});
	roundtrip(tcartesian{1_m, 0_m, 0_m});
	roundtrip(tcartesian{1_m, 1_m, 1_m});
	roundtrip(tcartesian{1_m, 1_m, 0_m});
	roundtrip(tcartesian{1_m, 1_m, 1_m});

	/* tpolar -> tcartesian -> tpolar */
	for(int r = 1; r < 10; ++r) {
		for(int theta = 0; theta <= 18; ++theta) {
			for(int phi = 1; phi <= 18; ++phi) {
				if(phi == 0 && theta != 0) {
					continue;
				}
				roundtrip(
						tpolar{1_m * static_cast<unit::tlength::type>(r),
							   10_deg * static_cast<unit::tangle::type>(theta),
							   10_deg * static_cast<unit::tangle::type>(phi)});
			}
		}
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_geometry_coordinate)
{
	polar_load();
	polar_store();
	polar_comparision();

	cartesian_load();
	cartesian_store();
	cartesian_length();
	cartesian_arithmetic();
	cartesian_comparision();

	roundtrip();
}
