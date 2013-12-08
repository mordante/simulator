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

#ifndef LIB_UTILITY_CONCATENATE_TPP_INCLUDED
#define LIB_UTILITY_CONCATENATE_TPP_INCLUDED

/**
 * @file
 * Contains the concatenate utility functions.
 *
 * These helper functions use variadic templates to concatenate a set of
 * variables to a @c std::ostream or a @c std::string.
 */

#include <sstream>
#include <utility>

namespace lib
{

/**
 * Streams a variable.
 *
 * This is a helper function for streaming. It is the terminator for the other
 * @ref stream function.
 *
 * It uses the operator<<().
 *
 * @param ostream                 The output stream to send @p rhs to.
 * @param rhs                     The variable to stream.
 *
 * @returns                       The parameter @p ostream.
 */
template <class T>
inline std::ostream& stream(std::ostream& ostream, T&& rhs)
{
	ostream << rhs;
	return ostream;
}

/**
 * Streams a list of variables.
 *
 * It uses the operator<<() for all variables.
 *
 * @param ostream                 The output stream to send @p rhs to.
 * @param rhs                     A variable to stream.
 * @param pack                    The other parameters to stream after
 *                                streaming @p rhs.
 *
 * @returns                       The parameter @p ostream.
 */
template <class T, class... Pack>
inline std::ostream& stream(std::ostream& ostream, T&& rhs, Pack&&... pack)
{
	stream(ostream, std::forward<T>(rhs));
	return stream(ostream, std::forward<Pack>(pack)...);
}

/**
 * Concatenates a list of variables to a string.
 *
 * It uses the operator<<() for all variables.
 *
 * @pre                           The following assertion holds:
 *                                @code (sizeof...(pack) > 0 @endcode
 *
 * @param pack                    The parameters to convert to a string.
 *
 * @returns                       The concatenated string.
 */

template <class... Pack>
inline std::string concatenate(Pack&&... pack)
{
	static_assert(sizeof...(pack) > 0,
				  "Concatenate needs at least one argument.");

	std::stringstream sstr;
	stream(sstr, std::forward<Pack>(pack)...);
	return sstr.str();
}

} // namespace lib

#endif
