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

#include "modules/grid/detail/vector.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

#include <array>

REGISTER_LOGGER_MODULE("/modules/grid")

namespace grid
{

namespace detail
{

static constexpr tpoint& operator*=(tpoint& lhs, const tpoint& rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
	lhs.z *= rhs.z;

	return lhs;
}

static constexpr tpoint operator*(tpoint lhs, const tpoint rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
	lhs.z *= rhs.z;

	return lhs;
}

static constexpr tpoint operator*(tpoint lhs, const tint rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;

	return lhs;
}

static constexpr tpoint& operator-=(tpoint& lhs, const tpoint& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;

	return lhs;
}

template <tint x_step, tint y_step, tint z_step>
static std::vector<tpoint> line(tpoint begin, tpoint delta)
{
	TRACE_PARAMETERS(begin, delta);

	std::vector<tpoint> result;

	const tpoint step{x_step, y_step, z_step};

	delta *= step;

	tint steps{std::max({delta.x, delta.y, delta.z})};

	tpoint correction{steps / 2, steps / 2, steps / 2};

	for(tint i{0}; i <= steps; ++i) {
		result.push_back(begin);

		correction -= delta;

		tpoint factor{correction.x < 0, correction.y < 0, correction.z < 0};

		correction += factor * steps;
		begin += factor * step;
	}

	return result;
}

std::vector<tpoint> line_vector(tpoint begin, tpoint end)
{
	TRACE_PARAMETERS(begin, end);

	const tpoint delta{end.x - begin.x, end.y - begin.y, end.z - begin.z};

	using tfunction = std::vector<tpoint>(*)(tpoint, tpoint);
	static constexpr std::array<tfunction, 8> functions{
			{line<-1, -1, -1>, line<-1, -1, 1>, line<-1, 1, -1>, line<-1, 1, 1>,
			 line<1, -1, -1>, line<1, -1, 1>, line<1, 1, -1>, line<1, 1, 1>}};

	const bool index_x{delta.x >= 0};
	const bool index_y{delta.y >= 0};
	const bool index_z{delta.z >= 0};

	return functions[4 * index_x + 2 * index_y + index_z](begin, delta);
}

} // namespace basic
} // namespace grid
