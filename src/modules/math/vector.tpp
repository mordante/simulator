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

#ifndef MODULES_MATH_VECTOR_TPP_INCLUDED
#define MODULES_MATH_VECTOR_TPP_INCLUDED

/**
 * @file
 * Contains the vector of the mathematics module.
 *
 * See @ref math_module for more information.
 */

#include <cstddef>

namespace math
{

/**
 * The vector definition.
 *
 * If type @p T allows it this class is an aggregate class, just like
 * @c std::array. The class has not implemented all operations for
 * @c std::array, these will be added when the need arises.
 *
 * @tparam T                      The type of the elements in the container.
 * @tparam N                      The number of elements.
 *
 * @pre                           The following assertion holds:
 *                                @code N >= 1 @endcode
 */
template <class T, std::size_t N>
struct tvector
{
	/***** ***** ***** ***** Types. ***** ***** ***** *****/

	using value_type = T;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using size_type = std::size_t;

	static_assert(N >= 1, "Zero sized vectors are not allowed.");

	/***** Constructors, assign operators, destructor. *****/

	tvector() = default;
	~tvector() = default;

	tvector& operator=(tvector&&) = default;
	tvector(tvector&&) = default;

	tvector& operator=(const tvector&) = default;
	tvector(const tvector&) = default;


	/***** ***** ***** ***** Operations. ***** ***** ***** *****/

	/**
	 * Returns the number of elements in the @ref tvector.
	 *
	 * @returns                   The number of elements in the vector.
	 */
	constexpr size_type size() const noexcept
	{
		return N;
	}

	/**
	 * Returns the n<i>th</i> element in the @ref tvector.
	 *
	 * @pre                       The following assertion holds:
	 *                            @code index < N @endcode
	 *
	 * @param index               The index of the element to retrieve.
	 *
	 * @returns                   The element at index @p index in the vector.
	 */
	constexpr reference operator[](size_type index) noexcept
	{
		return data[index];
	}

	/**
	 * Returns the n<i>th</i> element in the @ref tvector.
	 *
	 * @pre                       The following assertion holds:
	 *                            @code index < N @endcode
	 *
	 * @param index               The index of the element to retrieve.
	 *
	 * @returns                   The element at index @p index in the vector.
	 */
	constexpr const_reference operator[](size_type index) const noexcept
	{
		return data[index];
	}

	/**
	 * Returns the zeroth element in the @ref tvector.
	 *
	 * Since the vector is expected to be used to hold coordinates some helper
	 * functions using the vector as a coordinate are added.
	 *
	 * @returns                   The element at index @c 0 in the vector.
	 */
	constexpr reference x() noexcept
	{
		return data[0];
	}

	/**
	 * Returns the zeroth element in the @ref tvector.
	 *
	 * Since the vector is expected to be used to hold coordinates some helper
	 * functions using the vector as a coordinate are added.
	 *
	 * @returns                   The element at index @c 0 in the vector.
	 */
	constexpr const_reference x() const noexcept
	{
		return data[0];
	}

	/**
	 * Returns the second element in the @ref tvector.
	 *
	 * Since the vector is expected to be used to hold coordinates some helper
	 * functions using the vector as a coordinate are added.
	 *
	 * @pre                       The following assertion holds:
	 *                            @code N > 1 @endcode
	 *
	 * @returns                   The element at index @c 1 in the vector.
	 */
	constexpr reference y() noexcept
	{
		/* Note std::enable_if doesn't work as wanted. */
		static_assert(N > 1, "Try to access the vector out of bounds.");
		return data[1];
	}

	/**
	 * Returns the second element in the @ref tvector.
	 *
	 * Since the vector is expected to be used to hold coordinates some helper
	 * functions using the vector as a coordinate are added.
	 *
	 * @pre                       The following assertion holds:
	 *                            @code N > 1 @endcode
	 *
	 * @returns                   The element at index @c 1 in the vector.
	 */
	constexpr const_reference y() const noexcept
	{
		/* Note std::enable_if doesn't work as wanted. */
		static_assert(N > 1, "Try to access the vector out of bounds.");
		return data[1];
	}

	/**
	 * Returns the third element in the @ref tvector.
	 *
	 * Since the vector is expected to be used to hold coordinates some helper
	 * functions using the vector as a coordinate are added.
	 *
	 * @pre                       The following assertion holds:
	 *                            @code N > 2 @endcode
	 *
	 * @returns                   The element at index @c 2 in the vector.
	 */
	constexpr reference z() noexcept
	{
		/* Note std::enable_if doesn't work as wanted. */
		static_assert(N > 2, "Try to access the vector out of bounds.");
		return data[2];
	}

	/**
	 * Returns the third element in the @ref tvector.
	 *
	 * Since the vector is expected to be used to hold coordinates some helper
	 * functions using the vector as a coordinate are added.
	 *
	 * @pre                       The following assertion holds:
	 *                            @code N > 2 @endcode
	 *
	 * @returns                   The element at index @c 2 in the vector.
	 */
	constexpr const_reference z() const noexcept
	{
		/* Note std::enable_if doesn't work as wanted. */
		static_assert(N > 2, "Try to access the vector out of bounds.");
		return data[2];
	}

	/***** ***** ***** ***** Members. ***** ***** ***** *****/

	/** The array holding the elements of the @ref tvector. */
	T data[N];
};

} // namespace math

#endif
