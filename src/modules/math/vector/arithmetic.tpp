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

#ifndef MODULES_MATH_VECTOR_ARITHMETIC_TPP_INCLUDED
#define MODULES_MATH_VECTOR_ARITHMETIC_TPP_INCLUDED

/**
 * @file
 * Contains the arithmetic operations for the mathematics module's vector.
 *
 * See @ref math_module for more information.
 */

#include "modules/math/vector/detail/arithmetic.tpp"

#include <type_traits>

namespace math
{

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator+                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator+= for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after adding @p rhs to it.
 */
template <class T, std::size_t N>
inline constexpr auto&
operator+=(tvector<T, N>& lhs,
		   const tvector<T, N>& rhs) noexcept(noexcept(T {} + T{}))
{
	return detail::tarithmetic<0, T, N>::add(lhs, rhs);
}

/**
 * The @c operator+ for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by adding @p lhs and
 *                                @p rhs.
 */
template <class T, std::size_t N>
inline constexpr tvector<T, N>
operator+(tvector<T, N> lhs,
		  const tvector<T, N>& rhs) noexcept(noexcept(lhs += rhs))
{
	return lhs += rhs;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator-                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator-= for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after subtracting @p rhs from it.
 */
template <class T, std::size_t N>
inline constexpr auto&
operator-=(tvector<T, N>& lhs,
		   const tvector<T, N>& rhs) noexcept(noexcept(T {} - T{}))
{
	return detail::tarithmetic<0, T, N>::sub(lhs, rhs);
}

/**
 * The @c operator- for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by subtracting @p rhs from
 *                                @p lhs.
 */
template <class T, std::size_t N>
inline constexpr tvector<T, N>
operator-(tvector<T, N> lhs,
		  const tvector<T, N>& rhs) noexcept(noexcept(lhs -= rhs))
{
	return lhs -= rhs;
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator*                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator*= for a @ref math::tvector object and a scalar value.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 * @tparam S                      A scalar type to multiply with.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after multiplying all of its elements
 *                                by @p rhs.
 */
template <class T, std::size_t N, class S>
inline constexpr tvector<T, N>&
operator*=(tvector<T, N>& lhs, S rhs) noexcept(noexcept(T{}* S{}))
{
	return detail::tarithmetic<0, T, N>::mul(lhs, rhs);
}

/**
 * The @c operator*= for two @ref math::tvector objects.
 *
 * @note The module is intended to be used in combination with the unit module,
 * since most multiplications of units result in a new type not every type can
 * be used with @c operator*=. When not possible used @c operator* instead.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @pre                           The following type assertion holds:
 *                                @code T = T * T @endcode
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after multiplying it by @p rhs.
 */
template <class T, std::size_t N>
inline constexpr tvector<T, N>&
operator*=(tvector<T, N>& lhs,
		   const tvector<T, N>& rhs) noexcept(noexcept(T{}* T{}))
{
	static_assert(std::is_same<T, decltype(T{} * T{})>::value,
				  "Operation*= is only available if the type does not change "
				  "by multiplication.");

	return detail::tarithmetic<0, T, N>::mul(lhs, rhs);
}

/**
 * The @c operator* for a @ref math::tvector object and a scalar value.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 * @tparam S                      A scalar type to multiply with.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by multiplying all
 *                                elements of @p lhs with @p rhs.
 */
template <class T, std::size_t N, class S>
inline constexpr tvector<T, N>
operator*(tvector<T, N> lhs, S rhs) noexcept(noexcept(T{}* S{}))
{
	return lhs *= rhs;
}

/**
 * The @c operator* for a @ref math::tvector object and a scalar value.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 * @tparam S                      A scalar type to multiply with.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by multiplying all
 *                                elements of @p rhs with @p lhs.
 */
template <class T, std::size_t N, class S>
inline constexpr tvector<T, N>
operator*(S lhs, tvector<T, N> rhs) noexcept(noexcept(S{}* T{}))
{
	return rhs *= lhs;
}

/**
 * The @c operator* for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by multiplying @p lhs and
 *                                @p rhs.
 */
template <class T, std::size_t N>
inline constexpr tvector<decltype(T{}* T{}), N>
operator*(const tvector<T, N>& lhs,
		  const tvector<T, N>& rhs) noexcept(noexcept(T{}* T{}))
{
	tvector<decltype(T{} * T{}), N> result{};
	return detail::tarithmetic<0, T, N>::mul(result, lhs, rhs);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/
/***** Operator/                                                         *****/
/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * The @c operator/= for a @ref math::tvector object and a scalar value.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 * @tparam S                      A scalar type to divide by.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after dividing all of its elements
 *                                by @p rhs.
 */
template <class T, std::size_t N, class S>
inline constexpr tvector<T, N>&
operator/=(tvector<T, N>& lhs, S rhs) noexcept(noexcept(T{} / S{}))
{
	return detail::tarithmetic<0, T, N>::div(lhs, rhs);
}

/**
 * The @c operator/= for two @ref math::tvector objects.
 *
 * @note The module is intended to be used in combination with the unit module,
 * since most divisions of units result in a new type not every type can be
 * used with @c operator/=. When not possible used @c operator/ instead.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @pre                           The following type assertion holds:
 *                                @code T  / T = T @endcode
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       @p lhs after dividing it by @p rhs.
 */
template <class T, std::size_t N>
inline constexpr tvector<T, N>&
operator/=(tvector<T, N>& lhs,
		   const tvector<T, N>& rhs) noexcept(noexcept(T{} / T{}))
{
	static_assert(std::is_same<T, decltype(T{} / T{})>::value,
				  "Operation/= is only available if the type does not change "
				  "by divtiplication.");

	return detail::tarithmetic<0, T, N>::div(lhs, rhs);
}

/**
 * The @c operator/ for a @ref math::tvector object and a scalar value.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 * @tparam S                      A scalar type to divide by.
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by dividing every element
 *                                of @p lhs by @p rhs.
 */
template <class T, std::size_t N, class S>
inline constexpr tvector<T, N>
operator/(tvector<T, N> lhs, S rhs) noexcept(noexcept(T{} / S{}))
{
	return lhs /= rhs;
}

/**
 * The @c operator/ for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       The object created by dividing @p lhs by
 *                                @p rhs.
 */
template <class T, std::size_t N>
inline constexpr tvector<decltype(T{} / T{}), N>
operator/(const tvector<T, N>& lhs,
		  const tvector<T, N>& rhs) noexcept(noexcept(T{} / T{}))
{
	tvector<decltype(T{} / T{}), N> result{};
	return detail::tarithmetic<0, T, N>::div(result, lhs, rhs);
}

} // namespace math

#endif
