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

#include "modules/celestial/sun.hpp"

#include "modules/geometry/stream.hpp"
#include "modules/unit/quantity/comparison.tpp"
#include "modules/unit/quantity/stream.hpp"
#include "unit_test/exception.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

using namespace celestial;

struct tunit_test
{
	/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

	static void load()
	{
		const tsun result{
				"sun", geometry::tcartesian{1.23_m, 2.34_m, 3.45_m},
				geometry::torbit{geometry::tpolar{4.56_m, 5.67_rad, 6.78_rad},
								 7_s, 8_s},
				9.10_m, 10.11_J};

		boost::property_tree::ptree origin;
		origin.put("version", "1");
		origin.put("x", "1.23");
		origin.put("y", "2.34");
		origin.put("z", "3.45");

		boost::property_tree::ptree rotation;
		rotation.put("version", "1");
		rotation.put("r", "4.56");
		rotation.put("theta", "5.67");
		rotation.put("phi", "6.78");

		boost::property_tree::ptree orbit;
		orbit.put("version", "1");
		orbit.push_back(
				boost::property_tree::ptree::value_type{"rotation", rotation});
		orbit.put("rotation_period_theta_plane", "7");
		orbit.put("rotation_period_phi_plane", "8");

		boost::property_tree::ptree input;
		input.put("version", "1");
		input.put("id", "sun");
		input.push_back(
				boost::property_tree::ptree::value_type{"origin", origin});
		input.push_back(
				boost::property_tree::ptree::value_type{"orbit", orbit});
		input.put("radius", "9.10");
		input.put("energy_output", "10.11");

		BOOST_CHECK_EQUAL(tsun::load(input).id_, result.id_);
		BOOST_CHECK_EQUAL(tsun::load(input).origin_.x, result.origin_.x);
		BOOST_CHECK_EQUAL(tsun::load(input).origin_.y, result.origin_.y);
		BOOST_CHECK_EQUAL(tsun::load(input).origin_.z, result.origin_.z);
		BOOST_CHECK_EQUAL(tsun::load(input).orbit_.rotation,
						  result.orbit_.rotation);
		BOOST_CHECK_EQUAL(tsun::load(input).orbit_.rotation_period_theta_plane,
						  result.orbit_.rotation_period_theta_plane);
		BOOST_CHECK_EQUAL(tsun::load(input).orbit_.rotation_period_phi_plane,
						  result.orbit_.rotation_period_phi_plane);
		BOOST_CHECK_EQUAL(tsun::load(input).radius_, result.radius_);
		BOOST_CHECK_EQUAL(tsun::load(input).energy_output_,
						  result.energy_output_);

		input.put("version", "100");
		CHECK_EXCEPTION_MESSAGE(tsun::load(input),
								load_invalid_version,
								"Failed to load a sun object, version »100« "
								"is not supported.");
	}

	/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

	static void store()

	{
		const tsun input{
				"sun", geometry::tcartesian{1.23_m, 2.34_m, 3.45_m},
				geometry::torbit{geometry::tpolar{4.56_m, 5.67_rad, 6.78_rad},
								 7_s, 8_s},
				9.10_m, 10.11_J};

		const boost::property_tree::ptree output{input.store()};

		BOOST_REQUIRE_EQUAL(output.size(), 6);

		auto itor = output.begin();
		BOOST_CHECK_EQUAL(itor->first, "version");
		BOOST_CHECK_EQUAL(itor->second.data(), "1");
		BOOST_CHECK_EQUAL((++itor)->first, "id");
		BOOST_CHECK_EQUAL(itor->second.data(), "sun");
		BOOST_CHECK_EQUAL((++itor)->first, "origin");
		{
			BOOST_REQUIRE_EQUAL(itor->second.size(), 4);

			auto nested_itor = itor->second.begin();
			BOOST_CHECK_EQUAL(nested_itor->first, "version");
			BOOST_CHECK_EQUAL(nested_itor->second.data(), "1");
			BOOST_CHECK_EQUAL((++nested_itor)->first, "x");
			BOOST_CHECK_EQUAL(nested_itor->second.data(), "1.23");
			BOOST_CHECK_EQUAL((++nested_itor)->first, "y");
			BOOST_CHECK_EQUAL(nested_itor->second.data(), "2.34");
			BOOST_CHECK_EQUAL((++nested_itor)->first, "z");
			BOOST_CHECK_EQUAL(nested_itor->second.data(), "3.45");
		}
		BOOST_CHECK_EQUAL((++itor)->first, "orbit");
		{
			BOOST_REQUIRE_EQUAL(itor->second.size(), 4);

			auto nested_itor = itor->second.begin();
			BOOST_CHECK_EQUAL(nested_itor->first, "version");
			BOOST_CHECK_EQUAL(nested_itor->second.data(), "1");
			BOOST_CHECK_EQUAL((++nested_itor)->first, "rotation");
			{
				BOOST_REQUIRE_EQUAL(nested_itor->second.size(), 4);

				auto nested_nested_itor = nested_itor->second.begin();
				BOOST_CHECK_EQUAL(nested_nested_itor->first, "version");
				BOOST_CHECK_EQUAL(nested_nested_itor->second.data(), "1");
				BOOST_CHECK_EQUAL((++nested_nested_itor)->first, "r");
				BOOST_CHECK_EQUAL(nested_nested_itor->second.data(), "4.56");
				BOOST_CHECK_EQUAL((++nested_nested_itor)->first, "theta");
				BOOST_CHECK_EQUAL(nested_nested_itor->second.data(), "5.67");
				BOOST_CHECK_EQUAL((++nested_nested_itor)->first, "phi");
				BOOST_CHECK_EQUAL(nested_nested_itor->second.data(), "6.78");
			}
			BOOST_CHECK_EQUAL((++nested_itor)->first,
							  "rotation_period_theta_plane");
			BOOST_CHECK_EQUAL(nested_itor->second.data(), "7");
			BOOST_CHECK_EQUAL((++nested_itor)->first,
							  "rotation_period_phi_plane");
			BOOST_CHECK_EQUAL(nested_itor->second.data(), "8");
		}
		BOOST_CHECK_EQUAL((++itor)->first, "radius");
		BOOST_CHECK_EQUAL(itor->second.data(), "9.1");
		BOOST_CHECK_EQUAL((++itor)->first, "energy_output");
		BOOST_CHECK_EQUAL(itor->second.data(), "10.11");
	}
};

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_celestial_sun)
{
	tunit_test::load();
	tunit_test::store();
}
