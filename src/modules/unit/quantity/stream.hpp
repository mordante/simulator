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

#ifndef MODULES_UNIT_QUANTITY_STREAM_HPP_INCLUDED
#define MODULES_UNIT_QUANTITY_STREAM_HPP_INCLUDED

/**
 * @file
 * Contains the stream operators of the @ref unit::tquantity class.
 *
 * See @ref unit_module for more information.
 */

#include "modules/unit/quantity.tpp"

#include <ostream>

namespace unit
{

namespace detail
{

/**
 * Converts an amount of @p count units of @p unit to a string.
 *
 * @param unit                    The textual representation of the unit.
 * @param count                   The power of the unit, can be positive,
 *                                negative or zero.
 *
 * @returns                       A string representing the unit.
 */
std::string stream_unit(const std::string& unit, const int count);

/**
 * Converts the units of a @ref unit::tunit to a string.
 *
 * @tparam U                      The @ref unit::tunit to convert.
 *
 * @returns                       A string representing the @ref unit::tunit.
 */
template <class U>
inline std::string stream_unit()
{
	std::string result;
	constexpr U u{};

	result += stream_unit(" m", u.m);
	result += stream_unit(" kg", u.kg);
	result += stream_unit(" s", u.s);
	result += stream_unit(" K", u.k);
	result += stream_unit(" rad", u.rad);

	return result;
}

} // namespace detail

/**
 * The operator<< for a @ref unit::tquantity.
 *
 * @note Some units get an awkward value when used by this function, for
 * example a »J« becomes »m^2 kg s^-2«. These units need a specialisation to
 * get the wanted output. These overloads use the same input and output
 * variables, only specialise the @p U template parameter.
 *
 * @tparam U                      The type of @ref unit::tquantity::unit.
 * @tparam T                      The type of @ref unit::tquantity::type
 *
 * @param ostream                 The output stream to write to.
 * @param quantity                The object to write to the stream.
 *
 * @returns                       @p ostream
 */
template <class U, class T>
inline std::ostream& operator<<(std::ostream& ostream,
								const tquantity<U, T>& quantity)
{
	return ostream << quantity.value << detail::stream_unit<U>();
}

/**
 * Specialisation for: @code U == NONE @endcode
 *
 * @note The specialisation is only added as optimisation. The general template
 * would properly handle this case.
 */
template <class T>
inline constexpr std::ostream& operator<<(
		std::ostream& ostream,
		const tquantity<NONE, T>&
				quantity) noexcept(noexcept(ostream << quantity.value))
{
	return ostream << quantity.value;
}

/** Specialisation for: @code U == N @endcode */
template <class T>
inline constexpr std::ostream& operator<<(
		std::ostream& ostream,
		const tquantity<N, T>& quantity) noexcept(noexcept(ostream
														   << quantity.value))
{
	return ostream << quantity.value << " N";
}

/** Specialisation for: @code U == J @endcode */
template <class T>
inline constexpr std::ostream& operator<<(
		std::ostream& ostream,
		const tquantity<J, T>& quantity) noexcept(noexcept(ostream
														   << quantity.value))
{
	return ostream << quantity.value << " J";
}

} // namespace unit

#endif
