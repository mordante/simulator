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

/**
 * @page geometry_module The geometry module
 *
 * This module contains the coordinate system used in simulator. The
 * coordinates systems used use floating point values to obtain a high
 * precision. Since floating point calculations tend to be slow these
 * coordinates are rastered to a grid before the simulator starts its
 * calculations.
 */
