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

/**
 * @page grid_module Grid module.
 *
 * The grid is an abstraction layer for the simulation module. This module has
 * its own cartesian coordinate system. Unlike the coordinate system in the
 * @ref geometry namespace this coordinate system has no units of measurement.
 * This allows the engine to map @em x m from the @ref geometry namespace to
 * one unit in this namespace. The intention is that 1 mm from the
 * @ref geometry namespace is one unit in this namespace.
 */
