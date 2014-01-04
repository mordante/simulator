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

#ifndef MODULES_UNIT_QUANTITY_TRIGONOMETRY_TPP_INCLUDED
#define MODULES_UNIT_QUANTITY_TRIGONOMETRY_TPP_INCLUDED

/**
 * @file
 * Contains the trigonometry operations for @ref unit::tquantity.
 *
 * The operations are extended by a pi function which returns a value in
 * radians.
 *
 * See @ref unit_module for more information.
 */

#include "modules/unit/quantity.tpp"

#include <boost/math/constants/constants.hpp>

#include <cmath>

namespace unit
{

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Sine                                                              *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The sine of a @ref unit::tquantity object.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::numeric_limits<T>::min_exponent != 0
 *                                @endcode
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The object to operate upon.
 *
 * @returns                       The object created calculating the sine of
 *                                @p quantity.
 */
template <class U, class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::min_exponent
										 != 0,
										 tquantity<tsubtract<U, RAD>, T>>::type
sin(const tquantity<U, T>& quantity) noexcept(noexcept(sin(quantity.value)))
{
	using std::sin;
	return tquantity<tsubtract<U, RAD>, T>{static_cast<T>(sin(quantity.value))};
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Cosine                                                            *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The cosine of a @ref unit::tquantity object.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::numeric_limits<T>::min_exponent != 0
 *                                @endcode
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The object to operate upon.
 *
 * @returns                       The object created calculating the cosine of
 *                                @p quantity.
 */
template <class U, class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::min_exponent
										 != 0,
										 tquantity<tsubtract<U, RAD>, T>>::type
cos(const tquantity<U, T>& quantity) noexcept(noexcept(cos(quantity.value)))
{
	using std::cos;
	return tquantity<tsubtract<U, RAD>, T>{static_cast<T>(cos(quantity.value))};
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Tangent                                                           *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The tangent of a @ref unit::tquantity object.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::numeric_limits<T>::min_exponent != 0
 *                                @endcode
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The object to operate upon.
 *
 * @returns                       The object created calculating the tangent of
 *                                @p quantity.
 */
template <class U, class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::min_exponent
										 != 0,
										 tquantity<tsubtract<U, RAD>, T>>::type
tan(const tquantity<U, T>& quantity) noexcept(noexcept(tan(quantity.value)))
{
	using std::tan;
	return tquantity<tsubtract<U, RAD>, T>{static_cast<T>(tan(quantity.value))};
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Arcsine                                                           *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The arcsine of a @ref unit::tquantity object.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::numeric_limits<T>::min_exponent != 0
 *                                @endcode
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The object to operate upon.
 *
 * @returns                       The object created calculating the arcsine of
 *                                @p quantity.
 */
template <class U, class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::min_exponent
										 != 0,
										 tquantity<tadd<U, RAD>, T>>::type
asin(tquantity<U, T> quantity) noexcept(noexcept(asin(quantity.value)))
{
	using std::asin;
	return tquantity<tadd<U, RAD>, T>{static_cast<T>(asin(quantity.value))};
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Arccosine                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The arccosine of a @ref unit::tquantity object.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::numeric_limits<T>::min_exponent != 0
 *                                @endcode
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The object to operate upon.
 *
 * @returns                       The object created calculating the arccosine
 *                                of @p quantity.
 */
template <class U, class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::min_exponent
										 != 0,
										 tquantity<tadd<U, RAD>, T>>::type
acos(tquantity<U, T> quantity) noexcept(noexcept(acos(quantity.value)))
{
	using std::acos;
	return tquantity<tadd<U, RAD>, T>{static_cast<T>(acos(quantity.value))};
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Arctangent                                                        *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The arctangent of a @ref unit::tquantity object.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::numeric_limits<T>::min_exponent != 0
 *                                @endcode
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The object to operate upon.
 *
 * @returns                       The object created calculating the arctangent
 *                                of @p quantity.
 */
template <class U, class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::min_exponent
										 != 0,
										 tquantity<tadd<U, RAD>, T>>::type
atan(tquantity<U, T> quantity) noexcept(noexcept(atan(quantity.value)))
{
	using std::atan;
	return tquantity<tadd<U, RAD>, T>{static_cast<T>(atan(quantity.value))};
}

/**
 * The arctangent of two @ref unit::tquantity objects.
 *
 * @note This function is normally called atan2, but with overloading the extra
 * name is not required.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::numeric_limits<T>::min_exponent != 0
 *                                @endcode
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param y                       The object used as y value in atan2.
 * @param x                       The object used as x value in atan2.
 *
 * @returns                       The object created calculating the arctangent
 *                                of @p quantity, using two input object.
 */
template <class U, class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::min_exponent
										 != 0,
										 tquantity<RAD, T>>::type
atan(tquantity<U, T> y,
	 tquantity<U, T> x) noexcept(noexcept(atan2(y.value, x.value)))
{
	using std::atan;
	return tquantity<RAD, T>{static_cast<T>(atan2(y.value, x.value))};
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Pi                                                               *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * Creates a @ref unit::tquantity containing pi radians.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::numeric_limits<T>::min_exponent != 0
 *                                @endcode
 *
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @returns                       The object created from the value pi.
 */
template <class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::min_exponent
										 != 0,
										 tquantity<RAD, T>>::type
pi() noexcept(noexcept(boost::math::constants::pi<T>()))
{
	return tquantity<RAD, T>{boost::math::constants::pi<T>()};
}

/**
 * Creates a @ref unit::tquantity containing @p factor pi radians.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::numeric_limits<T>::min_exponent != 0
 *                                @endcode
 *
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param factor                  The value to multiply the result with.
 *
 * @returns                       The object created from the value pi times
 *                                @p factor.
 */
template <class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::min_exponent
										 != 0,
										 tquantity<RAD, T>>::type
pi(const double factor) noexcept(noexcept(boost::math::constants::pi<T>()))
{
	return tquantity<RAD, T>{factor * boost::math::constants::pi<T>()};
}

} // namespace unit

#endif
