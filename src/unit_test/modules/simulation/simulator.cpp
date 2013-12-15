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

#include "modules/simulation/simulator.hpp"

#include "lib/raster/raster.tpp"
#include "modules/grid/stream.hpp"

#include <boost/test/unit_test.hpp>

using namespace simulation;

struct tunit_test
{
	/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

	static void no_collision()
	{
		celestial::tuniverse universe;
		universe.add(celestial::tsun{
				"sun1", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 0._deg, 90._deg}, 40_s,
								 0_s},
				0.01_m, 1_J});

		universe.add(celestial::tsun{
				"sun2", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 90._deg, 90._deg},
								 40_s, 0_s},
				0.01_m, 1_J});

		universe.add(celestial::tmoon{
				"moon1", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 180._deg, 90._deg},
								 40_s, 0_s},
				0.01_m});

		universe.add(celestial::tmoon{
				"moon2", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 270._deg, 90._deg},
								 40_s, 0_s},
				0.01_m});

		tsimulator simulation(std::move(universe));
		simulation.run(42_s);
	}

	/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

	static void sun_collision()
	{
		celestial::tuniverse universe;
		universe.add(celestial::tsun{
				"sun1", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 0._deg, 90._deg}, 40_s,
								 0_s},
				0.001_m, 1_J});

		universe.add(celestial::tsun{
				"sun2", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 90._deg, 90._deg}, 1_s,
								 0_s},
				0.001_m, 1_J});

		universe.add(celestial::tmoon{
				"moon1", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 180._deg, 90._deg},
								 40_s, 0_s},
				0.01_m});

		universe.add(celestial::tmoon{
				"moon2", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 270._deg, 90._deg},
								 40_s, 0_s},
				0.01_m});

		tsimulator simulation(std::move(universe));
		BOOST_CHECK_THROW(simulation.run(42_s), tsimulator::tcollision);

		BOOST_REQUIRE_EQUAL(simulation.states_.back().suns.size(), 2);
		BOOST_CHECK_EQUAL(
				lib::raster(simulation.states_.back().suns[0].position),
				lib::raster(simulation.states_.back().suns[1].position));
	}

	/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

	static void sun_moon_collision()
	{
		celestial::tuniverse universe;
		universe.add(celestial::tsun{
				"sun1", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 0._deg, 90._deg}, 40_s,
								 0_s},
				0.01_m, 1_J});

		universe.add(celestial::tsun{
				"sun2", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 90._deg, 90._deg},
								 40_s, 0_s},
				0.001_m, 1_J});

		universe.add(celestial::tmoon{
				"moon1", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 180._deg, 90._deg},
								 1_s, 0_s},
				0.001_m});

		universe.add(celestial::tmoon{
				"moon2", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 270._deg, 90._deg},
								 40_s, 0_s},
				0.01_m});

		tsimulator simulation(std::move(universe));
		BOOST_CHECK_THROW(simulation.run(42_s), tsimulator::tcollision);

		BOOST_REQUIRE_EQUAL(simulation.states_.back().suns.size(), 2);
		BOOST_REQUIRE_EQUAL(simulation.states_.back().moons.size(), 2);
		BOOST_CHECK_EQUAL(
				lib::raster(simulation.states_.back().suns[1].position),
				lib::raster(simulation.states_.back().moons[0].position));
	}

	/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

	static void moon_moon_collision()
	{
		celestial::tuniverse universe;
		universe.add(celestial::tsun{
				"sun1", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 0._deg, 90._deg}, 40_s,
								 0_s},
				0.01_m, 1_J});

		universe.add(celestial::tsun{
				"sun2", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 90._deg, 90._deg},
								 40_s, 0_s},
				0.01_m, 1_J});

		universe.add(celestial::tmoon{
				"moon1", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 180._deg, 90._deg},
								 40_s, 0_s},
				0.001_m});

		universe.add(celestial::tmoon{
				"moon2", geometry::tcartesian{0_m, 0_m, 0_m},
				geometry::torbit{geometry::tpolar{0.1_m, 270._deg, 90._deg},
								 1_s, 0_s},
				0.001_m});

		tsimulator simulation(std::move(universe));
		BOOST_CHECK_THROW(simulation.run(42_s), tsimulator::tcollision);

		BOOST_REQUIRE_EQUAL(simulation.states_.back().moons.size(), 2);
		BOOST_CHECK_EQUAL(
				lib::raster(simulation.states_.back().moons[0].position),
				lib::raster(simulation.states_.back().moons[1].position));
	}
};

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

BOOST_AUTO_TEST_CASE(test_modules_simulation_simulator)
{
	tunit_test::no_collision();
	tunit_test::sun_collision();
	tunit_test::sun_moon_collision();
	tunit_test::moon_moon_collision();
}
