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

#ifndef MODULES_SIMULATION_DETAIL_STATE_HPP_INCLUDED
#define MODULES_SIMULATION_DETAIL_STATE_HPP_INCLUDED

#include "modules/unit/time.tpp"
#include "modules/simulation/detail/sun.hpp"
#include "modules/simulation/detail/moon.hpp"

#include <vector>

namespace simulation
{

namespace detail
{

struct tstate
{
	/***** Constructors, assign operators, destructor. *****/

	tstate() = delete;

	explicit tstate(unit::ttime time__);

	~tstate() = default;

	tstate& operator=(tstate&&) = default;
	tstate(tstate&&) = default;

	tstate& operator=(const tstate&) = delete;
	tstate(const tstate&) = delete;

private:
	/**
	 * Constructor.
	 *
	 * @note This function has no unit test, since the required test code would
	 * be quite verbose, so relay on the tests for the subcomponents to do the
	 * right thing (tm).
	 *
	 * @pre                       @p state contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param state               The property tree containing the @p state
	 *                            data.
	 */
	tstate(const boost::property_tree::ptree& state);

public:
	/**
	 * Creates a new @ref simulation::detail::tstate object from a property
	 * tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @note This function has no unit test, since the required test code would
	 * be quite verbose, so relay on the tests for the subcomponents to do the
	 * right thing (tm).
	 *
	 * @pre                       @p state contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param state               The property tree containing the @p state
	 *                            data.
	 *
	 * @returns                   The created property object.
	 */
	static tstate load(const boost::property_tree::ptree& state);

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


	/***** ***** ***** ***** Members. ***** ***** ***** *****/

	/**
	 * The time of the current in the universe.
	 *
	 * Every iteration of the simulator the state of the universe changes. This
	 * indicates the time in the universe at which this state was reached.
	 */
	unit::ttime time;

	/** The state for all suns in the universe. */
	std::vector<tsun> suns{};

	/** The state for all suns in the universe. */
	std::vector<tmoon> moons{};
};

} // namespace detail

} // namespace simulation

#endif
