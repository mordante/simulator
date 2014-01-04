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

#ifndef MODULES_SIMULATION_DETAIL_SUN_HPP_INCLUDED
#define MODULES_SIMULATION_DETAIL_SUN_HPP_INCLUDED

#include "modules/geometry/cartesian.hpp"

#include <boost/property_tree/ptree_fwd.hpp>

namespace simulation
{

namespace detail
{

struct tsun
{
	/***** Constructors, assign operators, destructor. *****/

	tsun() = delete;

	explicit tsun(std::string id__, geometry::tcartesian position__);

	~tsun() = default;

	tsun& operator=(tsun&&) = default;
	tsun(tsun&&) = default;

	tsun& operator=(const tsun&) = delete;
	tsun(const tsun&) = delete;

private:
	/**
	 * Constructor.
	 *
	 * @pre                       @p sun contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param sun                 The property tree containing the @p sun
	 *                            data.
	 */
	tsun(const boost::property_tree::ptree& sun);

public:
	/**
	 * Creates a new @ref simulation::detail::tsun object from a property tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @pre                       @p sun contains a property tree as
	 *                            created by @ref store.
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


	/***** ***** ***** ***** Members. ***** ***** ***** *****/

	/**
	 * The id (or name) of the sun.
	 *
	 * This id should match the id of a @ref celestial::tsun.
	 */
	std::string id;

	/**
	 * The current position of the sun in the simulation.
	 *
	 * Every iteration of the simulator moves the celestial bodies to another
	 * place. This field holds the position at @em t = @em x.
	 */
	geometry::tcartesian position;
};

} // namespace detail

} // namespace simulation

#endif
