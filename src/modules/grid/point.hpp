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

#ifndef MODULES_GRID_POINT_HPP_INCLUDED
#define MODULES_GRID_POINT_HPP_INCLUDED

/**
 * @file
 * Contains a definition of a point.
 *
 * See @ref grid_module for more information.
 */

#include "modules/grid/types.tpp"

#include <vector>

namespace grid
{

/**
 * A cartesian 3D point in the grid.
 *
 * The definition of the axis matches @ref geometry::tcartesian.
 */
struct tpoint
{
	/***** Constructors, assign operators, destructor. *****/

	tpoint() = delete;

	explicit constexpr tpoint(tint x__, tint y__, tint z__) noexcept : x{x__},
																	   y{y__},
																	   z{z__}
	{
	}

	~tpoint() = default;

	tpoint& operator=(tpoint&&) = default;
	tpoint(tpoint&&) = default;

	tpoint& operator=(const tpoint&) = default;
	tpoint(const tpoint&) = default;


	/***** ***** ***** ***** Members. ***** ***** ***** *****/

	/** The x-coordinate. */
	tint x;

	/** The y-coordinate. */
	tint y;

	/** The z-coordinate. */
	tint z;
};

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator==                                                        *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator== for two @ref grid::tpoint objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is equal to
 *                                the value of @p rhs.
 */
inline constexpr bool operator==(const tpoint& lhs, const tpoint& rhs) noexcept
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator!=                                                        *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator!= for two @ref grid::tpoint objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is not equal to
 *                                the value of @p rhs.
 */
inline constexpr bool operator!=(const tpoint& lhs, const tpoint& rhs) noexcept
{
	return !(lhs == rhs);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator<                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator< for two @ref grid::tpoint objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is less than
 *                                the value of @p rhs.
 */
inline constexpr bool operator<(const tpoint& lhs, const tpoint& rhs) noexcept
{
	return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y)
		   || (!(rhs.x < lhs.x) && !(rhs.y < lhs.y) && lhs.z < rhs.z);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator+=                                                        *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator+= for two @ref grid::tpoint objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The @p lhs after adding @p rhs to it.
 */
inline constexpr tpoint& operator+=(tpoint& lhs, const tpoint& rhs) noexcept
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;

	return lhs;
}

/**
 * The @c operator+= for a collection @ref grid::tpoint objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The @p lhs after adding @p rhs to every item
 *                                in @p lhs.
 */
std::vector<tpoint>&
operator+=(std::vector<tpoint>& lhs, const tpoint& rhs) noexcept;

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator+                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator+ for two @ref grid::tpoint objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by adding @p lhs to @p rhs.
 */
inline constexpr tpoint operator+(tpoint lhs, const tpoint& rhs) noexcept
{
	lhs += rhs;
	return lhs;
}

/**
 * The @c operator+ for a collection @ref grid::tpoint objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by adding @p rhs to every
 *                                item in @p lhs.
 */
std::vector<tpoint> operator+(std::vector<tpoint> lhs, const tpoint& rhs);

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operations                                                        *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * Tests whether two ranges of @ref grid::tpoint objects intersect.
 *
 * @pre                           This assertion holds: @code
 *                                std::is_sorted(lhs.cbegin(), lhs.cend())
 *                                @endcode
 * @pre                           This assertion holds: @code
 *                                std::is_sorted(rhs.cbegin(), rhs.cend())
 *                                @endcode
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether or not the two ranges have any point
 *                                in common.
 */
bool intersects(const std::vector<tpoint>& lhs, const std::vector<tpoint>& rhs);

/**
 * Returns the intersection two ranges of @ref grid::tpoint objects.
 *
 * @pre                           This assertion holds: @code
 *                                std::is_sorted(lhs.cbegin(), lhs.cend())
 *                                @endcode
 * @pre                           This assertion holds: @code
 *                                std::is_sorted(rhs.cbegin(), rhs.cend())
 *                                @endcode
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The points of @p lhs and @p rhs that are in
 *                                both ranges.
 */
std::vector<tpoint>
intersection(const std::vector<tpoint>& lhs, const std::vector<tpoint>& rhs);

} // namespace grid

#endif
