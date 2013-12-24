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

#ifndef MODULES_CELESTIAL_UNIVERSE_HPP_INCLUDED
#define MODULES_CELESTIAL_UNIVERSE_HPP_INCLUDED

/**
 * @file
 * Contains the definition of the universe.
 *
 * See @ref celestial_module for more information.
 */

#include "modules/celestial/moon.hpp"
#include "modules/celestial/planet.hpp"
#include "modules/celestial/sun.hpp"

#include <vector>

namespace celestial
{

/**
 * The universe is a container for all suns, moons and planets.
 */
struct tuniverse
{
	/***** Constructors, assign operators, destructor. *****/

	tuniverse() = default;

	~tuniverse() = default;

	tuniverse& operator=(tuniverse&&) = default;
	tuniverse(tuniverse&&) = default;

	tuniverse& operator=(const tuniverse&) = default;
	tuniverse(const tuniverse&) = default;


	/***** ***** ***** Load and store operations. ***** ***** *****/

private:
	/**
	 * Constructor.
	 *
	 * @note This function has no unit test, since the required test code would
	 * be quite verbose, so relay on the tests for the subcomponents to do the
	 * right thing (tm).
	 *
	 * @pre                       @p universe contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param universe            The property tree containing the @p universe
	 *                            data.
	 */
	tuniverse(const boost::property_tree::ptree& universe);

public:
	/**
	 * Creates a new @ref celestial::tuniverse object from a property tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @note This function has no unit test, since the required test code would
	 * be quite verbose, so relay on the tests for the subcomponents to do the
	 * right thing (tm).
	 *
	 * @pre                       @p universe contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param universe            The property tree containing the @p universe
	 *                            data.
	 *
	 * @returns                   The created property object.
	 */
	static tuniverse load(const boost::property_tree::ptree& universe);

	/**
	 * Stores the representation of the object in a property tree.
	 *
	 * @note This function has no unit test, since the required test code would
	 * be quite verbose, so relay on the tests for the subcomponents to do the
	 * right thing (tm).
	 *
	 * @returns                   The created property tree.
	 */
	boost::property_tree::ptree store() const;


	/***** ***** ***** ***** Operations. ***** ***** ***** *****/

	/**
	 * Add a new sun to the universe.
	 *
	 * @pre                       @p sun.id() is unique for all objects in
	 *                            @ref suns_.
	 *
	 * @param sun                 The sun to add (move) to the universe.
	 */
	void add(tsun&& sun);

	/**
	 * Add a new moon to the universe.
	 *
	 * @pre                       @p moon.id() is unique for all objects in
	 *                            @ref moons_.
	 *
	 * @param moon                The moon to add (move) to the universe.
	 */
	void add(tmoon&& moon);

	/**
	 * Add a new planet to the universe.
	 *
	 * @pre                       @p planet.id() is unique for all objects in
	 *                            @ref planets_.
	 *
	 * @param planet              The planet to add (move) to the universe.
	 */
	void add(tplanet&& planet);


	/***** ***** ***** ***** Setters and getters. ***** ***** ***** *****/

	const std::vector<tsun>& suns() const;

	const std::vector<tmoon>& moons() const;

	const std::vector<tplanet>& planets() const;


	/***** ***** ***** ***** Members. ***** ***** ***** *****/
private:
	/** Contains the suns in the universe. */
	std::vector<tsun> suns_{};

	/** Contains the moons in the universe. */
	std::vector<tmoon> moons_{};

	/** Contains the planets in the universe. */
	std::vector<tplanet> planets_{};
};

} // namespace celestial

#endif

