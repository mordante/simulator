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

#include "modules/simulation/detail/moon.hpp"

#include "modules/unit/quantity/comparison.tpp"
#include "modules/unit/quantity/stream.hpp"
#include "unit_test/exception.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

using namespace simulation::detail;

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void load()
{
	const tmoon result{"moon", geometry::tcartesian{unit::tlength{1.23},
													unit::tlength{2.34},
													unit::tlength{3.45}}};

	boost::property_tree::ptree position;
	position.put("version", "1");
	position.put("x", "1.23");
	position.put("y", "2.34");
	position.put("z", "3.45");

	boost::property_tree::ptree input;
	input.put("version", "1");
	input.put("id", "moon");
	input.push_back(
			boost::property_tree::ptree::value_type{"position", position});

	BOOST_CHECK_EQUAL(tmoon::load(input).id, result.id);
	BOOST_CHECK_EQUAL(tmoon::load(input).position.x, result.position.x);
	BOOST_CHECK_EQUAL(tmoon::load(input).position.y, result.position.y);
	BOOST_CHECK_EQUAL(tmoon::load(input).position.z, result.position.z);

	input.put("version", "100");
	CHECK_EXCEPTION_MESSAGE(
			tmoon::load(input),
			load_invalid_version,
			"Failed to load a simulator moon object, version »100« "
			"is not supported.");
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

static void store()
{
	const tmoon input{"moon", geometry::tcartesian{unit::tlength{1.23},
												   unit::tlength{2.34},
												   unit::tlength{3.45}}};

	const boost::property_tree::ptree output{input.store()};

	BOOST_REQUIRE_EQUAL(output.size(), 3);

	auto itor = output.begin();
	BOOST_CHECK_EQUAL(itor->first, "version");
	BOOST_CHECK_EQUAL(itor->second.data(), "1");
	BOOST_CHECK_EQUAL((++itor)->first, "id");
	BOOST_CHECK_EQUAL(itor->second.data(), "moon");
	BOOST_CHECK_EQUAL((++itor)->first, "position");
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
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_simulation_moon)
{
	load();
	store();
}
