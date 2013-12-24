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

#ifndef MODULES_CELESTIAL_PLANET_HPP_INCLUDED
#define MODULES_CELESTIAL_PLANET_HPP_INCLUDED

/**
 * @file
 * Contains the definition of a planet.
 *
 * See @ref celestial_module for more information.
 */

#include "modules/geometry/cartesian.hpp"

struct tunit_test;

namespace celestial
{

class tplanet
{
	friend ::tunit_test;

public:
	/***** Constructors, assign operators, destructor. *****/

	tplanet() = delete;

	explicit tplanet(std::string id__,
					 geometry::tcartesian origin__,
					 unit::tlength length__,
					 unit::tlength width__);

	~tplanet() = default;

	tplanet& operator=(tplanet&&) = default;
	tplanet(tplanet&&) = default;

	tplanet& operator=(const tplanet&) = delete;
	tplanet(const tplanet&) = delete;


	/***** ***** ***** Load and store operations. ***** ***** *****/

private:
	/**
	 * Constructor.
	 *
	 * @pre                       @p planet contains a property tree as created
	 *                            by @ref store.
	 *
	 * @param planet              The property tree containing the @p planet
	 *                            data.
	 */
	tplanet(const boost::property_tree::ptree& planet);

public:
	/**
	 * Creates a new @ref celestial::tplanet object from a property tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @pre                       @p planet contains a property tree as created
	 *                            by @ref store.
	 *
	 * @param planet              The property tree containing the @p planet
	 *                            data.
	 *
	 * @returns                   The created property object.
	 */
	static tplanet load(const boost::property_tree::ptree& planet);

	/**
	 * Stores the representation of the object in a property tree.
	 *
	 * @returns                   The created property tree.
	 */
	boost::property_tree::ptree store() const;


	/***** ***** ***** ***** Setters and getters. ***** ***** ***** *****/

	const std::string& id() const;


	/***** ***** ***** ***** Members. ***** ***** ***** *****/
private:
	/**
	 * The id (or name) of the planet.
	 *
	 * The id must be unique for all planets in a @ref tuniverse.
	 */
	std::string id_;

	/** The origin point of the planet. */
	geometry::tcartesian origin_;

	/** The length of the planet in the x-direction. */
	unit::tlength length_;

	/** The length of the planet in the y-direction. */
	unit::tlength width_;
};

} // namespace celestial

#endif
