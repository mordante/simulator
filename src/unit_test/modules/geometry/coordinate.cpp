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
	const tpolar result{unit::tlength{1.23}, unit::tangle{2.34},
						unit::tangle{3.45}};

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
	const tpolar input{unit::tlength{1.23}, unit::tangle{2.34},
					   unit::tangle{3.45}};
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
	const tpolar input{unit::tlength{1.23}, unit::tangle{2.34},
					   unit::tangle{3.45}};

	tpolar output{input};

	BOOST_REQUIRE_EQUAL(input, output);

	output.r = unit::tlength{3.141};
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);

	output.theta = unit::tangle{3.141};
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);

	output.phi = unit::tangle{3.141};
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void cartesian_load()
{
	const tcartesian result{unit::tlength{1.23}, unit::tlength{2.34},
							unit::tlength{3.45}};

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
	const tcartesian input{unit::tlength{1.23}, unit::tlength{2.34},
						   unit::tlength{3.45}};
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
		const tcartesian input{unit::tlength{0.}, unit::tlength{0.},
							   unit::tlength{0.}};
		const unit::tlength output{unit::tlength{0.}};
		BOOST_CHECK_EQUAL(input.length(), output);
	}

	{
		const tcartesian input{unit::tlength{1.}, unit::tlength{1.},
							   unit::tlength{1.}};
		const unit::tlength output{unit::tlength{std::sqrt(3.)}};
		BOOST_CHECK_EQUAL(input.length(), output);
	}

	{
		const tcartesian input{unit::tlength{2.}, unit::tlength{2.},
							   unit::tlength{2.}};
		const unit::tlength output{unit::tlength{std::sqrt(12.)}};
		BOOST_CHECK_EQUAL(input.length(), output);
	}

	{
		const tcartesian input{unit::tlength{-2.}, unit::tlength{-2.},
							   unit::tlength{-2.}};
		const unit::tlength output{unit::tlength{std::sqrt(12.)}};
		BOOST_CHECK_EQUAL(input.length(), output);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void cartesian_arithmetic()
{
	const tcartesian lhs{unit::tlength{1.25}, unit::tlength{2.50},
						 unit::tlength{3.75}};

	const tcartesian rhs{unit::tlength{5.00}, unit::tlength{6.25},
						 unit::tlength{7.50}};

	const tcartesian add{unit::tlength{6.25}, unit::tlength{8.75},
						 unit::tlength{11.25}};

	BOOST_CHECK_EQUAL(lhs + rhs, add);
	tcartesian add_tmp{lhs};
	BOOST_CHECK_EQUAL(add_tmp += rhs, add);


	const tcartesian sub{unit::tlength{-3.75}, unit::tlength{-3.75},
						 unit::tlength{-3.75}};

	BOOST_CHECK_EQUAL(lhs - rhs, sub);
	tcartesian sub_tmp{lhs};
	BOOST_CHECK_EQUAL(sub_tmp -= rhs, sub);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void cartesian_comparision()
{
	const tcartesian input{unit::tlength{1.23}, unit::tlength{2.34},
						   unit::tlength{3.45}};

	tcartesian output{input};

	BOOST_REQUIRE_EQUAL(input, output);

	output.x = unit::tlength{3.141};
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);

	output.y = unit::tlength{3.141};
	BOOST_REQUIRE_NE(input, output);
	output = input;
	BOOST_REQUIRE_EQUAL(input, output);

	output.z = unit::tlength{3.141};
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
	roundtrip(tcartesian{0._m, 0._m, 0._m});
	roundtrip(tcartesian{0._m, 0._m, 1._m});
	roundtrip(tcartesian{0._m, 1._m, 0._m});
	roundtrip(tcartesian{0._m, 1._m, 1._m});
	roundtrip(tcartesian{1._m, 0._m, 0._m});
	roundtrip(tcartesian{1._m, 0._m, 1._m});
	roundtrip(tcartesian{1._m, 0._m, 0._m});
	roundtrip(tcartesian{1._m, 1._m, 1._m});
	roundtrip(tcartesian{1._m, 1._m, 0._m});
	roundtrip(tcartesian{1._m, 1._m, 1._m});

	/* tpolar -> tcartesian -> tpolar */
	for(int r = 1; r < 10; ++r) {
		for(int theta = 0; theta <= 18; ++theta) {
			for(int phi = 1; phi <= 18; ++phi) {
				if(phi == 0 && theta != 0) {
					continue;
				}
				roundtrip(
						tpolar{1._m * static_cast<unit::tlength::type>(r),
							   10._deg * static_cast<unit::tangle::type>(theta),
							   10._deg * static_cast<unit::tangle::type>(phi)});
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
