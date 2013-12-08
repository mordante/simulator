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

#ifndef UNIT_TEST_EXCEPTION_HPP_INCLUDED
#define UNIT_TEST_EXCEPTION_HPP_INCLUDED

/**
 * @file
 * Defines the helper functions for testing internal exceptions.
 */

#include "lib/exception/exception.hpp"

#include <functional>

bool exception_type_predicate(const lib::texception& exception,
							  const lib::texception::ttype type);

#define CHECK_EXCEPTION(CODE, TYPE)                                            \
	BOOST_CHECK_EXCEPTION(CODE,                                                \
						  lib::texception,                                     \
						  std::bind(exception_type_predicate,                  \
									std::placeholders::_1,                     \
									lib::texception::ttype::TYPE));

bool exception_type_predicate_message(const lib::texception& exception,
									  const lib::texception::ttype type,
									  const std::string& message);

#define CHECK_EXCEPTION_MESSAGE(CODE, TYPE, MESSAGE)                           \
	BOOST_CHECK_EXCEPTION(CODE,                                                \
						  lib::texception,                                     \
						  std::bind(exception_type_predicate_message,          \
									std::placeholders::_1,                     \
									lib::texception::ttype::TYPE,              \
									MESSAGE));
#endif
