
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

/**
 * @page celestial_module The celestial module
 *
 * The celestial module contains the universe and its celestial bodies:
 * * suns
 * * moons
 *
 *
 * @section celestial_module_moon Moon
 *
 * A moon is an orbiting object in a universe. Its only 'task' is to reflect
 * the light of a sun or to (partly) hide it.
 *
 *
 * @section celestial_module_sun Sun
 *
 * A sun is an orbiting object in a universe. Its task is to provide
 * energy/light which can be used on a planet to evolve. The universe has no
 * stars but might get one later, a sun may be abused for it, but might provide
 * odd things. For example in the initial version light travels at infinite
 * speed, so the light of a sun is directly at a planet.
 */
