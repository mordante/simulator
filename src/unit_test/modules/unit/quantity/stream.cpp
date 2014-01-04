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

#include "modules/unit/quantity/stream.hpp"

#include "modules/logger/logger.hpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/unit")

using namespace unit;

template <class U>
static std::string stream()
{
	TRACE;

	std::stringstream sstr;
	sstr << tquantity<U, int>{1};
	return sstr.str();
}

BOOST_AUTO_TEST_CASE(test_modules_unit_stream)
{
	TRACE;

	BOOST_CHECK_EQUAL(stream<NONE>(), "1");

	BOOST_CHECK_EQUAL(stream<M>(), "1 m");
	BOOST_CHECK_EQUAL(stream<KG>(), "1 kg");
	BOOST_CHECK_EQUAL(stream<S>(), "1 s");
	BOOST_CHECK_EQUAL(stream<RAD>(), "1 rad");

	BOOST_CHECK_EQUAL(stream<N>(), "1 N");
	BOOST_CHECK_EQUAL(stream<J>(), "1 J");

	BOOST_CHECK_EQUAL((stream<tunit<-2, -1, 0, 1, 2>>()),
					  "1 m^-2 kg^-1 K rad^2");
}
