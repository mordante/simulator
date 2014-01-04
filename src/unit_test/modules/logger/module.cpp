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

#include "modules/logger/module.hpp"

#include "modules/logger/logger.hpp"
#include "unit_test/exception.hpp"
#include "unit_test/pointer.tpp"

#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/logger")

using namespace logger;

static void constructor()
{
	TRACE;

	BOOST_CHECK_NO_THROW(tmodule{"x"});

	CHECK_EXCEPTION(tmodule{""}, internal_failure);
	CHECK_EXCEPTION(tmodule{"*"}, internal_failure);
	CHECK_EXCEPTION(tmodule{"//"}, internal_failure);
	CHECK_EXCEPTION(tmodule{"/*/"}, internal_failure);
	CHECK_EXCEPTION(tmodule{"/*"}, internal_failure);
}

static void find()
{
	TRACE;

	CHECK_POINTER(tmodule::find("/"));
	CHECK_POINTER(tmodule::find("/unit_test/modules/logger"));
	CHECK_NULL(tmodule::find("/no/such/module"));

	CHECK_EXCEPTION(tmodule::find(""), internal_failure);
	CHECK_EXCEPTION(tmodule::find("*"), internal_failure);
	CHECK_EXCEPTION(tmodule::find("//"), internal_failure);
	CHECK_EXCEPTION(tmodule::find("/*/"), internal_failure);
	CHECK_EXCEPTION(tmodule::find("/*"), internal_failure);
}

static void set_severity()
{
	TRACE;

	tmodule& m_1(register_logger_module("/unit_test/modules/logger/1"));
	tmodule& m_1_1(register_logger_module("/unit_test/modules/logger/1/1"));
	tmodule& m_1_2(register_logger_module("/unit_test/modules/logger/1/2"));
	tmodule& m_1_3(register_logger_module("/unit_test/modules/logger/1/3"));

	tmodule& m_2(register_logger_module("/unit_test/modules/logger/2"));
	tmodule& m_2_1(register_logger_module("/unit_test/modules/logger/2/1"));
	tmodule& m_2_2(register_logger_module("/unit_test/modules/logger/2/2"));

	tmodule& m_3(register_logger_module("/unit_test/modules/logger/3"));
	tmodule& m_3_1(register_logger_module("/unit_test/modules/logger/3/1"));


	/*
	 * Validate the defaults are as expected, else the test makes no sense.
	 */

	BOOST_REQUIRE_EQUAL(m_1.get_severity(), tseverity::warning);
	BOOST_REQUIRE_EQUAL(m_1_1.get_severity(), tseverity::warning);
	BOOST_REQUIRE_EQUAL(m_1_2.get_severity(), tseverity::warning);
	BOOST_REQUIRE_EQUAL(m_1_3.get_severity(), tseverity::warning);

	BOOST_REQUIRE_EQUAL(m_2.get_severity(), tseverity::warning);
	BOOST_REQUIRE_EQUAL(m_2_1.get_severity(), tseverity::warning);
	BOOST_REQUIRE_EQUAL(m_2_2.get_severity(), tseverity::warning);

	BOOST_REQUIRE_EQUAL(m_3.get_severity(), tseverity::warning);
	BOOST_REQUIRE_EQUAL(m_3_1.get_severity(), tseverity::warning);


	tmodule::set_severity("/unit_test/modules/logger/1/1", tseverity::error);

	BOOST_CHECK_EQUAL(m_1.get_severity(), tseverity::warning);
	BOOST_CHECK_EQUAL(m_1_1.get_severity(), tseverity::error);
	BOOST_CHECK_EQUAL(m_1_2.get_severity(), tseverity::warning);
	BOOST_CHECK_EQUAL(m_1_3.get_severity(), tseverity::warning);

	BOOST_CHECK_EQUAL(m_2.get_severity(), tseverity::warning);
	BOOST_CHECK_EQUAL(m_2_1.get_severity(), tseverity::warning);
	BOOST_CHECK_EQUAL(m_2_2.get_severity(), tseverity::warning);

	BOOST_CHECK_EQUAL(m_3.get_severity(), tseverity::warning);
	BOOST_CHECK_EQUAL(m_3_1.get_severity(), tseverity::warning);


	tmodule::set_severity("/unit_test/modules/logger/1*", tseverity::debug);

	BOOST_CHECK_EQUAL(m_1.get_severity(), tseverity::debug);
	BOOST_CHECK_EQUAL(m_1_1.get_severity(), tseverity::debug);
	BOOST_CHECK_EQUAL(m_1_2.get_severity(), tseverity::debug);
	BOOST_CHECK_EQUAL(m_1_3.get_severity(), tseverity::debug);

	BOOST_CHECK_EQUAL(m_2.get_severity(), tseverity::warning);
	BOOST_CHECK_EQUAL(m_2_1.get_severity(), tseverity::warning);
	BOOST_CHECK_EQUAL(m_2_2.get_severity(), tseverity::warning);

	BOOST_CHECK_EQUAL(m_3.get_severity(), tseverity::warning);
	BOOST_CHECK_EQUAL(m_3_1.get_severity(), tseverity::warning);


#if 0
	std::cerr << tmodule::tree();
#endif

	tmodule::set_severity("/*", tseverity::fatal);

	BOOST_CHECK_EQUAL(module().get_severity(), tseverity::fatal);

	BOOST_CHECK_EQUAL(m_1.get_severity(), tseverity::fatal);
	BOOST_CHECK_EQUAL(m_1_1.get_severity(), tseverity::fatal);
	BOOST_CHECK_EQUAL(m_1_2.get_severity(), tseverity::fatal);
	BOOST_CHECK_EQUAL(m_1_3.get_severity(), tseverity::fatal);

	BOOST_CHECK_EQUAL(m_2.get_severity(), tseverity::fatal);
	BOOST_CHECK_EQUAL(m_2_1.get_severity(), tseverity::fatal);
	BOOST_CHECK_EQUAL(m_2_2.get_severity(), tseverity::fatal);

	BOOST_CHECK_EQUAL(m_3.get_severity(), tseverity::fatal);
	BOOST_CHECK_EQUAL(m_3_1.get_severity(), tseverity::fatal);

	tmodule::set_severity("/*", tseverity::warning);


#if 0
	std::cerr << tmodule::tree();
#endif

	CHECK_EXCEPTION(tmodule::set_severity("", tseverity::debug),
					internal_failure);
	CHECK_EXCEPTION(tmodule::set_severity("*", tseverity::debug),
					internal_failure);
	CHECK_EXCEPTION(tmodule::set_severity("//", tseverity::debug),
					internal_failure);
	CHECK_EXCEPTION(tmodule::set_severity("/*/", tseverity::debug),
					internal_failure);
}

static void register_logger_module()
{
	TRACE;

	const tmodule& lhs{register_logger_module("/unit_test/modules/logger")};
	const tmodule& rhs{register_logger_module("/unit_test/modules/logger")};

	BOOST_CHECK_EQUAL(&lhs, &rhs);

	BOOST_CHECK_EQUAL(&(register_logger_module("/")), &(module()));

	CHECK_EXCEPTION(register_logger_module(""), internal_failure);
	CHECK_EXCEPTION(register_logger_module("*"), internal_failure);
	CHECK_EXCEPTION(register_logger_module("//"), internal_failure);
	CHECK_EXCEPTION(register_logger_module("/*/"), internal_failure);
	CHECK_EXCEPTION(register_logger_module("/*"), internal_failure);
}

BOOST_AUTO_TEST_CASE(test_modules_logger_module)
{
	TRACE;

	constructor();
	find();
	set_severity();
	register_logger_module();
}
