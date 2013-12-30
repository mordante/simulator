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

#include "modules/logger/state.hpp"

#include <boost/utility/empty_deleter.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <thread>

namespace logger
{

namespace detail
{

static boost::shared_ptr<tsink> sink()
{
	boost::shared_ptr<tsink> result{boost::make_shared<tsink>()};

	boost::shared_ptr<std::ostream> stream(&std::clog, boost::empty_deleter());
	result->locked_backend()->add_stream(stream);

	return result;
}

} // namespace detail

boost::shared_ptr<tsink>& sink()
{
	static boost::shared_ptr<tsink> result{detail::sink()};

	return result;
}

namespace detail
{
static boost::log::sources::logger_mt log_source()
{
	boost::log::core::get()->add_sink(logger::sink());

	boost::log::sources::logger_mt result;
	return result;
}

} // namespace detail

boost::log::sources::logger_mt& log_source()
{
	static boost::log::sources::logger_mt result{detail::log_source()};

	return result;
}

void header_writer_default(boost::log::record_ostream& stream,
						   const tseverity severity)
{
	stream << boost::posix_time::to_iso_extended_string(
					  boost::posix_time::microsec_clock::local_time()) << " 0x"
		   << std::hex << std::this_thread::get_id() << std::dec << " "
		   << severity << ": ";
}

void header_writer_null(boost::log::record_ostream&, const tseverity)
{
}

std::function<void(boost::log::record_ostream&, const tseverity)>&
header_writer()
{
	static std::function<void(boost::log::record_ostream&, const tseverity)>
	result{header_writer_default};
	return result;
}

} // namespace logger
