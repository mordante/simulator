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

#ifndef MODULES_GEOMETRY_CARTESIAN_HPP_INCLUDED
#define MODULES_GEOMETRY_CARTESIAN_HPP_INCLUDED

/**
 * @file
 * Contains the definition of a cartesian coordinate.
 *
 * See @ref geometry_module for more information.
 */

#include "modules/unit/length.tpp"
#include "modules/unit/quantity/arithmetic.tpp"
#include "modules/unit/quantity/comparison.tpp"

#include <boost/property_tree/ptree_fwd.hpp>

namespace geometry
{

struct tpolar;

/**
 * The definition of a cartesian coordinate.
 *
 * The system uses the convention as described on wikipedia [1]:
@verbatim
	z
	|
	|__ y
   /
  /
 x
@endverbatim
 *
 * Thus:
 * - The positive x-axis is towards the viewer.
 * - The positive y-axis goes towards the right.
 * - The positive z-axis goes upwards.
 *
 * [1] http://en.wikipedia.org/wiki/Cartesian_coordinate_system
 */
struct tcartesian
{
	/***** Constructors, assign operators, destructor. *****/

	tcartesian() = delete;

	explicit constexpr tcartesian(unit::tlength x__,
								  unit::tlength y__,
								  unit::tlength z__)
		: x{x__}, y{y__}, z{z__}
	{
	}

	~tcartesian() = default;

	tcartesian& operator=(tcartesian&&) = default;
	tcartesian(tcartesian&&) = default;

	tcartesian& operator=(const tcartesian&) = default;
	tcartesian(const tcartesian&) = default;


	/***** ***** ***** Load and store operations. ***** ***** *****/

private:
	/**
	 * Constructor.
	 *
	 * @pre                       @p cartesian contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param cartesian           The property tree containing the @p cartesian
	 *                            data.
	 */
	tcartesian(const boost::property_tree::ptree& cartesian);

public:
	/**
	 * Creates a new @ref geometry::tcartesian object from a property tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @pre                       @p cartesian contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param cartesian           The property tree containing the @p cartesian
	 *                            data.
	 *
	 * @returns                   The created property object.
	 */
	static tcartesian load(const boost::property_tree::ptree& cartesian);

	/**
	 * Stores the representation of the object in a property tree.
	 *
	 * @returns                   The created property tree.
	 */
	boost::property_tree::ptree store() const;


	/***** ***** ***** ***** Conversion operators. ***** ***** ***** *****/

	/**
	 * Conversion operator for @ref geometry::tpolar.
	 *
	 * The code used is based on the formulae of Wolfram [1].
	 *
	 * See http://mathworld.wolfram.com/SphericalCoordinates.html
	 */
	explicit operator tpolar() const;


	/***** ***** ***** ***** Operations. ***** ***** ***** *****/

	/**
	 * Determines the length a the vector.
	 *
	 * The length is the distance between this object and an object at 0, 0, 0.
	 *
	 * @returns                   The length of a vector.
	 */
	constexpr unit::tlength length() const
	{
		return sqrt(x * x + y * y + z * z);
	}


	/***** ***** ***** ***** Members. ***** ***** ***** *****/

	/** The x-coordinate. */
	unit::tlength x;

	/** The y-coordinate. */
	unit::tlength y;

	/** The z-coordinate. */
	unit::tlength z;
};

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator+                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator+= for two @ref geometry::tcartesian objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after adding @p rhs to it.
 */
inline constexpr tcartesian& operator+=(tcartesian& lhs, const tcartesian& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;

	return lhs;
}

/**
 * The @c operator+ for two @ref geometry::tcartesian objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by adding @p lhs and
 *                                @p rhs.
 */
inline constexpr tcartesian operator+(tcartesian lhs, const tcartesian& rhs)
{
	return lhs += rhs;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator-                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator-= for two @ref geometry::tcartesian objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after subtracting @p rhs from it.
 */
inline constexpr tcartesian& operator-=(tcartesian& lhs, const tcartesian& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;

	return lhs;
}

/**
 * The @c operator- for two @ref geometry::tcartesian objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by subtracting @p rhs from
 *                                @p lhs.
 */
inline constexpr tcartesian operator-(tcartesian lhs, const tcartesian& rhs)
{
	return lhs -= rhs;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator==                                                        *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator== for two @ref geometry::tcartesian objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is equal to
 *                                the value of @p rhs.
 */
inline constexpr bool operator==(const tcartesian& lhs, const tcartesian& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

} // namespace geometry

#endif
