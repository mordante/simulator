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

#include "modules/geometry/orbit.hpp"

#include "modules/geometry/cartesian.hpp"
#include "modules/geometry/stream.hpp"
#include "modules/unit/quantity/comparison.tpp"
#include "modules/unit/quantity/stream.hpp"
#include "unit_test/exception.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

using namespace geometry;

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void load()
{
	const torbit result{tpolar{1.23_m, 2.34_rad, 3.45_rad}, 4_s, 5_s};

	boost::property_tree::ptree rotation;
	rotation.put("version", "1");
	rotation.put("r", "1.23");
	rotation.put("theta", "2.34");
	rotation.put("phi", "3.45");

	boost::property_tree::ptree input;
	input.put("version", "1");
	input.push_back(
			boost::property_tree::ptree::value_type{"rotation", rotation});
	input.put("rotation_period_theta_plane", "4");
	input.put("rotation_period_phi_plane", "5");

	BOOST_CHECK_EQUAL(torbit::load(input).rotation, result.rotation);
	BOOST_CHECK_EQUAL(torbit::load(input).rotation_period_theta_plane,
					  result.rotation_period_theta_plane);
	BOOST_CHECK_EQUAL(torbit::load(input).rotation_period_phi_plane,
					  result.rotation_period_phi_plane);

	input.put("version", "100");
	CHECK_EXCEPTION_MESSAGE(
			torbit::load(input),
			load_invalid_version,
			"Failed to load an orbit object, version »100« is not supported.");
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void store()
{
	const torbit input{tpolar{1.23_m, 2.34_rad, 3.45_rad}, 4_s, 5_s};
	const boost::property_tree::ptree output{input.store()};

	BOOST_REQUIRE_EQUAL(output.size(), 4);

	auto itor = output.begin();
	BOOST_CHECK_EQUAL(itor->first, "version");
	BOOST_CHECK_EQUAL(itor->second.data(), "1");
	BOOST_CHECK_EQUAL((++itor)->first, "rotation");
	{
		BOOST_REQUIRE_EQUAL(itor->second.size(), 4);

		auto nested_itor = itor->second.begin();
		BOOST_CHECK_EQUAL(nested_itor->first, "version");
		BOOST_CHECK_EQUAL(nested_itor->second.data(), "1");
		BOOST_CHECK_EQUAL((++nested_itor)->first, "r");
		BOOST_CHECK_EQUAL(nested_itor->second.data(), "1.23");
		BOOST_CHECK_EQUAL((++nested_itor)->first, "theta");
		BOOST_CHECK_EQUAL(nested_itor->second.data(), "2.34");
		BOOST_CHECK_EQUAL((++nested_itor)->first, "phi");
		BOOST_CHECK_EQUAL(nested_itor->second.data(), "3.45");
	}
	BOOST_CHECK_EQUAL((++itor)->first, "rotation_period_theta_plane");
	BOOST_CHECK_EQUAL(itor->second.data(), "4");
	BOOST_CHECK_EQUAL((++itor)->first, "rotation_period_phi_plane");
	BOOST_CHECK_EQUAL(itor->second.data(), "5");
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void check(tcartesian lhs, tcartesian rhs, tcartesian delta)
{
	lhs -= rhs;

	BOOST_CHECK_LE(abs(lhs.x), delta.x);
	BOOST_CHECK_LE(abs(lhs.y), delta.y);
	BOOST_CHECK_LE(abs(lhs.z), delta.z);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void test_theta_plane()
{
	const tcartesian delta{1e-9_m, 1e-9_m, 1e-9_m};

	{
		torbit orbit{geometry::tpolar{1_m, 0_deg, 90_deg}, 36 * 36_s, 36_s};
		check(orbit.position(0_s), tcartesian{1_m, 0_m, 0_m}, delta);
	}

	for(int i = 0; i <= 36; ++i) {

		unit::tangle angle{10_deg};
		angle *= i;
		const tcartesian result{1.25_m * cos(angle), 1.25_m * sin(angle), 0_m};

		const torbit orbit{geometry::tpolar{1.25_m, 0_deg, 90_deg}, 36_s, 0_s};
		check(orbit.position(1_s * i), result, delta);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void test_phi_plane()
{
	const tcartesian delta{1e-9_m, 1e-9_m, 1e-9_m};

	for(int i = 0; i <= 72; ++i) {

		unit::tangle angle{10_deg};
		angle *= i;
		const tcartesian result{1.66_m * sin(angle), 0_m, 1.66_m * cos(angle)};

		const torbit orbit{geometry::tpolar{1.66_m, 0_deg, 0_deg}, 0_s, 36_s};
		check(orbit.position(1_s * i), result, delta);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void test_theta_and_phi_plane()
{
	const tcartesian delta{1e-9_m, 1e-9_m, 1e-9_m};

	for(int i = 0; i <= 360; ++i) {

		unit::tangle theta_angle{10_deg};
		theta_angle *= i;

		unit::tangle phi_angle{1_deg};
		phi_angle *= i;

		const tcartesian result{1_m * cos(theta_angle) * sin(phi_angle),
								1_m * sin(theta_angle) * sin(phi_angle),
								1_m * cos(phi_angle)};

		const torbit orbit{geometry::tpolar{1_m, 0_deg, 0_deg}, 36_s, 360_s};
		check(orbit.position(1_s * i), result, delta);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_geometry_orbit)
{
	test_theta_plane();
	test_phi_plane();
	test_theta_and_phi_plane();
	load();
	store();
}
