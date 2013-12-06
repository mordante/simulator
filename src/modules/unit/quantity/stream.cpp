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

#include "modules/unit/quantity/stream.hpp"

#include "modules/logger/logger.hpp"

REGISTER_LOGGER_MODULE("/modules/unit")

namespace unit
{

namespace detail
{

std::string stream_unit(const std::string& unit, const int count)
{
	TRACE_PARAMETERS(unit, count);

	std::string result;
	if(count == 0) {
		return result;
	}

	result += unit;

	if(count < 0 || count > 1) {
		result += "^" + std::to_string(count);
	}

	return result;
}

} // namespace detail

} // namespace unit
