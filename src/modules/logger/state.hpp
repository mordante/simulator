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

#ifndef MODULES_LOGGER_STATE_HPP_INCLUDED
#define MODULES_LOGGER_STATE_HPP_INCLUDED

#include "modules/logger/severity.hpp"

#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>

namespace logger
{

/** Helper typedef, not really used. */
using tsink = boost::log::sinks::synchronous_sink
		<boost::log::sinks::text_ostream_backend>;

/**
 * The default sink used in the logger.
 *
 * @note It uses a boost::shared_ptr, since that is required by the logger's
 * API.
 *
 * @note It is possible to change the default sink, but it is mainly intended
 * to be used for the unit tests, not for normal usage.
 */
boost::shared_ptr<tsink>& sink();

/** The log source used for logging. */
boost::log::sources::logger_mt& log_source();

/**
 * The default for @ref header_writer.
 *
 * The default writes the time, thread id and severity as header.
 *
 * @param stream                  The log record stream to write to.
 * @param severity                The severity of the log record being written.
 */
void header_writer_default(boost::log::record_ostream& stream,
						   const tseverity severity);
/**
 * A NULL writer for @ref header_writer.
 *
 * This version does nothing.
 */
void header_writer_null(boost::log::record_ostream& stream,
						const tseverity severity);

/**
 * The function used to write the header of a log record.
 *
 * @note It is possible to change the default function, but it is mainly
 * intended to be used for the unit tests, not for normal usage.
 *
 * See @ref header_writer_default for more information.
 */
std::function<void(boost::log::record_ostream&, const tseverity)>&
header_writer();

} // namespace logger

#endif
