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

#ifndef LIB_EXCEPTION_THROW_TPP_INCLUDED
#define LIB_EXCEPTION_THROW_TPP_INCLUDED

/**
 * @file
 * Defines the base throw macros.
 */

#include "modules/logger/logger.hpp"
#include "lib/exception/exception.hpp"

/**
 * Helper macro for throwing exceptions and logging them at the same time.
 *
 * The macro is not intended to be used directly, instead the helper macros
 * are intended to be used:
 * - @ref THROW_F for throwing fatal errors.
 * - @ref THROW_E for throwing errors.
 * - @ref THROW_W for throwing warnings.
 * - @ref THROW_I for throwing information messages.
 * - @ref THROW_D for throwing debug messages.
 * - @ref THROW_T for throwing trace messages. Note whether or not the trace
 *   messages are available depends on whether or not the ENABLE_TRACE_LOGGER
 *   macro is defined.
 *
 * @param severity                The severity of the message; one of
 *                                @ref logger::tseverity.
 * @param type                    The type of the exception; one of
 *                                @ref lib::texception::ttype.
 * @param ...                     A list of parameters that are concatenated
 *                                by @ref lib::concatenate to create the
 *                                message of the exception and the message to
 *                                be logged.
 */
#define THROW(severity, type, ...)                                             \
	do {                                                                       \
		::std::string message{ ::lib::concatenate(__VA_ARGS__)};               \
		LOG(::logger::tseverity::severity,                                     \
			"Throwing »",                                                      \
			::lib::texception::ttype::type,                                    \
			"« message »",                                                     \
			message,                                                           \
			"«.");                                                             \
		throw ::lib::texception{ ::lib::texception::ttype::type,               \
								 std::move(message)};                          \
	} while(0)

/**
 * The @ref THROW macro for the @ref logger::tseverity::fatal severity.
 */
#define THROW_F(type, ...) THROW(fatal, type, __VA_ARGS__)

/**
 * The @ref THROW macro for the @ref logger::tseverity::error severity.
 */
#define THROW_E(type, ...) THROW(error, type, __VA_ARGS__)

/**
 * The @ref THROW macro for the @ref logger::tseverity::warning severity.
 */
#define THROW_W(type, ...) THROW(warning, type, __VA_ARGS__)

/**
 * The @ref THROW macro for the @ref logger::tseverity::information severity.
 */
#define THROW_I(type, ...) THROW(information, type, __VA_ARGS__)

/**
 * The @ref THROW macro for the @ref logger::tseverity::debug severity.
 */
#define THROW_D(type, ...) THROW(debug, type, __VA_ARGS__)

#ifdef ENABLE_TRACE_LOGGER
/**
 * The @ref THROW macro for the @ref logger::tseverity::trace severity.
 */
#define THROW_T(type, ...) THROW(trace, type, __VA_ARGS__)
#endif

#endif
