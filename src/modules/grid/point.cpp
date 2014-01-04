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

#include "modules/grid/point.hpp"

#include <algorithm>

namespace grid
{

std::vector<tpoint>&
operator+=(std::vector<tpoint>& lhs, const tpoint& rhs) noexcept
{
	for(auto& point : lhs) {
		point += rhs;
	}

	return lhs;
}

std::vector<tpoint> operator+(std::vector<tpoint> lhs, const tpoint& rhs)
{
	for(auto& point : lhs) {
		point += rhs;
	}

	return lhs;
}

bool intersects(const std::vector<tpoint>& lhs, const std::vector<tpoint>& rhs)
{
	return !intersection(lhs, rhs).empty();
}

std::vector<tpoint>
intersection(const std::vector<tpoint>& lhs, const std::vector<tpoint>& rhs)
{
	std::vector<tpoint> result;
	std::set_intersection(lhs.cbegin(),
						  lhs.cend(),
						  rhs.cbegin(),
						  rhs.cend(),
						  std::back_inserter(result));

	return result;
}

} // namespace grid
