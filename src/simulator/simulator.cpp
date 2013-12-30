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

#include "lib/exception/exception.hpp"
#include "modules/logger/logger.hpp"
#include "modules/simulation/simulator.hpp"
#include "simulator/options.hpp"

#include <boost/property_tree/xml_parser.hpp>

#include <iostream>

REGISTER_LOGGER_MODULE("/simulator")

static simulation::tsimulator load()
{
	TRACE;

	if(!toptions::instance().input_file.empty()) {
		try
		{
			return simulation::tsimulator::load(
					toptions::instance().input_file);
		}

		catch(const boost::property_tree::xml_parser_error& e)
		{
			LOG_E("Load failure using defaults, errno »", e.what(), "«.");
		}
		catch(...)
		{
			LOG_E("Unknown load failure using defaults.");
		}
	}

	celestial::tuniverse universe;
	universe.add(celestial::tsun{
			"Greater sun", geometry::tcartesian{0_m, 0_m, 0_m},
			geometry::torbit{geometry::tpolar{0.01_m, 0._deg, 90._deg}, 4_s,
							 16_s},
			0.002_m, 1_J});
	universe.add(celestial::tsun{
			"Lesser sun", geometry::tcartesian{0_m, 0_m, 0_m},
			geometry::torbit{geometry::tpolar{0.1_m, 0._deg, 90._deg}, 16_s,
							 256_s},
			0.001_m, 1_J});

	universe.add(celestial::tmoon{
			"Zar", geometry::tcartesian{0_m, 0_m, 0_m},
			geometry::torbit{geometry::tpolar{1_m, 0._deg, 90._deg}, 16_s,
							 256_s},
			0.001_m});

	universe.add(celestial::tplanet{"The continent",
									geometry::tcartesian{-0.2_m, -0.2_m, 0_m},
									0.4_m, 0.4_m});

	return simulation::tsimulator(std::move(universe));
}

int main(const int argc, const char* argv[])
{
	TRACE_PARAMETERS(argc);

	try
	{
		if(!toptions::parse(argc, const_cast<const char**>(argv))) {
			toptions::show_help();
			return EXIT_FAILURE;
		}

		if(toptions::instance().help) {
			toptions::show_help();
			return EXIT_SUCCESS;
		}

		simulation::tsimulator simulator{load()};
		try
		{
			simulator.run(
					unit::ttime(toptions::instance().simulator_iterations));
		}
		catch(const simulation::tsimulator::tcollision&)
		{
			LOG_F("There was a collision in the universe simulation aborted.");
		}

		if(!toptions::instance().output_file.empty()) {
			try
			{
				simulator.store(toptions::instance().output_file);
			}
			catch(const boost::property_tree::xml_parser_error& e)
			{
				LOG_E("Save failure, errno »", e.what(), "«.");
			}
		}
	}
	catch(const lib::texception& e)
	{
		LOG_F("Caught exception »",
			  e.type,
			  "« with message »",
			  e.message,
			  "«.");

		return EXIT_FAILURE;
	}
	catch(const std::exception& e)
	{
		LOG_F("Caught a standard exception with message »", e.what(), "«.");
		return EXIT_FAILURE;
	}
	catch(...)
	{
		LOG_F("Caught an unknown exception.");
		return EXIT_FAILURE;
	}
}
