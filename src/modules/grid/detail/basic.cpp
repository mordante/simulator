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

#include "modules/grid/detail/basic.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

REGISTER_LOGGER_MODULE("/modules/grid")

namespace grid
{

namespace detail
{

static std::vector<tpoint>
line(tpoint begin, tint dx, tint dy, tint dz, bool px, bool py, bool pz)
{
	TRACE_PARAMETERS(begin, dx, dy, dz, px, py, pz);

	std::vector<tpoint> result;

	const tint x_step{px ? 1 : -1};
	const tint y_step{py ? 1 : -1};
	const tint z_step{pz ? 1 : -1};

	tint h_correction{dx / 2};
	tint v_correction{h_correction};

	for(tint i{0}; i <= dx; ++i) {
		result.push_back(begin);

		begin.x += x_step;

		h_correction -= dy;
		if(h_correction < 0) {
			h_correction += dx;
			begin.y += y_step;
		}

		v_correction -= dz;
		if(v_correction < 0) {
			v_correction += dx;
			begin.z += z_step;
		}
	}

	return result;
}

std::vector<tpoint> line_basic(tpoint begin, tpoint end)
{
	TRACE_PARAMETERS(begin, end);

	std::vector<tpoint> result;

	const tpoint delta{end.x - begin.x, end.y - begin.y, end.z - begin.z};

	const tint dx{std::abs(delta.x)};
	const tint dy{std::abs(delta.y)};
	const tint dz{std::abs(delta.z)};

	if(dx >= dy && dx >= dz) {
		result = line(
				begin, dx, dy, dz, delta.x >= 0, delta.y >= 0, delta.z >= 0);
	}

	return result;
}

} // namespace basic
} // namespace grid
