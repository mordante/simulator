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

#include "lib/exception/validate.tpp"

namespace logger
{

tlogger::tproxy::~tproxy()
{
	stream_.flush();
	log_source().push_record(std::move(record_));
}

boost::log::record tlogger::tproxy::record_constructor()
{
	boost::log::record result{log_source().open_record()};
	VALIDATE(result);
	return result;
}

} // namespace logger
