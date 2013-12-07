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

#ifndef LIB_EXCEPTION_EXCEPTION_HPP_INCLUDED
#define LIB_EXCEPTION_EXCEPTION_HPP_INCLUDED

/**
 * @file
 * Defines the class for all exceptions.
 *
 * All normal exceptions thrown in the programs should use this exception. The
 * @ref lib::texception::ttype is used to differentiate between the various
 * exceptions.
 */

#include "lib/utility/concatenate.tpp"

namespace lib
{

struct texception final
{
	/***** ***** Types. ***** *****/

	/**
	 * The type of exception thrown.
	 *
	 * All exceptions have a sub-type. Their basic type is determined by the
	 * object id but the sub-type gives more information regarding the exact
	 * cause of the issue. This sub-type is one of the members of this
	 * enumerate.
	 */
	enum class ttype {
		/**
		 * The value given is invalid.
		 *
		 * This is a generic error code when a value given is not valid. It
		 * can be the wrong type, but also a range error.
		 */
		invalid_value

		/**
		 * The operation does not exist yet.
		 *
		 * This is thrown when a non-existing operation is attempted. This
		 * exception is used when the operation will be implemented in the
		 * future.
		 */
		,
		not_implemented_yet

		/**
		 * An internal failure occurred.
		 *
		 * This means an internal assertion has failed. This exception should
		 * never be thrown.
		 */
		,
		internal_failure

		/**
		 * A non-supported version of a file was loaded.
		 *
		 * All classes that load a XML-property tree have a static member
		 * called <i>load</i>. This function is able to convert certain
		 * versions, if this loader fails it throws this exception.
		 */
		,
		load_invalid_version
	};


	/***** ***** Constructor, destructor, assignment. ***** *****/

	texception() = delete;

	explicit texception(const ttype type__) = delete;

	template <class... M>
	explicit texception(const ttype type__, M&&... messages)
		: type{type__}, message{lib::concatenate(std::forward<M>(messages)...)}
	{
	}

	~texception() = default;

	texception& operator=(const texception&) = default;
	texception(const texception&) = default;

	texception& operator=(texception&&) = default;
	texception(texception&&) = default;


	/***** ***** Members. ***** *****/

	/** The type of the exception. */
	ttype type;

	/** The message containing information regarding the exception. */
	std::string message;
};

} // namespace lib

#include "lib/utility/enumerate.tpp"

namespace lib
{

ENUM_DECLARE_STREAM_OPERATORS(::lib::texception::ttype)

} // namespace lib

#endif
