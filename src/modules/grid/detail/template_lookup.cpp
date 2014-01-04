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

#include "modules/grid/detail/template_lookup.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

#include <array>

REGISTER_LOGGER_MODULE("/modules/grid")

namespace grid
{

namespace detail
{

template <tint x_step, tint y_step, tint z_step>
static std::vector<tpoint> line(tpoint begin, tint dx, tint dy, tint dz)
{
	TRACE_PARAMETERS(begin, dx, dy, dz);

	std::vector<tpoint> result;

	dx *= x_step;
	dy *= y_step;
	dz *= z_step;

	tint steps = std::max({dx, dy, dz});

	tint x_correction{steps / 2};
	tint y_correction{steps / 2};
	tint z_correction{steps / 2};

	for(tint i{0}; i <= steps; ++i) {
		result.push_back(begin);

		x_correction -= dx;
		if(x_correction < 0) {
			x_correction += steps;
			begin.x += x_step;
		}

		y_correction -= dy;
		if(y_correction < 0) {
			y_correction += steps;
			begin.y += y_step;
		}

		z_correction -= dz;
		if(z_correction < 0) {
			z_correction += steps;
			begin.z += z_step;
		}
	}

	return result;
}

std::vector<tpoint> line_template_lookup(tpoint begin, tpoint end)
{
	TRACE_PARAMETERS(begin, end);

	tint x = end.x - begin.x;
	tint y = end.y - begin.y;
	tint z = end.z - begin.z;

	using tfunction = std::vector<tpoint>(*)(tpoint, tint, tint, tint);
	static constexpr std::array<tfunction, 8> functions{
			{line<-1, -1, -1>, line<-1, -1, 1>, line<-1, 1, -1>, line<-1, 1, 1>,
			 line<1, -1, -1>, line<1, -1, 1>, line<1, 1, -1>, line<1, 1, 1>}};

	const bool index_x{x >= 0};
	const bool index_y{y >= 0};
	const bool index_z{z >= 0};

	return functions[4 * index_x + 2 * index_y + index_z](begin, x, y, z);
}

} // namespace basic
} // namespace grid
