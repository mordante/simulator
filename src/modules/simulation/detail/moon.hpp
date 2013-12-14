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

#ifndef MODULES_SIMULATION_DETAIL_MOON_HPP_INCLUDED
#define MODULES_SIMULATION_DETAIL_MOON_HPP_INCLUDED

#include "modules/geometry/cartesian.hpp"

#include <boost/property_tree/ptree_fwd.hpp>

namespace simulation
{

namespace detail
{

struct tmoon
{
	/***** Constructors, assign operators, destructor. *****/

	tmoon() = delete;

	explicit tmoon(std::string id__, geometry::tcartesian position__);

	~tmoon() = default;

	tmoon& operator=(tmoon&&) = default;
	tmoon(tmoon&&) = default;

	tmoon& operator=(const tmoon&) = delete;
	tmoon(const tmoon&) = delete;

private:
	/**
	 * Constructor.
	 *
	 * @pre                       @p moon contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param moon                The property tree containing the @p moon
	 *                            data.
	 */
	tmoon(const boost::property_tree::ptree& moon);

public:
	/**
	 * Creates a new @ref simulation::detail::tmoon object from a property tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @pre                       @p moon contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param moon                The property tree containing the @p moon
	 *                            data.
	 *
	 * @returns                   The created property object.
	 */
	static tmoon load(const boost::property_tree::ptree& moon);

	/**
	 * Stores the representation of the object in a property tree.
	 *
	 * @returns                   The created property tree.
	 */
	boost::property_tree::ptree store() const;


	/***** ***** ***** ***** Members. ***** ***** ***** *****/

	/**
	 * The id (or name) of the moon.
	 *
	 * This id should match the id of a @ref celestial::tmoon.
	 */
	std::string id;

	/**
	 * The current position of the moon in the simulation.
	 *
	 * Every iteration of the simulator moves the celestial bodies to another
	 * place. This field holds the position at @em t = @em x.
	 */
	geometry::tcartesian position;
};

} // namespace detail

} // namespace simulation

#endif
