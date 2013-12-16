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

#ifndef SIMULATOR_OPTIONS_HPP_INCLUDED
#define SIMULATOR_OPTIONS_HPP_INCLUDED

#include <string>

/** The command line options send to the program. */
class toptions final
{
private:
	/***** Constructors, assign operators, destructor. *****/

	toptions() = default;

public:
	~toptions() = default;

	toptions& operator=(toptions&&) = delete;
	toptions(toptions&&) = delete;

	toptions& operator=(const toptions&) = delete;
	toptions(const toptions&) = delete;


	/***** ***** ***** Load and store operations. ***** ***** *****/

	/**
	 * Parses the command line options.
	 *
	 * @pre                       This function has not been called before.
	 *
	 * @param argc                The @p argc send to @c main.
	 * @param argv                The @p argv send to @c main.
	 *
	 * @returns                   The status:
	 *                            - @c true if all is well.
	 *                            - @c false when an error occurred.
	 */
	static bool parse(const int argc, const char* argv[]);

	/**
	 * Returns a singleton of the options.
	 *
	 * @pre                       The function @ref parse has been called
	 *                            before.
	 *
	 * @returns                   The parsed options.
	 */
	static const toptions& instance();


	/***** ***** Operations. ***** *****/

	/** Shows a help message. */
	static void show_help();


	/***** ***** Members. ***** *****/

	/** The file to read the simulation status from. */
	std::string input_file{};

	/** The file to write the simulation status to. */
	std::string output_file{};

	/** The number of iterations the simulation should run. */
	int simulator_iterations{1};

	/** Show a help message instead of running the simulator? */
	bool help{false};

private:
	/** Has the function @ref parse been called before. */
	bool parsed_{false};


	/***** ***** Operations. ***** *****/

	/**
	 * Returns a singleton of the options.
	 *
	 * @pre                       The following assertion holds:
	 *                            @code parsed_status == parsed_; @endcode
	 *
	 * @param parsed_status       The expected parsed status upon entry.
	 *
	 * @returns                   The options.
	 */
	static toptions& singleton(const bool parsed_status);
};

#endif
