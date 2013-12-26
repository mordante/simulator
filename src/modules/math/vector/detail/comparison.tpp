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

#ifndef MODULES_MATH_VECTOR_DETAIL_COMPARISON_TPP_INCLUDED
#define MODULES_MATH_VECTOR_DETAIL_COMPARISON_TPP_INCLUDED

/**
 * @file
 * Contains the comparison operations for the mathematic module's vector.
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
struct tcomparison
{
	static constexpr bool
	equal(const tvector<T, N>& lhs,
		  const tvector<T, N>& rhs) noexcept(noexcept(T{} == T{}))
	{
		return lhs.data[I] == rhs.data[I] && tcomparison
			   <I + 1, T, N>::equal(lhs, rhs);
	}

	static constexpr bool
	less(const tvector<T, N>& lhs,
		 const tvector<T, N>& rhs) noexcept(noexcept(T{} < T{}))
	{
		return lhs.data[I] < rhs.data[I]
			   || (!(rhs.data[I] < lhs.data[I]) && tcomparison
				   <I + 1, T, N>::less(lhs, rhs));
	}
};

template <class T, std::size_t N>
struct tcomparison<N, T, N>
{
	static constexpr bool
	equal(const tvector<T, N>& /*lhs*/, const tvector<T, N>& /*rhs*/) noexcept
	{
		return true;
	}

	static constexpr bool
	less(const tvector<T, N>& /*lhs*/, const tvector<T, N>& /*rhs*/) noexcept
	{
		return false;
	}
};

} // detail

} // namespace math

#endif
