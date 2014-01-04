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

#include "modules/grid/circle.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

REGISTER_LOGGER_MODULE("/modules/grid")

namespace grid
{

std::vector<tpoint> circle_raw(const tint radius)
{
	TRACE_PARAMETERS(radius);

	tint x{radius};
	tint y{0};
	const tint z{0};
	tint correction{1 - x};

	std::vector<tpoint> result;
	if(radius == 0) {
		return result;
	}

	while(x >= y) {

		result.emplace_back(x, y, z);
		result.emplace_back(x, -y, z);
		result.emplace_back(-x, y, z);
		result.emplace_back(-x, -y, z);

		result.emplace_back(y, x, z);
		result.emplace_back(y, -x, z);
		result.emplace_back(-y, x, z);
		result.emplace_back(-y, -x, z);

		++y;

		if(correction < 0) {
			correction += 2 * y + 1;
		} else {
			--x;
			correction += 2 * (y - x + 1);
		}
	}

	return result;
}

std::vector<tpoint> circle(const tint radius, const bool sorted_output)
{
	TRACE_PARAMETERS(radius, sorted_output);

	tint x{radius};
	tint y{0};
	const tint z{0};
	tint correction{1 - x};

	std::vector<tpoint> result;
	if(radius == 0) {
		return result;
	}

	while(x >= y) {

		if(y == 0) {
			result.emplace_back(x, y, z);
			result.emplace_back(-x, y, z);
			result.emplace_back(y, x, z);
			result.emplace_back(y, -x, z);
		} else if(y == x) {
			result.emplace_back(x, y, z);
			result.emplace_back(x, -y, z);
			result.emplace_back(-x, y, z);
			result.emplace_back(-x, -y, z);
		} else {
			result.emplace_back(x, y, z);
			result.emplace_back(x, -y, z);
			result.emplace_back(-x, y, z);
			result.emplace_back(-x, -y, z);

			result.emplace_back(y, x, z);
			result.emplace_back(y, -x, z);
			result.emplace_back(-y, x, z);
			result.emplace_back(-y, -x, z);
		}

		++y;

		if(correction < 0) {
			correction += 2 * y + 1;
		} else {
			--x;
			correction += 2 * (y - x + 1);
		}
	}

	if(sorted_output) {
		std::sort(std::begin(result), std::end(result));
	}

	return result;
}

std::vector<tpoint>
circle(const tpoint& centre, const tint radius, const bool sorted_output)
{
	TRACE_PARAMETERS(centre, radius, sorted_output);

	std::vector<tpoint> result{circle(radius, sorted_output)};
	/* Note shifting the output does not affect the sorting order. */
	return result += centre;
}

} // namespace grid
