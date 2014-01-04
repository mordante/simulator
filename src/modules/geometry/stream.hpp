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

#ifndef MODULES_GEOMETRY_STREAM_HPP_INCLUDED
#define MODULES_GEOMETRY_STREAM_HPP_INCLUDED

/**
 * @file
 * Contains the stream operators for the module.
 *
 * Most stream operators are intended for debug usage, so not included for
 * normal usage. Therefore there are no unit tests for this file.
 */

#include <iosfwd>

namespace geometry
{

struct tcartesian;
struct torbit;
struct tpolar;

/**
 * The operator<< for a @ref geometry::tcartesian.
 *
 * @param ostream                 The output stream to write to.
 * @param cartesian               The object to write to the stream.
 *
 * @returns                       @p ostream
 */
std::ostream& operator<<(std::ostream& ostream, const tcartesian& cartesian);

/**
 * The operator<< for a @ref geometry::torbit.
 *
 * @param ostream                 The output stream to write to.
 * @param orbit                   The object to write to the stream.
 *
 * @returns                       @p ostream
 */
std::ostream& operator<<(std::ostream& ostream, const torbit& orbit);

/**
 * The operator<< for a @ref geometry::tpolar.
 *
 * @param ostream                 The output stream to write to.
 * @param polar                   The object to write to the stream.
 *
 * @returns                       @p ostream
 */
std::ostream& operator<<(std::ostream& ostream, const tpolar& polar);

} // namespace geometry

#endif
