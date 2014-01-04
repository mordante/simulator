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

#ifndef MODULES_MATH_VECTOR_UTILITY_DETAIL_TPP_INCLUDED
#define MODULES_MATH_VECTOR_UTILITY_DETAIL_TPP_INCLUDED

/**
 * @file
 * Contains the utility operations for the mathematic module's vector.
 *
 * The functions here didn't fit in another header.
 *
 * This file contains the implementation details. The functions are not
 * documented, but they should become clear when looking at the caller.
 *
 * The functions perform a compile-time loop over all elements in the
 * @ref math::tvector and perform the wanted operation. The parameter @p I is
 * the looping 'variable' and runs over the range [@c 0, @p N]. There is a
 * specialised class for @p I == @p N. This specialisation it the loop's
 * terminator operation, it is executed but shouldn't modify the result.
 *
 * See @ref math_module for more information.
 */

#include "modules/math/vector/arithmetic.tpp"

namespace math
{

namespace detail
{

template <std::size_t P, class T>
struct tpow
{
	static constexpr auto pow(T value) noexcept(noexcept(T{}* T{}))
			-> decltype(T{}* tpow<P - 1, T>::pow(T{}))
	{
		static_assert(P != 0, "Raising to the zeroth power is not supported.");
		return value * tpow<P - 1, T>::pow(value);
	}
};

template <class T>
struct tpow<1, T>
{
	static constexpr T pow(T value) noexcept
	{
		return value;
	}
};

template <std::size_t I, class T, std::size_t N>
struct tsum
{
	static constexpr T
	sum(const tvector<T, N>& vector) noexcept(noexcept(T {} + T{}))
	{
		return vector.data[I] + tsum<I + 1, T, N>::sum(vector);
	}


	template <std::size_t P>
	static constexpr auto pow_sum(const tvector<T, N>& vector) noexcept(
			noexcept(T {} + T{}) && noexcept(T{}* T{}))
			-> decltype(detail::tpow<P, T>::pow(T{}))
	{
		return tpow<P, T>::pow(vector.data[I])
			   + tsum<I + 1, T, N>::template pow_sum<P>(vector);
	}
};

template <class T, std::size_t N>
struct tsum<N, T, N>
{
	static constexpr T sum(const tvector<T, N>& /*vector*/) noexcept
	{
		return T{0};
	}

	template <std::size_t P>
	static constexpr auto pow_sum(const tvector<T, N>& /*vector*/) noexcept
			-> decltype(detail::tpow<P, T>::pow(T{}))
	{
		return decltype(detail::tpow<P, T>::pow(T{})) {0};
	}
};

} // detail

} // namespace math

#endif
