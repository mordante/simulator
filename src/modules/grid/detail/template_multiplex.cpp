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

#include "modules/grid/detail/template_multiplex.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

REGISTER_LOGGER_MODULE("/modules/grid")

namespace grid
{

namespace detail
{

template <tint x_step, tint y_step, tint z_step>
static std::vector<tpoint>
line(tpoint begin, tint steps, tint dx, tint dy, tint dz)
{
	TRACE_PARAMETERS(begin, steps, dx, dy, dz);

	std::vector<tpoint> result;

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

std::vector<tpoint> line_template_multiplex(tpoint begin, tpoint end)
{
	TRACE_PARAMETERS(begin, end);

	tint x{end.x - begin.x};
	tint y{end.y - begin.y};
	tint z{end.z - begin.z};

	if(x >= 0) {
		if(y >= 0) {
			if(z >= 0) {
				return line<1, 1, 1>(begin, std::max({x, y, z}), x, y, z);
			} else {
				z = -z;
				return line<1, 1, -1>(begin, std::max({x, y, z}), x, y, z);
			}
		} else {
			y = -y;
			if(z >= 0) {
				return line<1, -1, 1>(begin, std::max({x, y, z}), x, y, z);
			} else {
				z = -z;
				return line<1, -1, -1>(begin, std::max({x, y, z}), x, y, z);
			}
		}
	} else {
		x = -x;
		if(y >= 0) {
			if(z >= 0) {
				return line<-1, 1, 1>(begin, std::max({x, y, z}), x, y, z);
			} else {
				z = -z;
				return line<-1, 1, -1>(begin, std::max({x, y, z}), x, y, z);
			}
		} else {
			y = -y;
			if(z >= 0) {
				return line<-1, -1, 1>(begin, std::max({x, y, z}), x, y, z);
			} else {
				z = -z;
				return line<-1, -1, -1>(begin, std::max({x, y, z}), x, y, z);
			}
		}
	}
}

} // namespace basic
} // namespace grid
