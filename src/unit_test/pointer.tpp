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

#ifndef UNIT_TEST_POINTER_HPP_INCLUDED
#define UNIT_TEST_POINTER_HPP_INCLUDED

/**
 * @file
 * Defines the helper functions for testing pointers.
 */

#define CHECK_POINTER(CODE) BOOST_CHECK_NE(CODE, static_cast<void*>(nullptr))
#define CHECK_NULL(CODE) BOOST_CHECK_EQUAL(CODE, static_cast<void*>(nullptr))

#endif
