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

#ifndef MODULES_GRID_TYPES_TPP_INCLUDED
#define MODULES_GRID_TYPES_TPP_INCLUDED

/**
 * @file
 * Defines the types for the grid module.
 *
 * See @ref grid_module for more information.
 */

namespace grid
{

/**
 * The basic integral type used.
 *
 * Not sure whether the type should be int or int64_t so use a typedef for now.
 */
using tint = int;

} // namespace grid

#endif


