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

#include "modules/grid/line.hpp"

#include "modules/grid/detail/optimised.hpp"
#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

REGISTER_LOGGER_MODULE("/modules/grid")

namespace grid
{

std::vector<tpoint> line(tpoint begin, tpoint end)
{
	TRACE_PARAMETERS(begin, end);

	return detail::line_optimised(begin, end);
}

} // namespace grid
