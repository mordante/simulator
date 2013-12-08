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

#ifndef MODULES_LOGGER_SEVERITY_HPP_INCLUDED
#define MODULES_LOGGER_SEVERITY_HPP_INCLUDED

/**
 * @file
 * Defines the severities for the logging engine.
 *
 * See @ref logger_module.
 */

namespace logger
{

/**
 * The log severities.
 *
 * The severities are listed in ascending severity. The description of the
 * severities holds a bit of the policy, maybe that part should be moved to
 * the design document.
 */
enum class tseverity {
	/**
	 * Fatal error messages.
	 *
	 * These messages are shown when something goes completely wrong. When
	 * this happens the program or one of its threads stops working. This
	 * message is always shown in the logs.
	 */
	fatal

	/**
	 * Error messages.
	 *
	 * These messages are shown when something goes wrong unexpectedly. This
	 * is the highest severity level to be enabled by the user. This message
	 * is always shown in the logs.
	 */
	,
	error

	/**
	 * Warning messages.
	 *
	 * These are shown when something goes wrong which is `kind of expected'
	 * eg an invalid filename is a rather common issue. A network which
	 * cannot be reached as well.
	 */
	,
	warning

	/**
	 * Information messages.
	 *
	 * Information for the user. Can be starting of a certain operation.
	 */
	,
	information

	/**
	 * Debug messages.
	 *
	 * Messages to be used to show debug information. This is the lowest
	 * severity to be enabled by the user.
	 */
	,
	debug

#ifdef ENABLE_TRACE_LOGGER
	/**
	 * Tracing messages.
	 *
	 * Tracing messages are used in modules to get an indication which
	 * functions are called with which parameters. This severity is not
	 * intended to be enabled by the normal user.
	 */
	,
	trace
#endif
};

} // namespace logger

#include "lib/utility/enumerate.tpp"

namespace logger
{

ENUM_DECLARE_STREAM_OPERATORS(::logger::tseverity)

} // namespace logger

#endif
