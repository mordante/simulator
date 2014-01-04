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

#ifdef ENABLE_TRACE_LOGGER
#define ENUM_TRACE ENUM(trace, "trace");
#else
#define ENUM_TRACE
#endif

#define ENUM_ENABLE_STREAM_OPERATORS_IMPLEMENTATION
#define ENUM_TYPE ::logger::tseverity
#define ENUM_LIST                                                              \
	ENUM(fatal, "fatal");                                                      \
	ENUM(error, "error");                                                      \
	ENUM(warning, "warning");                                                  \
	ENUM(information, "information");                                          \
	ENUM(debug, "debug");                                                      \
	ENUM_TRACE

#include "modules/logger/severity.hpp"

namespace logger
{

ENUM_DEFINE_STREAM_OPERATORS(::logger::tseverity)
}
