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

#include "simulator/options.hpp"

#include "lib/exception/validate.tpp"
#include "modules/logger/logger.hpp"

#include <boost/lexical_cast.hpp>

REGISTER_LOGGER_MODULE("/simulator")

bool toptions::parse(const int argc, const char* argv[])
{
	TRACE_PARAMETERS(argc);

	toptions& result = singleton(false);
	result.parsed_ = true;

	/***** Parse the input. *****/
	int i = 1;
	while(i < argc) {
		if(strcmp(argv[i], "-h") == 0) {
			result.help = true;
			if(argc != 2) {
				LOG_E("The -h argument can't be combined with other "
					  "arguments.");
				return false;
			}
		} else if(strcmp(argv[i], "-r") == 0) {
			result.simulator_iterations = boost::lexical_cast<int>(argv[i]);
		} else {
			result.input_file = argv[i];
			result.output_file = argv[i];
			if(i + 1 != argc) {
				LOG_E("The FILE must be the last argument.");
				return false;
			}
		}
		++i;
	}

	/***** Validate the settings. *****/

	return true;
}

const toptions& toptions::instance()
{
	TRACE;

	static toptions& result = singleton(true);
	return result;
}

void toptions::show_help()
{
	TRACE;

	std::cout << R"(Usage:
 - similator [OPTION...] [FILE]
 - similator -h
Starts the similator program

Configuration selection:
-r RUN  Run the simulator RUN steps.

Miscellaneous:
-h      Prints this help message and exists.

The exit status is 0 upon success and 1 upon failure.)";
}

toptions& toptions::singleton(const bool parsed_status)
{
	static toptions result;
	VALIDATE(result.parsed_ == parsed_status);
	return result;
}
