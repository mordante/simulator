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
 * @page unit_module The unit module
 *
 * The unit module contains the basis to implement calculations that keep track
 * of the value of the units. The module mainly contains templated functions,
 * since large templated files tend to slow down the compiler, several
 * operations are moved to their own header. The disadvantage is that multiple
 * includes are required, but changing one header might avoid recompile the
 * entire system.
 *
 * The basis of the implementation is based on the ideas presented in §28.7 of
 * TC++PL [BS13].
 *
 * [BS13] Bjarne Stroustrup, The C++ Programming Language (4th Edition),
 * Addison-Wesley ISBN 978-0-321-95832-7
 */
