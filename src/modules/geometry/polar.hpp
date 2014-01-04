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

#ifndef MODULES_GEOMETRY_POLAR_HPP_INCLUDED
#define MODULES_GEOMETRY_POLAR_HPP_INCLUDED

/**
 * @file
 * Contains the definition of a polar coordinate.
 *
 * See @ref geometry_module for more information.
 */

#include "modules/unit/angle.tpp"
#include "modules/unit/length.tpp"
#include "modules/unit/quantity/comparison.tpp"

#include <boost/property_tree/ptree_fwd.hpp>

namespace geometry
{

struct tcartesian;

/**
 * A polar coordinate.
 *
 * The system uses the mathematical convention as described on Wikipedia [1].
 *
 * [1] http://en.wikipedia.org/wiki/Spherical_coordinate_system
 */
struct tpolar
{
	/***** Constructors, assign operators, destructor. *****/

	tpolar() = delete;

	explicit constexpr tpolar(unit::tlength r__,
							  unit::tangle theta__,
							  unit::tangle phi__)
		: r{r__}, theta{theta__}, phi{phi__}
	{
	}

	~tpolar() = default;

	tpolar& operator=(tpolar&&) = default;
	tpolar(tpolar&&) = default;

	tpolar& operator=(const tpolar&) = default;
	tpolar(const tpolar&) = default;


	/***** ***** ***** Load and store operations. ***** ***** *****/

private:
	/**
	 * Constructor.
	 *
	 * @pre                       @p polar contains a property tree as created
	 *                            by @ref store.
	 *
	 * @param polar               The property tree containing the @p polar
	 *                            data.
	 */
	tpolar(const boost::property_tree::ptree& polar);

public:
	/**
	 * Creates a new @ref geometry::tpolar object from a property tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @pre                       @p polar contains a property tree as created
	 *                            by @ref store.
	 *
	 * @param polar               The property tree containing the @p polar
	 *                            data.
	 *
	 * @returns                   The created property object.
	 */
	static tpolar load(const boost::property_tree::ptree& polar);

	/**
	 * Stores the representation of the object in a property tree.
	 *
	 * @returns                   The created property tree.
	 */
	boost::property_tree::ptree store() const;


	/***** ***** ***** ***** Conversion operators. ***** ***** ***** *****/

	/**
	 * Conversion operator for @ref geometry::tcartesian.
	 *
	 * The code used is based on the formulae of Wolfram [1].
	 *
	 * See http://mathworld.wolfram.com/SphericalCoordinates.html
	 */
	explicit operator tcartesian() const;


	/***** ***** ***** ***** Members. ***** ***** ***** *****/

	/** The radial distance. */
	unit::tlength r;

	/**
	 * The azimuthal angle.
	 *
	 * The rotation angle in the x-y-plane where the x-axis is 0 rad and
	 * positive angles rotate to the y-axis.
	 */
	unit::tangle theta;

	/**
	 * The polar angle.
	 *
	 * The rotation angle in the x-z-plane where the z-axis is 0 rad and
	 * positive angles rotate to the x-axis.
	 */
	unit::tangle phi;
};

/**
 * The @c operator== for two @ref geometry::tpolar objects.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is equal to
 *                                the value of @p rhs.
 */
inline constexpr bool operator==(const tpolar& lhs, const tpolar& rhs)
{
	return lhs.r == rhs.r && lhs.phi == rhs.phi && lhs.theta == rhs.theta;
}

} // namespace geometry

#endif
