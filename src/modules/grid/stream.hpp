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

#ifndef MODULES_GRID_STREAM_HPP_INCLUDED
#define MODULES_GRID_STREAM_HPP_INCLUDED

#include <iosfwd>

namespace grid
{

struct tpoint;

/**
 * The operator<< for a @ref grid::tpoint.
 *
 * @param ostream                 The output stream to write to.
 * @param point                   The object to write to the stream.
 *
 * @returns                       @p ostream
 */
std::ostream& operator<<(std::ostream& ostream, const tpoint& point);

} // namespace grid

#endif
