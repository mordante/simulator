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

#ifndef LIB_EXCEPTION_VALIDATE_TPP_INCLUDED
#define LIB_EXCEPTION_VALIDATE_TPP_INCLUDED

/**
 * @file
 * Defines several validation and failure macros.
 *
 * The macros all throw a @ref lib::texception upon failure. The header also
 * defines some wrappers for static assertions. This allows to validate macro
 * parameters.
 */

#include "lib/exception/exception.hpp"

/**
 * Validates whether the @p condition is true.
 *
 * This function is intended to replace @c std::assert(condition).
 *
 * @pre                           @p condition can be evaluated as a boolean
 *                                expression.
 *
 * @param condition               The condition to validate. It the condition
 *                                evaluates to @c true, nothing happens, if it
 *                                evaluates to @c false an @ref
 *lib::texception
 *                                is thrown.
 */
#define VALIDATE(condition)                                                    \
	do {                                                                       \
		if(!(condition)) {                                                     \
			throw ::lib::texception(                                           \
					::lib::texception::ttype::internal_failure,                \
					"Conditional failure in function '",                       \
					__PRETTY_FUNCTION__,                                       \
					"' file '",                                                \
					__FILE__,                                                  \
					"' line '",                                                \
					__LINE__,                                                  \
					"' condition '",                                           \
					#condition,                                                \
					"'");                                                      \
		}                                                                      \
	} while(0)


/**
 * Throws an @ref lib::texception.
 *
 * This function is intended to replace @c std::assert(false).
 */
#define FAIL                                                                   \
	do {                                                                       \
		throw ::lib::texception(::lib::texception::ttype::internal_failure,    \
								"Unconditional failure in function '",         \
								__PRETTY_FUNCTION__,                           \
								"' file '",                                    \
								__FILE__,                                      \
								"' line '",                                    \
								__LINE__,                                      \
								"'");                                          \
	} while(0)

/**
 * Throws an @ref lib::texception.
 *
 * This function is intended to replace @c std::assert(false).
 *
 * @param message                 A message to add to the exception thrown,
 *                                this can be used to aid debugging.
 */
#define FAIL_MSG(message)                                                      \
	do {                                                                       \
		throw ::lib::texception(::lib::texception::ttype::internal_failure,    \
								"Unconditional failure in function '",         \
								__PRETTY_FUNCTION__,                           \
								"' file '",                                    \
								__FILE__,                                      \
								"' line '",                                    \
								__LINE__,                                      \
								"' message '",                                 \
								message,                                       \
								"'");                                          \
	} while(0)

/**
 * Validates the range of an @c enum in @c operator<<().
 *
 * The typical use case is:
 * @code
 * switch(enumerate) {
 *     case member_1 : ...; return;
 *     case member_2 : ...; return;
 * }
 * ENUM_FAIL_OUTPUT(enumerate);
 * @endcode
 * Since the enumerate cannot be converted to a string its numeric value is
 * used as error instead. When used in a normal function and with a valid @c
 * operator<< @ref ENUM_FAIL_RANGE can be used instead.
 *
 * @note Normally the compiler can warn if a member of an enum is not handled,
 * at least when the @c switch doesn't have a default handler. So the error
 * should normally never trigger.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::is_enum<decltype(enumerate)>::value ==
 *                                true
 *                                @endcode
 *
 * @param enumerate               The enumerate which failed.
 */
#define ENUM_FAIL_OUTPUT(enumerate)                                            \
	do {                                                                       \
		static_assert(std::is_enum<decltype(enumerate)>::value,                \
					  "The enumerate parameter must be an enum type.");        \
		throw ::lib::texception(                                               \
				::lib::texception::ttype::invalid_value,                       \
				"Enumerate out of range during output, value '",               \
				static_cast<unsigned>(enumerate),                              \
				"' in function '",                                             \
				__PRETTY_FUNCTION__,                                           \
				"' file '",                                                    \
				__FILE__,                                                      \
				"' line '",                                                    \
				__LINE__,                                                      \
				"'");                                                          \
	} while(0)

