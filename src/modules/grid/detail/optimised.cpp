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

#include "modules/grid/detail/optimised.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

#include <array>

REGISTER_LOGGER_MODULE("/modules/grid")

namespace grid
{

namespace detail
{

enum tupdate {
	zero,
	one,
	multiple
};

template <tupdate>
inline void update(tint& value,
				   tint& correction,
				   tint& delta,
				   const tint steps,
				   const tint step)
{
	TRACE_PARAMETERS(value, correction, delta, steps, step);

	correction -= delta;
	if(correction < 0) {
		correction += steps;
		value += step;
	}
}

template <>
inline void update<tupdate::zero>(tint& /*value*/,
								  tint& /*correction*/,
								  tint& /*delta*/,
								  const tint /*steps*/,
								  const tint /*step*/)
{
	TRACE;
}

template <>
inline void update<tupdate::one>(tint& value,
								 tint& /*correction*/,
								 tint& /*delta*/,
								 const tint /*steps*/,
								 const tint step)
{
	TRACE_PARAMETERS(value, step);

	value += step;
}

template <tint x_step,
		  tupdate x_update,
		  tint y_step,
		  tupdate y_update,
		  tint z_step,
		  tupdate z_update>
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

		update<x_update>(begin.x, x_correction, dx, steps, x_step);
		update<y_update>(begin.y, y_correction, dy, steps, y_step);
		update<z_update>(begin.z, z_correction, dz, steps, z_step);
	}

	return result;
}

template <tint x_step, tint y_step, tint z_step>
static std::vector<tpoint> line(tpoint begin, tint dx, tint dy, tint dz)
{
	TRACE_PARAMETERS(begin, dx, dy, dz);

	dx *= x_step;
	dy *= y_step;
	dz *= z_step;

	tint steps = std::max({dx, dy, dz});

	using tfunction = std::vector<tpoint>(*)(tpoint, tint, tint, tint, tint);
	static constexpr std::array<tfunction, 27> functions{
			{line<x_step,
				  tupdate::zero,
				  y_step,
				  tupdate::zero,
				  z_step,
				  tupdate::zero>,
			 line<x_step,
				  tupdate::zero,
				  y_step,
				  tupdate::zero,
				  z_step,
				  tupdate::one>,
			 line<x_step,
				  tupdate::zero,
				  y_step,
				  tupdate::zero,
				  z_step,
				  tupdate::multiple>,
			 line<x_step,
				  tupdate::zero,
				  y_step,
				  tupdate::one,
				  z_step,
				  tupdate::zero>,
			 line<x_step,
				  tupdate::zero,
				  y_step,
				  tupdate::one,
				  z_step,
				  tupdate::one>,
			 line<x_step,
				  tupdate::zero,
				  y_step,
				  tupdate::one,
				  z_step,
				  tupdate::multiple>,
			 line<x_step,
				  tupdate::zero,
				  y_step,
				  tupdate::multiple,
				  z_step,
				  tupdate::zero>,
			 line<x_step,
				  tupdate::zero,
				  y_step,
				  tupdate::multiple,
				  z_step,
				  tupdate::one>,
			 line<x_step,
				  tupdate::zero,
				  y_step,
				  tupdate::multiple,
				  z_step,
				  tupdate::multiple>,
			 line<x_step,
				  tupdate::one,
				  y_step,
				  tupdate::zero,
				  z_step,
				  tupdate::zero>,
			 line<x_step,
				  tupdate::one,
				  y_step,
				  tupdate::zero,
				  z_step,
				  tupdate::one>,
			 line<x_step,
				  tupdate::one,
				  y_step,
				  tupdate::zero,
				  z_step,
				  tupdate::multiple>,
			 line<x_step,
				  tupdate::one,
				  y_step,
				  tupdate::one,
				  z_step,
				  tupdate::zero>,
			 line<x_step,
				  tupdate::one,
				  y_step,
				  tupdate::one,
				  z_step,
				  tupdate::one>,
			 line<x_step,
				  tupdate::one,
				  y_step,
				  tupdate::one,
				  z_step,
				  tupdate::multiple>,
			 line<x_step,
				  tupdate::one,
				  y_step,
				  tupdate::multiple,
				  z_step,
				  tupdate::zero>,
			 line<x_step,
				  tupdate::one,
				  y_step,
				  tupdate::multiple,
				  z_step,
				  tupdate::one>,
			 line<x_step,
				  tupdate::one,
				  y_step,
				  tupdate::multiple,
				  z_step,
				  tupdate::multiple>,
			 line<x_step,
				  tupdate::multiple,
				  y_step,
				  tupdate::zero,
				  z_step,
				  tupdate::zero>,
			 line<x_step,
				  tupdate::multiple,
				  y_step,
				  tupdate::zero,
				  z_step,
				  tupdate::one>,
			 line<x_step,
				  tupdate::multiple,
				  y_step,
				  tupdate::zero,
				  z_step,
				  tupdate::multiple>,
			 line<x_step,
				  tupdate::multiple,
				  y_step,
				  tupdate::one,
				  z_step,
				  tupdate::zero>,
			 line<x_step,
				  tupdate::multiple,
				  y_step,
				  tupdate::one,
				  z_step,
				  tupdate::one>,
			 line<x_step,
				  tupdate::multiple,
				  y_step,
				  tupdate::one,
				  z_step,
				  tupdate::multiple>,
			 line<x_step,
				  tupdate::multiple,
				  y_step,
				  tupdate::multiple,
				  z_step,
				  tupdate::zero>,
			 line<x_step,
				  tupdate::multiple,
				  y_step,
				  tupdate::multiple,
				  z_step,
				  tupdate::one>,
			 line<x_step,
				  tupdate::multiple,
				  y_step,
				  tupdate::multiple,
				  z_step,
				  tupdate::multiple>}};

	const size_t index_x{dx == 0 ? tupdate::zero : dx == steps
														   ? tupdate::one
														   : tupdate::multiple};
	const size_t index_y{dy == 0 ? tupdate::zero : dy == steps
														   ? tupdate::one
														   : tupdate::multiple};
	const size_t index_z{dz == 0 ? tupdate::zero : dz == steps
														   ? tupdate::one
														   : tupdate::multiple};

	return functions[9 * index_x + 3 * index_y + index_z](
			begin, steps, dx, dy, dz);
}

std::vector<tpoint> line_optimised(tpoint begin, tpoint end)
{
	TRACE_PARAMETERS(begin, end);

	tint dx{end.x - begin.x};
	tint dy{end.y - begin.y};
	tint dz{end.z - begin.z};

	using tfunction = std::vector<tpoint>(*)(tpoint, tint, tint, tint);

	static constexpr std::array<tfunction, 8> functions{
			{line<-1, -1, -1>, line<-1, -1, 1>, line<-1, 1, -1>, line<-1, 1, 1>,
			 line<1, -1, -1>, line<1, -1, 1>, line<1, 1, -1>, line<1, 1, 1>}};

	const bool index_x{dx >= 0};
	const bool index_y{dy >= 0};
	const bool index_z{dz >= 0};

	return functions[4 * index_x + 2 * index_y + index_z](begin, dx, dy, dz);
}

} // namespace basic
} // namespace grid
