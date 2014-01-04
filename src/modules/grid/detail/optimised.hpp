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

#ifndef MODULES_GRID_DETAIL_OPTIMISED_HPP_INCLUDED
#define MODULES_GRID_DETAIL_OPTIMISED_HPP_INCLUDED

#include "modules/grid/point.hpp"

#include <vector>

namespace grid
{

namespace detail
{

/**
 * An implementation for @ref grid::line.
 *
 * This version does not care which delta is the largest. It uses a templated
 * function for some optimisations. This version uses a lookup table for
 * dispatching. It uses more template parameters as the previous templated
 * version, hoping to shave of a few more cycles.
 */
std::vector<tpoint> line_optimised(tpoint begin, tpoint end);

} // namespace detail
} // namespace grid

#endif
