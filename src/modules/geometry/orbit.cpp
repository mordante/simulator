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

#include "modules/geometry/orbit.hpp"

#include "lib/exception/throw.tpp"
#include "modules/geometry/cartesian.hpp"
#include "modules/logger/logger.hpp"
#include "modules/unit/ptree.tpp"
#include "modules/unit/quantity/comparison.tpp"
#include "modules/unit/value.tpp"

REGISTER_LOGGER_MODULE("/modules/unit")

namespace geometry
{

torbit::torbit(const boost::property_tree::ptree& orbit)
	: torbit(tpolar::load(orbit.get_child("rotation")),
			 orbit.get<unit::ttime>("rotation_period_theta_plane"),
			 orbit.get<unit::ttime>("rotation_period_phi_plane"))
{
	TRACE;
}

torbit torbit::load(const boost::property_tree::ptree& orbit)
{
	TRACE;

	switch(const int version{orbit.get<int>("version")}) {
		case 1:
			return torbit(orbit);

		default:
			THROW_F(load_invalid_version,
					"Failed to load an orbit object, version »",
					version,
					"« is not supported.");
	}
}

boost::property_tree::ptree torbit::store() const
{
	TRACE;

	boost::property_tree::ptree result;

	result.put("version", 1);
	result.push_back(boost::property_tree::ptree::value_type{"rotation",
															 rotation.store()});
	result.put("rotation_period_theta_plane", rotation_period_theta_plane);
	result.put("rotation_period_phi_plane", rotation_period_phi_plane);

	return result;
}

static constexpr unit::tangle
rotation_angle(unit::ttime time, const unit::ttime period)
{
	/*
	 * The type is used for casting from the intergral ttime type to the
	 * floating point tangle type.
	 */
	using ttype = unit::tangle::type;

	/* If the period == 0_s there is no rotation. */
	if(period == 0_s) {
		return 0_rad;
	}

	/* Promote the T's of the unit:ttime to the T of unit:tangle. */
	unit::tquantity<unit::S, ttype> t{static_cast<ttype>(time.value)};
	unit::tquantity<unit::S, ttype> p{static_cast<ttype>(period.value)};

	/*
	 * Determine the result.
	 *
	 * Note the quotient can be > 1 if the time is multiple periods, however
	 * this has no effect on the calculation.
	 */
	unit::tvalue quotient{t / p};
	return unit::pi<ttype>(2.) * quotient;
}

tcartesian torbit::position(const unit::ttime time) const
{
	TRACE;

	/* Position at time == 0 */
	tpolar result{rotation};

	/* Adjust for the rotation in the theta plane. */
	const unit::tangle theta_rotation{
			rotation_angle(time, rotation_period_theta_plane)};

	result.theta += theta_rotation;

	/* Adjust for the rotation in the phi plane. */
	const unit::tangle phi_rotation{
			rotation_angle(time, rotation_period_phi_plane)};
	result.phi += phi_rotation;

	/* Return result. */
	return static_cast<tcartesian>(result);
}

} // namespace geometry
