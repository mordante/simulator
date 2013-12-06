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

#ifndef MODULES_UNIT_QUANTITY_COMPARISON_TPP_INCLUDED
#define MODULES_UNIT_QUANTITY_COMPARISON_TPP_INCLUDED

/**
 * @file
 * Contains the comparison operators for @ref unit::tquantity.
 *
 * See @ref unit_module for more information.
 */

#include "modules/unit/quantity.tpp"

namespace unit
{

/**
 * The @c operator== for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is equal to
 *                                the value of @p rhs.
 */
template <class U, class T>
inline constexpr bool
operator==(const tquantity<U, T>& lhs,
		   const tquantity
		   <U, T>& rhs) noexcept(noexcept(lhs.value == rhs.value))
{
	return lhs.value == rhs.value;
}

/**
 * The @c operator!= for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is not equal to
 *                                the value of @p rhs.
 */
template <class U, class T>
inline constexpr bool
operator!=(const tquantity<U, T>& lhs,
		   const tquantity
		   <U, T>& rhs) noexcept(noexcept(lhs.value == rhs.value))
{
	return !(lhs.value == rhs.value);
}

/**
 * The @c operator< for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is less than
 *                                the value of @p rhs.
 */
template <class U, class T>
inline constexpr bool
operator<(const tquantity<U, T>& lhs, const tquantity<U, T>& rhs) noexcept(
		noexcept(lhs.value < rhs.value) && noexcept(rhs.value < lhs.value))
{
	return lhs.value < rhs.value;
}

/**
 * The @c operator<= for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is less than or
 *                                equal to the value of @p rhs.
 */
template <class U, class T>
inline constexpr bool
operator<=(const tquantity<U, T>& lhs, const tquantity<U, T>& rhs) noexcept(
		noexcept(lhs.value < rhs.value) && noexcept(rhs.value < lhs.value))

{
	return !(rhs.value < lhs.value);
}

/**
 * The @c operator> for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is greater than
 *                                the value of @p rhs.
 */
template <class U, class T>
inline constexpr bool
operator>(const tquantity<U, T>& lhs, const tquantity<U, T>& rhs) noexcept(
		noexcept(lhs.value < rhs.value) && noexcept(rhs.value < lhs.value))

{
	return rhs.value < lhs.value;
}

/**
 * The @c operator>= for two @ref unit::tquantity objects.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param rhs                     The right hand side object.
 * @param lhs                     The left hand side object.
 *
 * @returns                       Whether the value of @p lhs is greater than
 *                                or equal to the value of @p rhs.
 */
template <class U, class T>
inline constexpr bool
operator>=(const tquantity<U, T>& lhs, const tquantity<U, T>& rhs) noexcept(
		noexcept(lhs.value < rhs.value) && noexcept(rhs.value < lhs.value))

{
	return !(lhs.value < rhs.value);
}

} // namespace unit

#endif
