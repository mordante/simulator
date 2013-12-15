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

#ifndef MODULES_GRID_DETAIL_BASIC_HPP_INCLUDED
#define MODULES_GRID_DETAIL_BASIC_HPP_INCLUDED

#include "modules/grid/point.hpp"

#include <vector>

namespace grid
{

namespace detail
{

/**
 * An implementation for @ref grid::line.
 *
 * This version is the basic implementation. It uses a rather straight forward
 * implementation.
 *
 * @warning This version only functions if the delta @em x is the largest delta.
 */
std::vector<tpoint> line_basic(tpoint begin, tpoint end);

} // namespace detail
} // namespace grid

#endif

