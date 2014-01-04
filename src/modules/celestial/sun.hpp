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

#ifndef MODULES_CELESTIAL_SUN_HPP_INCLUDED
#define MODULES_CELESTIAL_SUN_HPP_INCLUDED

/**
 * @file
 * Contains the definition of a sun.
 *
 * @note The @ref celestial::tsun and @ref celestial::tmoon are quite similar,
 * at the moment the only difference is that a @ref celestial::tsun produces
 * energy and a @ref celestial::tmoon does not.
 *
 * See @ref celestial_module for more information.
 */

#include "modules/geometry/cartesian.hpp"
#include "modules/geometry/orbit.hpp"
#include "modules/grid/point.hpp"
#include "modules/unit/energy.tpp"
#include "modules/unit/length.tpp"

struct tunit_test;

namespace celestial
{

class tsun
{
	friend ::tunit_test;

public:
	/***** Constructors, assign operators, destructor. *****/

	tsun() = delete;

	explicit tsun(std::string id__,
				  geometry::tcartesian origin__,
				  geometry::torbit orbit__,
				  unit::tlength radius__,
				  unit::tenergy energy_output__);

	~tsun() = default;

	tsun& operator=(tsun&&) = default;
	tsun(tsun&&) = default;

	tsun& operator=(const tsun&) = delete;
	tsun(const tsun&) = delete;


	/***** ***** ***** Load and store operations. ***** ***** *****/

private:
	/**
	 * Constructor.
	 *
	 * @pre                       @p sun contains a property tree as created
	 *                            by @ref store.
	 *
	 * @param sun                 The property tree containing the @p sun
	 *                            data.
	 */
	tsun(const boost::property_tree::ptree& sun);

public:
	/**
	 * Creates a new @ref celestial::tsun object from a property tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @pre                       @p sun contains a property tree as created
	 *                            by @ref store.
	 *
	 * @param sun                 The property tree containing the @p sun
	 *                            data.
	 *
	 * @returns                   The created property object.
	 */
	static tsun load(const boost::property_tree::ptree& sun);

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
	geometry::tcartesian position(const unit::ttime time) const;

	/**
	 * Calculates the grid of the object at time @p time.
	 *
	 * @param time                The time at which the grid is requested.
	 *
	 * @returns                   The grid at time @p time.
	 */
	std::vector<grid::tpoint> grid(const unit::ttime time) const;


	/***** ***** ***** ***** Setters and getters. ***** ***** ***** *****/

	const std::string& id() const;


	/***** ***** ***** ***** Members. ***** ***** ***** *****/
private:
	/**
	 * The id (or name) of the sun.
	 *
	 * The id must be unique for all suns in a @ref tuniverse.
	 */
	std::string id_;

	/** The origin point of the sun. */
	geometry::tcartesian origin_;

	/** The orbit point of the sun. */
	geometry::torbit orbit_;

	/**
	 * The radius of the sun.
	 *
	 * @note If there will be a setter for this variable it also should update
	 * the clear the @ref grid_ so the next call to @ref update_grid will
	 * refresh the cached value.
	 */
	unit::tlength radius_;

	/**
	 * The amount of energy the sun outputs per second.
	 *
	 * Note maybe the output should be in W instead of J.
	 */
	unit::tenergy energy_output_;

	/**
	 * Contains the current object as a set of @ref grid::tpoint objects.
	 *
	 * @note The value is mutable since it might be the getter will
	 * automatically update the value when needed.
	 */
	mutable std::vector<grid::tpoint> grid_{};

	/**
	 * Updates @ref grid_.
	 *
	 * The function assumes the current @ref grid_ is invalid and recalculates
	 * it.
	 */
	void update_grid() const;
};

} // namespace celestial

#endif
