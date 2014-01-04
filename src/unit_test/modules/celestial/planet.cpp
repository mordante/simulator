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

#include "modules/celestial/planet.hpp"

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
		const tplanet result{
				"planet", geometry::tcartesian{1.23_m, 2.34_m, 3.45_m},
				4.56_m,   5.67_m};

		boost::property_tree::ptree origin;
		origin.put("version", "1");
		origin.put("x", "1.23");
		origin.put("y", "2.34");
		origin.put("z", "3.45");

		boost::property_tree::ptree input;
		input.put("version", "1");
		input.put("id", "planet");
		input.push_back(
				boost::property_tree::ptree::value_type{"origin", origin});
		input.put("length", "3.56");
		input.put("width", "4.67");

		BOOST_CHECK_EQUAL(tplanet::load(input).id_, result.id_);
		BOOST_CHECK_EQUAL(tplanet::load(input).origin_.x, result.origin_.x);
		BOOST_CHECK_EQUAL(tplanet::load(input).origin_.y, result.origin_.y);
		BOOST_CHECK_EQUAL(tplanet::load(input).origin_.z, result.origin_.z);
		BOOST_CHECK_EQUAL(tplanet::load(input).length_, result.length_);
		BOOST_CHECK_EQUAL(tplanet::load(input).width_, result.width_);

		input.put("version", "100");
		CHECK_EXCEPTION_MESSAGE(tplanet::load(input),
								load_invalid_version,
								"Failed to load a planet object, version »100« "
								"is not supported.");
	}

	/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

	static void store()
	{
		const tplanet input{
				"planet", geometry::tcartesian{1.23_m, 2.34_m, 3.45_m},
				4.56_m,   5.67_m};

		const boost::property_tree::ptree output{input.store()};

		BOOST_REQUIRE_EQUAL(output.size(), 5);

		auto itor = output.begin();
		BOOST_CHECK_EQUAL(itor->first, "version");
		BOOST_CHECK_EQUAL(itor->second.data(), "1");
		BOOST_CHECK_EQUAL((++itor)->first, "id");
		BOOST_CHECK_EQUAL(itor->second.data(), "planet");
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
		BOOST_CHECK_EQUAL((++itor)->first, "length");
		BOOST_CHECK_EQUAL(itor->second.data(), "4.56");
		BOOST_CHECK_EQUAL((++itor)->first, "width");
		BOOST_CHECK_EQUAL(itor->second.data(), "5.67");
	}
};

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_celestial_planet)
{
	tunit_test::load();
	tunit_test::store();
}
