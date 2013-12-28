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

#ifndef MODULES_UNIT_QUANTITY_TPP_INCLUDED
#define MODULES_UNIT_QUANTITY_TPP_INCLUDED

/**
 * @file
 * Contains the @ref unit::tquantity class.
 *
 * Defines the member functions and some basic operations. Most of the other
 * operations are in the headers in the <i>modules/unit/quantity</i> directory.
 *
 * See @ref unit_module for more information.
 */

#include "modules/unit/unit.tpp"

#include <algorithm>
#include <type_traits>

namespace unit
{

template <class U, class T>
struct tquantity
{
	/***** ***** ***** ***** Types. ***** ***** ***** *****/

	/** The type of the value of the quantity */
	using type = T;

	/** The type of the unit of the quantity. */
	using unit = U;


	/***** Constructors, assign operators, destructor. *****/

	tquantity() = default;

	/**
	 * Constructor.
	 *
	 * @param value__             Forwarded to @ref value.
	 */
	explicit constexpr tquantity(T value__) noexcept : value{std::move(value__)}
	{
	}

	~tquantity() = default;

	tquantity& operator=(tquantity&&) = default;
	tquantity(tquantity&&) = default;

	tquantity& operator=(const tquantity&) = default;
	tquantity(const tquantity&) = default;


	/***** ***** ***** ***** Conversion operators. ***** ***** ***** *****/

	template <class N>
	constexpr operator tquantity<U, N>() const
	{
		static_assert(std::is_same
					  <typename std::common_type<N, T>::type, N>::value,
					  "Narrowing conversion is prohibited.");

		return tquantity<U, N>{static_cast<N>(value)};
	}


	/***** ***** ***** ***** Members. ***** ***** ***** *****/

	/** The value of the quantity. */
	T value;
};

/**
 * Sets the units of a quantity.
 *
 * @note The function is unused at the moment and maybe will be removed.
 *
 * @tparam N                      The type of @ref unit::tquantity::unit to
 *                                return.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The quantity whose unit to set.
 *
 * @returns                       The quantity with the new unit type.
 */
template <class N, class T>
inline constexpr auto set(const tquantity<NONE, T>& quantity) noexcept
{
	return tquantity<N, T>{quantity.value};
}

/**
 * Clears the units of a quantity.
 *
 * @note The function is unused at the moment and maybe will be removed.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param quantity                The quantity whose unit to clear.
 *
 * @returns                       The quantity with the @ref unit::NONE unit
 *                                type.
 */
template <class U, class T>
inline constexpr auto clear(tquantity<U, T>& quantity) noexcept
{
	return tquantity<NONE, T>{quantity.value};
}

} // namespace unit

#endif
