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

#ifndef MODULES_GEOMETRY_ORBIT_HPP_INCLUDED
#define MODULES_GEOMETRY_ORBIT_HPP_INCLUDED

/**
 * @file
 * Contains the definition of an orbit.
 *
 * See @ref geometry_module for more information.
 */

#include "modules/geometry/polar.hpp"
#include "modules/unit/time.tpp"

#include <boost/property_tree/ptree_fwd.hpp>

namespace geometry
{

struct tcartesian;

/**
 * The definition of an orbit.
 *
 * An orbit always rotates around the point(0, 0, 0), when another coordinate
 * is wanted a class needs to use a @ref geometry::tcartesian as offset and add
 * that value to the result of @ref geometry::torbit::position.
 *
 * The object has two rotation planes.
 */
struct torbit
{
	/***** Constructors, assign operators, destructor. *****/

	torbit() = delete;

	explicit constexpr torbit(tpolar rotation__,
							  unit::ttime rotation_period_theta_plane__,
							  unit::ttime rotation_period_phi_plane__)
		: rotation{std::move(rotation__)}
		, rotation_period_theta_plane{rotation_period_theta_plane__}
		, rotation_period_phi_plane{rotation_period_phi_plane__}
	{
	}

	~torbit() = default;

	torbit& operator=(torbit&&) = default;
	torbit(torbit&&) = default;

	torbit& operator=(const torbit&) = default;
	torbit(const torbit&) = default;


	/***** ***** ***** Load and store operations. ***** ***** *****/

private:
	/**
	 * Constructor.
	 *
	 * @pre                       @p orbit contains a property tree as created
	 *                            by @ref store.
	 *
	 * @param orbit               The property tree containing the @p orbit
	 *                            data.
	 */
	torbit(const boost::property_tree::ptree& orbit);

public:
	/**
	 * Creates a new @ref geometry::torbit object from a property tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @pre                       @p orbit contains a property tree as created
	 *                            by @ref store.
	 *
	 * @param orbit               The property tree containing the @p orbit
	 *                            data.
	 *
	 * @returns                   The created property object.
	 */
	static torbit load(const boost::property_tree::ptree& orbit);

	/**
	 * Stores the representation of the object in a property tree.
	 *
	 * @returns                   The created property tree.
	 */
	boost::property_tree::ptree store() const;


	/***** ***** ***** ***** Operations. ***** ***** ***** *****/

	/**
	 * Calculates the position of the object at time @p time.
	 *
	 * @param time                The time at which the position is requested.
	 *
	 * @returns                   The position at time @p time.
	 */
	tcartesian position(const unit::ttime time) const;


	/***** ***** ***** ***** Members. ***** ***** ***** *****/

	/** The base rotation vector of the orbit. */
	tpolar rotation;

	/**
	 * The amount of time it takes to orbit around the major axis.
	 *
	 * The major axis is defined by running a circle from the x-axis to the
	 * y-axis. A negative value means there is no rotation; to rotate from y to
	 * x, just change to direction of the @ref rotation.
	 */
	unit::ttime rotation_period_theta_plane;

	/**
	 * The amount of time it takes to orbit around the major axis.
	 *
	 * Like the @ref rotation_period_theta_plane, but goes from the x-axis to
	 * the z-axis.
	 */
	unit::ttime rotation_period_phi_plane;
};

} // namespace geometry

#endif
