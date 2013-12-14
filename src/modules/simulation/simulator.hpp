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

#ifndef MODULES_SIMULATION_SIMULATOR_HPP_INCLUDED
#define MODULES_SIMULATION_SIMULATOR_HPP_INCLUDED

#include "modules/celestial/universe.hpp"

#include "modules/simulation/detail/state.hpp"

#include <vector>

namespace simulation
{

/**
 * The simulator, the base of the simulation engine.
 */
class tsimulator
{
public:
	/***** Constructors, assign operators, destructor. *****/

	tsimulator() = delete;

	explicit tsimulator(celestial::tuniverse&& universe__);

	~tsimulator() = default;

	tsimulator& operator=(tsimulator&&) = default;
	tsimulator(tsimulator&&) = default;

	tsimulator& operator=(const tsimulator&) = delete;
	tsimulator(const tsimulator&) = delete;


	/***** ***** ***** Load and store operations. ***** ***** *****/

private:
	/**
	 * Constructor.
	 *
	 * @note This function has no unit test, since the required test code would
	 * be quite verbose, so relay on the tests for the subcomponents to do the
	 * right thing (tm).
	 *
	 * @pre                       @p simulator contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param simulator           The property tree containing the @p simulator
	 *                            data.
	 */
	tsimulator(const boost::property_tree::ptree& simulator);

public:
	/**
	 * Creates a new @ref simulation::tsimulator object from a property tree.
	 *
	 * This function, unlike the constructor, is able to convert older versions
	 * of the property tree to the current version.
	 *
	 * @note This function has no unit test, since the required test code would
	 * be quite verbose, so relay on the tests for the subcomponents to do the
	 * right thing (tm).
	 *
	 * @pre                       @p simulator contains a property tree as
	 *                            created by @ref store.
	 *
	 * @param simulator           The property tree containing the @p simulator
	 *                            data.
	 *
	 * @returns                   The created property object.
	 */
	static tsimulator load(const boost::property_tree::ptree& simulator);

	/**
	 * Creates a new @ref simulation::tsimulator object from a file.
	 *
	 * @note This function has no unit test, since the required test code would
	 * be quite verbose, so relay on the tests for the subcomponents to do the
	 * right thing (tm).
	 *
	 * @pre                       @p filename points to a file containing a
	 *                            property tree as created by @ref store.
	 *
	 * @param filename            The file to be loaded.
	 *
	 * @returns                   The created property object.
	 */
	static tsimulator load(const std::string& filename);

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

	/**
	 * Stores the representation of the object in a file.
	 *
	 * @note This function has no unit test, since the required test code would
	 * be quite verbose, so relay on the tests for the subcomponents to do the
	 * right thing (tm).
	 *
	 * @param filename            The file to store the data in.
	 */
	void store(const std::string& filename) const;


	/***** ***** ***** ***** Operations. ***** ***** ***** *****/

	/**
	 * Runs the simulator for a certain period.
	 *
	 * @param seconds             The number of seconds the simulation should
	 *                            run. Every second is one iteration.
	 */
	void run(const unit::ttime seconds);


	/***** ***** ***** ***** Members. ***** ***** ***** *****/

private:
	/**
	 * The universe the simulation runs on.
	 *
	 * This contains the initial values of the simulation.
	 */
	celestial::tuniverse universe_;

	/** The various states in the simulation. */
	std::vector<detail::tstate> states_{};

	/** Updates the positions of all celestial bodies. */
	void update_positions();
};

} // namespace simulation

#endif
