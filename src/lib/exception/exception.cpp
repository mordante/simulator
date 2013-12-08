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

#define ENUM_ENABLE_STREAM_OPERATORS_IMPLEMENTATION
#define ENUM_TYPE ::lib::texception::ttype
#define ENUM_LIST                                                              \
	ENUM(invalid_value, "E_INVALID_VALUE");                                    \
	ENUM(not_implemented_yet, "E_NOT_IMPLEMENTED");                            \
	ENUM(internal_failure, "E_INTERNAL_FAILURE");

#include "lib/exception/exception.hpp"

namespace lib
{

ENUM_DEFINE_STREAM_OPERATORS(ENUM_TYPE)

} // namespace lib
