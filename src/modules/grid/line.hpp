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

#ifndef MODULES_GRID_LINE_HPP_INCLUDED
#define MODULES_GRID_LINE_HPP_INCLUDED

/**
 * @file
 * Contains a function to create a line.
 *
 * See @ref grid_module for more information.
 */

#include "modules/grid/point.hpp"

#include <vector>

namespace grid
{

/**
 * Calculates all points which form a line.
 *
 * The algorithm is based on Bresenham's line algorithm[1]. The
 * @ref grid::detail namespace holds several implementations of the algorithm.
 * These implementations are a testing place to get a preferred algorithm. This
 * version calls the preferred version internally.
 *
 * [1] http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 *
 * @param begin              The point marking the beginning of the line.
 * @param end                The point marking the end of the line.
 *
 * @returns                  The points that form the line [@p begin, @p end],
 *                           where @c front() matches @p begin and @c back()
 *                           matches @p end.
 */
std::vector<tpoint> line(tpoint begin, tpoint end);

} // namespace grid

#endif