/**
 * Validates the range of an @c enum in @c operator>>().
 *
 * The typical use case is:
 * @code
 * if(enumerate == "member_1") { ...; return; }
 * if(enumerate == "member_2") { ...; return; }
 *
 * ENUM_FAIL_INPUT(enumerate);
 * @endcode
 * @warning The compiler cannot verify whether all cases are handled properly
 * so this error might be more common as @ref ENUM_FAIL_OUTPUT.
 *
 * @pre                           The following assertion holds:
 *                                @code std::is_same<std::remove_cv
 *                                <std::remove_reference<decltype(enumerate)>::
 *                                type>::type == true @endcode
 *                                Or, less formal, the @p enumerate is a @c
 *                                std::string.
 *
 * @param enumerate               The enumerate which failed.
 */
#define ENUM_FAIL_INPUT(enumerate)                                             \
	do {                                                                       \
		static_assert(                                                         \
				std::is_same<std::remove_cv<std::remove_reference<decltype(    \
									 enumerate)>::type>::type,                 \
							 std::string>::value,                              \
				"The enumerate parameter must be a string type.");             \
		throw ::lib::texception(                                               \
				::lib::texception::ttype::invalid_value,                       \
				"Enumerate out of range during input, value '",                \
				enumerate,                                                     \
				"' in function '",                                             \
				__PRETTY_FUNCTION__,                                           \
				"' file '",                                                    \
				__FILE__,                                                      \
				"' line '",                                                    \
				__LINE__,                                                      \
				"'");                                                          \
	} while(0)

/**
 * Validates the range of an @c enum in a function.
 *
 * The typical use case is:
 * @code
 * switch(enumerate) {
 *     case member_1 : ...; return;
 *     case member_2 : ...; return;
 * }
 * ENUM_FAIL_OUTPUT(enumerate);
 * @endcode
 *
 * @note Normally the compiler can warn if a member of an enum is not handled,
 * at least when the @c switch doesn't have a default handler. So the error
 * should normally never trigger.
 *
 * @pre                           The following assertion holds:
 *                                @code
 *                                std::is_enum<decltype(enumerate)>::value ==
 *                                true
 *                                @endcode
 * @pre                           enumerate can be converted to a string with
 *                                @c operator<<, if not use
 *                                @ref ENUM_FAIL_OUTPUT instead.
 *
 * @param enumerate               The enumerate which failed.
 */
#define ENUM_FAIL_RANGE(enumerate)                                             \
	do {                                                                       \
		static_assert(std::is_enum<decltype(enumerate)>::value,                \
					  "The enumerate parameter must be an enum type.");        \
		throw ::lib::texception(::lib::texception::ttype::internal_failure,    \
								"Enumerate out of range, value '",             \
								enumerate,                                     \
								"' in function '",                             \
								__PRETTY_FUNCTION__,                           \
								"' file '",                                    \
								__FILE__,                                      \
								"' line '",                                    \
								__LINE__,                                      \
								"'");                                          \
	} while(0)


/**
 * Unconditional error when a not implemented part of code is reached.
 *
 * This function can be used when a not implemented part of code causes a
 * fatal error.
 *
 * @note The implementation uses a @c static_assert(true), when changing the
 * value of the boolean, the compilation will fail if this macro is used in
 * the code.
 */
#define NOT_IMPLEMENTED_YET                                                    \
	do {                                                                       \
		static_assert(true, "Not implemented code is not allowed.");           \
		throw ::lib::texception(::lib::texception::ttype::not_implemented_yet, \
								"'Code not implemented in function '",         \
								__PRETTY_FUNCTION__,                           \
								"' file '",                                    \
								__FILE__,                                      \
								"' line '",                                    \
								__LINE__,                                      \
								"'");                                          \
	} while(0)

#endif
