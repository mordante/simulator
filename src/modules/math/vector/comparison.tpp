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

#ifndef MODULES_MATH_VECTOR_COMPARISON_TPP_INCLUDED
#define MODULES_MATH_VECTOR_COMPARISON_TPP_INCLUDED

/**
 * @file
 * Contains the comparison operations for the mathematics module's vector.
 *
 * See @ref math_module for more information.
 */

#include "modules/math/vector/detail/comparison.tpp"

namespace math
{

/**
 * The @c operator== for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is equal to
 *                                the value of @p rhs.
 */
template <class T, std::size_t N>
inline constexpr bool
operator==(const tvector<T, N>& lhs,
		   const tvector<T, N>& rhs) noexcept(noexcept(T{} == T{}))
{
	return detail::tcomparison<0, T, N>::equal(lhs, rhs);
}

/**
 * The @c operator!= for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is not equal to
 *                                the value of @p rhs.
 */
template <class T, std::size_t N>
inline constexpr bool
operator!=(const tvector<T, N>& lhs,
		   const tvector<T, N>& rhs) noexcept(noexcept(T{} == T{}))
{
	return !(lhs == rhs);
}

/**
 * The @c operator< for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is less than
 *                                the value of @p rhs.
 */
template <class T, std::size_t N>
inline constexpr bool
operator<(const tvector<T, N>& lhs,
		  const tvector<T, N>& rhs) noexcept(noexcept(T{} < T{}))
{
	return detail::tcomparison<0, T, N>::less(lhs, rhs);
}

/**
 * The @c operator<= for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is less than or
 *                                equal to the value of @p rhs.
 */
template <class T, std::size_t N>
inline constexpr bool
operator<=(const tvector<T, N>& lhs,
		   const tvector<T, N>& rhs) noexcept(noexcept(T{} < T{}))
{
	return !(rhs < lhs);
}

/**
 * The @c operator> for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is greater than
 *                                the value of @p rhs.
 */
template <class T, std::size_t N>
inline constexpr bool
operator>(const tvector<T, N>& lhs,
		  const tvector<T, N>& rhs) noexcept(noexcept(T{} < T{}))
{
	return rhs < lhs;
}

/**
 * The @c operator>= for two @ref math::tvector objects.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is greater than
 *                                or equal to the value of @p rhs.
 */
template <class T, std::size_t N>
inline constexpr bool
operator>=(const tvector<T, N>& lhs,
		   const tvector<T, N>& rhs) noexcept(noexcept(T{} < T{}))
{
	return !(lhs < rhs);
}

} // namespace math

#endif
