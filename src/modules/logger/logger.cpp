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

#include "modules/logger/logger.hpp"

namespace logger
{

boost::log::sources::severity_logger_mt<tseverity>& tlogger::stream()
{
	static boost::log::sources::severity_logger_mt<tseverity> result;
	return result;
}

} // namespace logger
