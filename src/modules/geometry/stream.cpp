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

#include "modules/geometry/stream.hpp"

#include "modules/geometry/cartesian.hpp"
#include "modules/geometry/orbit.hpp"
#include "modules/unit/quantity/stream.hpp"

#include <ostream>

namespace geometry
{

std::ostream& operator<<(std::ostream& ostream, const tcartesian& cartesian)
{
	return ostream << "cartesian[" << cartesian.x << ", " << cartesian.y << ", "
				   << cartesian.z << "]";
}

std::ostream& operator<<(std::ostream& ostream, const torbit& orbit)
{
	return ostream << "orbit[\n"
				   << "\trotation[" << orbit.rotation << "]\n"
				   << "\trotation_period_theta_plane["
				   << orbit.rotation_period_theta_plane << "]\n"
				   << "\trotation_period_phi_plane["
				   << orbit.rotation_period_phi_plane << "]\n"
				   << "]";
}

std::ostream& operator<<(std::ostream& ostream, const tpolar& polar)
{
	return ostream << "polar[" << polar.r << ", " << polar.theta << ", "
				   << polar.phi << "]";
}

} // namespace geometry
