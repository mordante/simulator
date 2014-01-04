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

#ifndef MODULES_GRID_CIRCLE_HPP_INCLUDED
#define MODULES_GRID_CIRCLE_HPP_INCLUDED

/**
 * @file
 * Contains a function to create a circle.
 *
 * See @ref grid_module for more information.
 */

#include "modules/grid/point.hpp"

namespace grid
{

/**
 * Calculates all points which form a circle.
 *
 * This version draws the circle around the origin. It does not remove the
 * duplicate points, and is mainly intended to be used a base for testing
 * @ref circle.
 *
 * The algorithm is based on Bresenham's circle algorithm[1].
 *
 * [1] http://en.wikipedia.org/wiki/Bresenham%27s_circle_algorithm
 *
 * @param radius             The radius of the circle.
 *
 * @returns                  The points that form the circle.
 */
std::vector<tpoint> circle_raw(const tint radius);

/**
 * Calculates all points which form a circle.
 *
 * This version draws the circle around the origin and removes the duplicate
 * points.
 *
 * The algorithm is based on Bresenham's circle algorithm[1].
 *
 * [1] http://en.wikipedia.org/wiki/Bresenham%27s_circle_algorithm
 *
 * @param radius             The radius of the circle.
 * @param sorted_output      Sort the returned value. Certain algorithms expect
 *                           sorted ranges, for example
 *                           @ref grid::intersection, setting this value to
 *                           @c true makes the output suitable for these
 *                           functions.
 *
 * @returns                  The points that form the circle.
 */
std::vector<tpoint> circle(const tint radius, const bool sorted_output);

/**
 * Calculates all points which form a circle.
 *
 * This version draws the circle around @p centre and removes the duplicate
 * points.
 *
 * The algorithm is based on Bresenham's circle algorithm[1].
 *
 * [1] http://en.wikipedia.org/wiki/Bresenham%27s_circle_algorithm
 *
 * @param centre             The point marking the centre of the circle.
 * @param radius             The radius of the circle.
 * @param sorted_output      Sort the returned value. Certain algorithms expect
 *                           sorted ranges, for example
 *                           @ref grid::intersection, setting this value to
 *                           @c true makes the output suitable for these
 *                           functions.
 *
 * @returns                  The points that form the circle.
 */
std::vector<tpoint>
circle(const tpoint& centre, const tint radius, const bool sorted_output);

} // namespace grid

#endif
