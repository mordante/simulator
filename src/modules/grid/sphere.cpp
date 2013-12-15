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

#include "modules/grid/sphere.hpp"

#include "modules/grid/circle.hpp"

#include "modules/grid/stream.hpp"
#include "modules/logger/logger.hpp"

#include <algorithm>

REGISTER_LOGGER_MODULE("/modules/grid")

namespace grid
{
static void
layer_raw(std::vector<tpoint>& result, const tint radius, const tint z)
{
	TRACE_PARAMETERS(radius, z);

	tpoint centre{0, 0, z};
	std::vector<tpoint> data{circle(centre, radius, false)};

	for(auto& element : data) {
		result.push_back(element);
		element.z = -element.z;
		result.push_back(element);
	}
}

std::vector<tpoint> sphere_raw(tint radius)
{
	TRACE_PARAMETERS(radius);

	std::vector<tpoint> result;

	tint z{0};
	tint correction{1 - radius};

	while(radius >= z) {

		layer_raw(result, radius, z);
		layer_raw(result, z, radius);

		++z;

		if(correction < 0) {
			correction += 2 * z + 1;
		} else {
			--radius;
			correction += 2 * (z - radius + 1);
		}
	}

	return result;
}

static void layer(std::vector<tpoint>& result, const tint radius, const tint z)
{
	TRACE_PARAMETERS(radius, z);

	tpoint centre{0, 0, z};
	std::vector<tpoint> data{circle(centre, radius, false)};

	if(z == 0) {
		std::move(data.begin(), data.end(), std::back_inserter(result));
	} else {
		for(auto& element : data) {
			result.push_back(element);
			element.z = -element.z;
			result.push_back(std::move(element));
		}
	}
}

std::vector<tpoint> sphere(tint radius, const bool sorted_output)
{
	TRACE_PARAMETERS(radius, sorted_output);

	std::vector<tpoint> result;

	tint z{0};
	tint correction{1 - radius};

	while(radius >= z) {
		layer(result, radius, z);
		if(radius != z) {
			layer(result, z, radius);
		}

		++z;

		if(correction < 0) {
			correction += 2 * z + 1;
		} else {
			--radius;
			correction += 2 * (z - radius + 1);
		}
	}

	if(sorted_output) {
		std::sort(std::begin(result), std::end(result));
	}

	return result;
}

std::vector<tpoint>
sphere(const tpoint& centre, const tint radius, const bool sorted_output)
{
	TRACE_PARAMETERS(centre, radius, sorted_output);

	std::vector<tpoint> result{sphere(radius, sorted_output)};
	/* Note shifting the output does not affect the sorting order. */
	return result += centre;
}

} // namespace d
