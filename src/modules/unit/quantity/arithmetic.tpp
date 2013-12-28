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

#ifndef MODULES_UNIT_QUANTITY_ARITHMETIC_TPP_INCLUDED
#define MODULES_UNIT_QUANTITY_ARITHMETIC_TPP_INCLUDED

/**
 * @file
 * Contains the arithmetic operators for @ref unit::tquantity.
 *
 * This file also adds some generic functions, closely related to the
 * arithmetic operators.
 *
 * See @ref unit_module for more information.
 */

#include "modules/unit/quantity.tpp"

namespace unit
{

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator+                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator+= for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after adding @p rhs to it.
 */
template <class U, class T>
inline constexpr tquantity<U, T>&
operator+=(tquantity<U, T>& lhs,
		   const tquantity
		   <U, T>& rhs) noexcept(noexcept(lhs.value += rhs.value))
{
	lhs.value += rhs.value;
	return lhs;
}

/**
 * The @c operator+ for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by adding @p lhs and
 *                                @p rhs.
 */
template <class U, class T>
inline constexpr tquantity<U, T>
operator+(tquantity<U, T> lhs,
		  const tquantity<U, T>& rhs) noexcept(noexcept(lhs += rhs))
{
	return lhs += rhs;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator++                                                        *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator++ for a @ref unit::tquantity object.
 *
 * @note The function is only enable for intergral type, not for floating point
 * types.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after increasing its value by @c 1.
 */
template <class U, class T>
inline constexpr typename std::enable_if
		<std::numeric_limits<T>::min_exponent == 0, tquantity<U, T>&>::type
operator++(tquantity<U, T>& lhs) noexcept(noexcept(++lhs.value))
{
	++lhs.value;
	return lhs;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator-                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator-= for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after subtracting @p rhs from it.
 */
template <class U, class T>
inline constexpr tquantity<U, T>&
operator-=(tquantity<U, T>& lhs,
		   const tquantity
		   <U, T>& rhs) noexcept(noexcept(lhs.value -= rhs.value))
{
	lhs.value -= rhs.value;
	return lhs;
}

/**
 * The @c operator- for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by subtracting @p rhs from
 *                                @p lhs.
 */
template <class U, class T>
inline constexpr tquantity<U, T>
operator-(tquantity<U, T> lhs,
		  const tquantity<U, T>& rhs) noexcept(noexcept(lhs -= rhs))
{
	return lhs -= rhs;
}

/**
 * The unary @c operator- for a @ref unit::tquantity object.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The object to operate upon.
 *
 * @returns                       The object created taking the negative value
 *                                of @p quantity.
 */
template <class U, class T>
inline constexpr tquantity<U, T>
operator-(tquantity<U, T> quantity) noexcept(noexcept(-quantity.value))
{
	quantity.value = -quantity.value;
	return quantity;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator*                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator*= for two @ref unit::tquantity objects.
 *
 * @note Since operator*= can't change the type of the value it can't be
 * multiplied with a quantity that has a dimension.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after multiplying it by @p rhs.
 */
template <class U, class T>
inline constexpr tquantity<U, T>&
operator*=(tquantity<U, T>& lhs,
		   const tquantity
		   <NONE, T>& rhs) noexcept(noexcept(lhs.value *= rhs.value))
{
	lhs.value *= rhs.value;
	return lhs;
}

/**
 * The @c operator*= for two @ref unit::tquantity objects.
 *
 * @note Since operator*= can't change the type of the value it can't be
 * multiplied with a quantity that has a dimension.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam LHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p lhs parameter.
 * @tparam RHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p rhs parameter.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after multiplying it by @p rhs.
 */
template <class U, class LHS_T, class RHS_T>
inline constexpr tquantity<U, LHS_T>&
operator*=(tquantity<U, LHS_T>& lhs,
		   const RHS_T
		   & rhs) noexcept(noexcept(lhs.value *= static_cast<RHS_T>(rhs)))
{
	lhs.value *= static_cast<LHS_T>(rhs);
	return lhs;
}

/**
 * The @c operator* for two @ref unit::tquantity objects.
 *
 * @tparam LHS_U                  The type of @ref unit::tquantity::unit for the
 *                                @p lhs parameter.
 * @tparam LHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p lhs parameter.
 * @tparam RHS_U                  The type of @ref unit::tquantity::unit for the
 *                                @p rhs parameter.
 * @tparam RHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p rhs parameter.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by multiplying @p lhs and
 *                                @p rhs.
 */
template <class LHS_U, class LHS_T, class RHS_U, class RHS_T>
inline constexpr tquantity
		<tadd<LHS_U, RHS_U>, typename std::common_type<LHS_T, RHS_T>::type>
		/*
		 * Formatter fails; the * is an multiplication not a pointer.
		 * Look like http://llvm.org/bugs/show_bug.cgi?id=16500
		 */
operator*(const tquantity<LHS_U, LHS_T>& lhs,
		  const tquantity
		  <RHS_U, RHS_T>& rhs) noexcept(noexcept(lhs.value* rhs.value))
{
	using type = typename std::common_type<LHS_T, RHS_T>::type;

	return tquantity<tadd<LHS_U, RHS_U>, type>{static_cast<type>(lhs.value)
											   * static_cast<type>(rhs.value)};
}

/**
 * The @c operator* for a @ref unit::tquantity object with a value.
 *
 * This is a scaling operation for the @p lhs object.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side value.
 *
 * @returns                       The object created by multiplying @p lhs and
 *                                @p rhs.
 */
template <class U, class T>
inline constexpr tquantity<U, T>
operator*(tquantity<U, T> lhs, const T& rhs) noexcept(noexcept(lhs *= rhs))
{
	return lhs *= rhs;
}

/**
 * The @c operator* for a @ref unit::tquantity object with a value.
 *
 * This is a scaling operation for the @p rhs object.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side value.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by multiplying @p lhs and
 *                                @p rhs.
 */
template <class U, class T>
inline constexpr tquantity<U, T>
operator*(const T& lhs, tquantity<U, T> rhs) noexcept(noexcept(rhs *= lhs))
{
	return rhs *= lhs;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator/                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator/= for a @ref unit::tquantity object with a value.
 *
 * This is a scaling operation for the @p lhs object.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam LHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p lhs parameter.
 * @tparam RHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p rhs parameter.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side value.
 *
 * @returns                       @p lhs after dividin it by @p rhs.
 */
template <class U, class LHS_T, class RHS_T>
inline constexpr tquantity<U, LHS_T>&
operator/=(tquantity<U, LHS_T>& lhs,
		   const RHS_T
		   & rhs) noexcept(noexcept(lhs.value /= static_cast<LHS_T>(rhs)))
{
	lhs.value /= static_cast<LHS_T>(rhs);
	return lhs;
}

/**
 * The @c operator/ for two @ref unit::tquantity objects.
 *
 * @tparam LHS_U                  The type of @ref unit::tquantity::unit for the
 *                                @p lhs parameter.
 * @tparam LHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p lhs parameter.
 * @tparam RHS_U                  The type of @ref unit::tquantity::unit for the
 *                                @p rhs parameter.
 * @tparam RHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p rhs parameter.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by dividing @p lhs by
 *                                @p rhs.
 */
template <class LHS_U, class LHS_T, class RHS_U, class RHS_T>
inline constexpr tquantity
		<tsubtract<LHS_U, RHS_U>, typename std::common_type<LHS_T, RHS_T>::type>
operator/(const tquantity<LHS_U, LHS_T>& lhs,
		  const tquantity
		  <RHS_U, RHS_T>& rhs) noexcept(noexcept(lhs.value / rhs.value))
{
	using type = typename std::common_type<LHS_T, RHS_T>::type;

	return tquantity<tsubtract<LHS_U, RHS_U>, type>{
			static_cast<type>(lhs.value) / static_cast<type>(rhs.value)};
}

/**
 * The @c operator/ for a @ref unit::tquantity object with a value.
 *
 * This is a scaling operation for the @p lhs object.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam LHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p lhs parameter.
 * @tparam RHS_T                  The type of @ref unit::tquantity::type for the
 *                                @p rhs parameter.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side value.
 *
 * @returns                       The object created by dividing @p lhs by
 *                                @p rhs.
 */
template <class U, class LHS_T, class RHS_T>
inline constexpr tquantity<U, LHS_T>
operator/(tquantity<U, LHS_T> lhs,
		  const RHS_T& rhs) noexcept(noexcept(lhs /= rhs))
{
	return lhs /= rhs;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator%                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

namespace detail
{

/**
 * The @c mod for two integral values.
 *
 * @note Since @code std::is_floating_point<T>::value @endcode fails for the
 * boost::multiprecision class use this test.
 *
 * @tparam T                      The type of the value to evaluate.
 *
 * @param rhs                     The right hand side value.
 * @param lhs                     The left hand side value.
 *
 * @returns                       The value created by the remaining part of
 *                                dividing @p lhs by @p rhs.
 */
template <class T>
inline constexpr typename std::enable_if
		<std::numeric_limits<T>::min_exponent == 0, T>::type
mod(const T& lhs, const T& rhs) noexcept(noexcept(lhs % rhs))
{
	return lhs % rhs;
}

/**
 * The @c mod for two floating point values.
 *
 * @note Since @code std::is_floating_point<T>::value @endcode fails for the
 * boost::multiprecision class use this test.
 *
 * @tparam T                      The type of the value to evaluate.
 *
 * @param rhs                     The right hand side value.
 * @param lhs                     The left hand side value.
 *
 * @returns                       The value created by the remaining part of
 *                                dividing @p lhs by @p rhs.
 */
template <class T>
inline constexpr typename std::enable_if
		<std::numeric_limits<T>::min_exponent != 0, T>::type
mod(const T& lhs, const T& rhs) noexcept(noexcept(fmod(lhs, rhs)))
{
	return fmod(lhs, rhs);
}

} // namespace detail

/**
 * The @c operator% for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by the remaining part of
 *                                dividing @p lhs by @p rhs.
 */
template <class U, class T>
inline constexpr tquantity<U, T>
operator%(const tquantity<U, T>& lhs,
		  const tquantity
		  <U, T>& rhs) noexcept(noexcept(detail::mod(lhs.value, rhs.value)))
{
	return tquantity<U, T>{detail::mod(lhs.value, rhs.value)};
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Sqrt                                                              *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The square root of a @ref unit::tquantity object.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The object to operate upon.
 *
 * @returns                       The object created by taking the square root
 *                                of @p quantity.
 */
template <class U, class T>
inline constexpr auto sqrt(const tquantity<U, T>& quantity) noexcept(
		noexcept(sqrt(quantity.value)))
{
	using std::sqrt;
	return tquantity<tsqrt<U>, T>{static_cast<T>(sqrt(quantity.value))};
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Abs                                                              *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The absolute value of a @ref unit::tquantity object.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The object to operate upon.
 *
 * @returns                       The object created by calculating the
 *                                absolute value of@p quantity.
 */
template <class U, class T>
inline constexpr tquantity<U, T>
abs(tquantity<U, T> quantity) noexcept(noexcept(abs(quantity.value)))
{
	using std::abs;
	quantity.value = abs(quantity.value);
	return quantity;
}

} // namespace unit

#endif
