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

#ifndef MODULES_GRID_DETAIL_VECTOR_HPP_INCLUDED
#define MODULES_GRID_DETAIL_VECTOR_HPP_INCLUDED

#include "modules/grid/point.hpp"

#include <vector>

namespace grid
{

namespace detail
{

/**
 * An implementation for @ref grid::line.
 *
 * This version does not care which delta is the largest. It is written in a
 * way, where the hope is that the compiler will be able to vectorise the code.
 */
std::vector<tpoint> line_vector(tpoint begin, tpoint end);

} // namespace detail
} // namespace grid

#endif
