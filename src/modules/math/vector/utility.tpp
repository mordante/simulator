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

#ifndef MODULES_MATH_VECTOR_UTILITY_TPP_INCLUDED
#define MODULES_MATH_VECTOR_UTILITY_TPP_INCLUDED

/**
 * @file
 * Contains the utility operations for the mathematic module's vector.
 *
 * The functions here didn't fit in another header.
 *
 * See @ref math_module for more information.
 */

#include "modules/math/vector/detail/utility.tpp"

#include <cmath>

namespace math
{

/**
 * Calculates the sum of the elements of a @ref math::tvector object.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param vector                  The object whose sum to determine.
 *
 * @returns                       The sum of all elements in @p vector.
 */
template <class T, std::size_t N>
inline constexpr T
sum(const tvector<T, N>& vector) noexcept(noexcept(T {} + T{}))
{
	return detail::tsum<0, T, N>::sum(vector);
}

/**
 * Calculates the power sum of the elements of a @ref math::tvector object.
 *
 * This function calculates the sum of all elements, were every element is
 * raised to the P<i>th</i> power.
 *
 * @warning In order to have a @c constexpr power implementation the function
 * uses a set of multiplications, so using high powers will probably be
 * inefficient.
 *
 * @tparam P                      The power to which raise the elements.
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @pre                           The following assertion holds:
 *                                @code p >= 1 @endcode
 *                                Note that raising to the power 1 is allowed,
 *                                but in that case better use @ref sum instead.
 *
 * @param vector                  The object whose power sum to determine.
 *
 * @returns                       The power sum of all elements in @p vector.
 */
template <std::size_t P, class T, std::size_t N>
inline constexpr auto pow_sum(const tvector<T, N>& vector) noexcept(
		noexcept(T {} + T{}) && noexcept(T{}* T{}))
		-> decltype(detail::tpow<P, T>::pow(T{}))
{
	return detail::tsum<0, T, N>::template pow_sum<P>(vector);
}

/**
 * Calculates the 'length' of the elements of a @ref math::tvector object.
 *
 * This function calculates the 'length' by taking the square root of the sum
 * of all elements raised to the power @c 2.
 *
 * @note If the type @p T is not a floating point type the result is truncated.
 *
 * @tparam T                      The type of @ref math::tvector::value_type.
 * @tparam N                      The value of @ref math::tvector::size().
 *
 * @param vector                  The object whose length to determine.
 *
 * @returns                       The length of all elements in @p vector.
 */
template <class T, std::size_t N>
inline T
length(const tvector<T, N>& vector) noexcept(noexcept(sqrt((T{}* T{}))))
{
	return static_cast<T>(sqrt(pow_sum<2>(vector)));
}

} // namespace math

#endif
