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

#include "lib/utility/concatenate.tpp"

#include "modules/logger/logger.hpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/lib/utility")

static void stream()
{
	TRACE;

	std::stringstream sstr;

	lib::stream(sstr, "abc");
	BOOST_CHECK_EQUAL(sstr.str(), "abc");
	sstr.str("");

	lib::stream(sstr, 42);
	BOOST_CHECK_EQUAL(sstr.str(), "42");
	sstr.str("");

	lib::stream(sstr, 3.141);
	BOOST_CHECK_EQUAL(sstr.str(), "3.141");
	sstr.str("");

	lib::stream(sstr, "abc", 42, 3.141);
	BOOST_CHECK_EQUAL(sstr.str(), "abc423.141");
	sstr.str("");
}

static void concatenate()
{
	TRACE;

	BOOST_CHECK_EQUAL(lib::concatenate("abc"), "abc");
	BOOST_CHECK_EQUAL(lib::concatenate(42), "42");
	BOOST_CHECK_EQUAL(lib::concatenate(3.141), "3.141");

	BOOST_CHECK_EQUAL(lib::concatenate("abc", 42, 3.141), "abc423.141");
}

BOOST_AUTO_TEST_CASE(test_lib_utility_concatenate)
{
	TRACE;

	stream();
	concatenate();
}
