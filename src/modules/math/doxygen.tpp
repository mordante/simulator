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
 * @page math_module The mathematics module
 *
 * The mathematics module contains the operations for applying mathematical
 * operations to sets of values. This module is intended to extend the
 * functionality of the unit modules [@ref unit_module]. Like the unit module
 * the code contains mainly templated functions and is likewise separated in
 * several smaller files.
 *
 * The module contains the following container:
 * - vector [@ref math_module_vector]
 *
 *
 * @section math_module_vector The vector
 *
 * This class is based on a combination of @c std::array and @c std::valarray,
 * an aggregate class for doing operations on all elements of the vector.
 * Several array operations are evaluated on runtime, for example comparison.
 * This class instead unrolls the 'looping over the elements' at compile time,
 * which should lead to better comparison. Since the sizes of the array are
 * expected to be small the generated code should remain compact.
 */
