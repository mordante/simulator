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

#ifndef MODULES_UNIT_UNIT_TPP_INCLUDED
#define MODULES_UNIT_UNIT_TPP_INCLUDED

/**
 * @file
 * Contains the @ref unit::tunit class.
 *
 * This class is the basis for the unit calculations. It also contains some
 * helper structs for the usage of units.
 *
 * Since the unit contains no code, the file has no unit tests.
 *
 * See @ref unit_module for more information.
 */

namespace unit
{

/**
 * The class to define a unit.
 *
 * The class uses template parameters to notate the number of times a SI-unit
 * is present in the unit. (The number of times is the power of the unit.)
 *
 * Derived SI-units are normally defined by setting the proper powers, but
 * there might be some exceptions.
 *
 * @tparam M                      The metre unit.
 * @tparam KG                     The kg unit.
 * @tparam S                      The second unit.
 * @tparam K                      The Kelvin unit.
 * @tparam RAD                    The radian unit. This is not a real SI-unit;
 *                                its definition is m/m. However using the
 *                                radians as a real unit makes parts of the
 *                                code easier.
 */
template <int M, int KG, int S, int K, int RAD>
struct tunit
{
	/** Helper enum to make the template parameters 'visible' at runtime. */
	enum {
		m = M,
		kg = KG,
		s = S,
		k = K,
		rad = RAD
	};
};

/** Defines a dimensionless unit. */
using NONE = tunit<0, 0, 0, 0, 0>;


/** Defines the metre unit. */
using M = tunit<1, 0, 0, 0, 0>;

/** Defines the kilogramme unit. */
using KG = tunit<0, 1, 0, 0, 0>;

/** Defines the second unit. */
using S = tunit<0, 0, 1, 0, 0>;

/** Defines the radian unit. */
using RAD = tunit<0, 0, 0, 0, 1>;


/** Defines the Newton unit. */
using N = tunit<1, 1, -2, 0, 0>;

/** Defines the Joule unit. */
using J = tunit<2, 1, -2, 0, 0>;

namespace detail
{

/**
 * Helper class for adding to units together.
 *
 * This is used when two units are multiplied.
 *
 * @tparam LHS                    The type of the lhs side of the
 *                                multiplication.
 * @tparam RHS                    The type of the rhs side of the
 *                                multiplication.
 */
template <class LHS, class RHS>
struct tadd
{
	/** The type resulted by the multiplication. */
	using type = tunit<LHS::m + RHS::m,
					   LHS::kg + RHS::kg,
					   LHS::s + RHS::s,
					   LHS::k + RHS::k,
					   LHS::rad + RHS::rad>;
};

/**
 * Helper class for adding to units together.
 *
 * This is used when two units are divided.
 *
 * @tparam LHS                    The type of the lhs side of the division.
 * @tparam RHS                    The type of the rhs side of the division.
 */
template <class LHS, class RHS>
struct tsubtract
{
	/** The type resulted by the division */
	using type = tunit<LHS::m - RHS::m,
					   LHS::kg - RHS::kg,
					   LHS::s - RHS::s,
					   LHS::k - RHS::k,
					   LHS::rad - RHS::rad>;
};

/**
 * Helper class for taking the square root of a unit.
 *
 * @note Since units are integral values and the square root halves a value
 * only even values (and zero) are allowed to have their square root taken.
 *
 * @tparam U                      The type to take the square root from.
 */
template <class U>
struct tsqrt
{
	static_assert(U::m % 2 == 0, "The square root of an odd »m« is undefined.");

	static_assert(U::kg % 2 == 0,
				  "The square root of an odd »kg« is undefined.");

	static_assert(U::s % 2 == 0, "The square root of an odd »s« is undefined.");

	static_assert(U::k % 2 == 0, "The square root of an odd »k« is undefined.");

	static_assert(U::rad % 2 == 0,
				  "The square root of an odd »rad« is undefined.");

	/** The type resulted by the square root */
	using type = tunit<U::m / 2, U::kg / 2, U::s / 2, U::k / 2, U::rad / 2>;
};

} // namespace detail

/** Helper wrapper for @ref detail::tadd. */
template <class LHS, class RHS>
using tadd = typename detail::tadd<LHS, RHS>::type;

/** Helper wrapper for @ref detail::tsubtract */
template <class LHS, class RHS>
using tsubtract = typename detail::tsubtract<LHS, RHS>::type;

/** Helper wrapper for @ref detail::tsqrt */
template <class U>
using tsqrt = typename detail::tsqrt<U>::type;

} // unit

#endif
