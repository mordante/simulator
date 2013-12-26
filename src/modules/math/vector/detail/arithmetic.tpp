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

#ifndef MODULES_MATH_VECTOR_DETAIL_ARITHMETIC_TPP_INCLUDED
#define MODULES_MATH_VECTOR_DETAIL_ARITHMETIC_TPP_INCLUDED

/**
 * @file
 * Contains the arithmetic operations for the mathematic module's vector.
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

#include "modules/math/vector.tpp"

namespace math
{

namespace detail
{

template <std::size_t I, class T, std::size_t N>
struct tarithmetic
{
	static constexpr tvector<T, N>&
	add(tvector<T, N>& lhs,
		const tvector<T, N>& rhs) noexcept(noexcept(T {} + T{}))
	{
		lhs.data[I] += rhs.data[I];
		return tarithmetic<I + 1, T, N>::add(lhs, rhs);
	}

	static constexpr tvector<T, N>&
	sub(tvector<T, N>& lhs,
		const tvector<T, N>& rhs) noexcept(noexcept(T {} - T{}))
	{
		lhs.data[I] -= rhs.data[I];
		return tarithmetic<I + 1, T, N>::sub(lhs, rhs);
	}

	template <class S>
	static constexpr tvector<T, N>&
	mul(tvector<T, N>& lhs, S rhs) noexcept(noexcept(T{}* S{}))

	{
		lhs.data[I] *= rhs;
		return tarithmetic<I + 1, T, N>::mul(lhs, rhs);
	}

	static constexpr tvector<T, N>&
	mul(tvector<T, N>& lhs,
		const tvector<T, N>& rhs) noexcept(noexcept(T{}* T{}))
	{
		lhs.data[I] *= rhs.data[I];
		return tarithmetic<I + 1, T, N>::mul(lhs, rhs);
	}

	static constexpr tvector<decltype(T{}* T{}), N>&
	mul(tvector<decltype(T{}* T{}), N>& result,
		const tvector<T, N>& lhs,
		const tvector<T, N>& rhs) noexcept(noexcept(T{}* T{}))
	{
		result.data[I] = lhs.data[I] * rhs.data[I];
		return tarithmetic<I + 1, T, N>::mul(result, lhs, rhs);
	}

	template <class S>
	static constexpr tvector<T, N>&
	div(tvector<T, N>& lhs, S rhs) noexcept(noexcept(T{} / S{}))
	{
		lhs.data[I] /= rhs;
		return tarithmetic<I + 1, T, N>::div(lhs, rhs);
	}

	static constexpr tvector<T, N>&
	div(tvector<T, N>& lhs,
		const tvector<T, N>& rhs) noexcept(noexcept(T{} / T{}))
	{
		lhs.data[I] /= rhs.data[I];
		return tarithmetic<I + 1, T, N>::div(lhs, rhs);
	}

	static constexpr tvector<decltype(T{} / T{}), N>&
	div(tvector<decltype(T{} / T{}), N>& result,
		const tvector<T, N>& lhs,
		const tvector<T, N>& rhs) noexcept(noexcept(T{} / T{}))
	{
		result.data[I] = lhs.data[I] / rhs.data[I];
		return tarithmetic<I + 1, T, N>::div(result, lhs, rhs);
	}
};

template <class T, std::size_t N>
struct tarithmetic<N, T, N>
{
	static constexpr tvector<T, N>&
	add(tvector<T, N>& lhs, const tvector<T, N>& /*rhs*/) noexcept
	{
		return lhs;
	}

	static constexpr tvector<T, N>&
	sub(tvector<T, N>& lhs, const tvector<T, N>& /*rhs*/) noexcept
	{
		return lhs;
	}

	template <class S>
	static constexpr tvector<T, N>& mul(tvector<T, N>& lhs, S /*rhs*/) noexcept
	{
		return lhs;
	}

	static constexpr tvector<T, N>&
	mul(tvector<T, N>& lhs, const tvector<T, N>& /*rhs*/) noexcept
	{
		return lhs;
	}

	static constexpr tvector<decltype(T{}* T{}), N>&
	mul(tvector<decltype(T{}* T{}), N>& result,
		const tvector<T, N>& /*lhs*/,
		const tvector<T, N>& /*rhs*/) noexcept
	{
		return result;
	}

	template <class S>
	static constexpr tvector<T, N>& div(tvector<T, N>& lhs, S /*rhs*/) noexcept
	{
		return lhs;
	}

	static constexpr tvector<T, N>&
	div(tvector<T, N>& lhs, const tvector<T, N>& /*rhs*/) noexcept
	{
		return lhs;
	}

	static constexpr tvector<decltype(T{} / T{}), N>&
	div(tvector<decltype(T{} / T{}), N>& result,
		const tvector<T, N>& /*lhs*/,
		const tvector<T, N>& /*rhs*/) noexcept
	{
		return result;
	}
};

} // detail

} // namespace math

#endif
