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

#ifndef LIB_RASTER_RASTER_TPP_INCLUDED
#define LIB_RASTER_RASTER_TPP_INCLUDED

/**
 * @file
 * Contains conversion functions to generate types in a @ref grid.
 *
 * Some parts of the engine use floating point variables which also have units.
 * These types are mapped to dimensionless integral types to do parts of the
 * calculations.
 */

#include "modules/grid/point.hpp"
#include "modules/geometry/cartesian.hpp"

namespace lib
{

inline constexpr grid::tint raster(const unit::tlength& length)
{
	return static_cast<grid::tint>(length.value * 1000.);
}

inline constexpr grid::tpoint raster(const geometry::tcartesian& point)
{
	return grid::tpoint{raster(point.x), raster(point.y), raster(point.z)};
}

} // namespace lib

#endif
