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

#include "modules/logger/logger.hpp"

#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>

REGISTER_LOGGER_MODULE("/unit_test/modules/logger")

using namespace logger;

class tstream
{
	using text_sink = boost::log::sinks::
			synchronous_sink<boost::log::sinks::text_ostream_backend>;

public:
	tstream()
	{
		TRACE;

		/* Remove default logging settings. */
		boost::log::core::get()->remove_sink(sink());
		header_writer() = header_writer_null;

		/* Set our logging settings. */
		sink_->locked_backend()->add_stream(stream_);
		boost::log::core::get()->add_sink(sink_);
	}

	~tstream()
	{
		TRACE;

		/* Remove our logging settings. */
		boost::log::core::get()->remove_sink(sink_);

		/* Set default logging settings. */
		boost::log::core::get()->add_sink(sink());
		header_writer() = old_header_;
	}

	std::stringstream& stream()
	{
		return *stream_;
	}

private:
	boost::shared_ptr<text_sink> sink_{boost::make_shared<text_sink>()};

	boost::shared_ptr<std::stringstream> stream_{
			boost::make_shared<std::stringstream>()};

	std::function<void(boost::log::record_ostream&, const tseverity)>
	old_header_{header_writer()};
};

static void log()
{
	TRACE;

	tstream output;

	{
		tmodule::set_severity("/unit_test/modules/logger", tseverity::fatal);

		LOG_T('T');
		LOG_D('D');
		LOG_I('I');
		LOG_W('W');
		LOG_E('E');
		LOG_F('F');

		BOOST_CHECK_EQUAL(output.stream().str(), "F\n");
		output.stream().str(std::string());
	}

	{
		tmodule::set_severity("/unit_test/modules/logger", tseverity::error);

		LOG_T('T');
		LOG_D('D');
		LOG_I('I');
		LOG_W('W');
		LOG_E('E');
		LOG_F('F');

		BOOST_CHECK_EQUAL(output.stream().str(), "E\nF\n");
		output.stream().str(std::string());
	}

	{
		tmodule::set_severity("/unit_test/modules/logger", tseverity::warning);

		LOG_T('T');
		LOG_D('D');
		LOG_I('I');
		LOG_W('W');
		LOG_E('E');
		LOG_F('F');

		BOOST_CHECK_EQUAL(output.stream().str(), "W\nE\nF\n");
		output.stream().str(std::string());
	}

	{
		tmodule::set_severity("/unit_test/modules/logger",
							  tseverity::information);

		LOG_T('T');
		LOG_D('D');
		LOG_I('I');
		LOG_W('W');
		LOG_E('E');
		LOG_F('F');

		BOOST_CHECK_EQUAL(output.stream().str(), "I\nW\nE\nF\n");
		output.stream().str(std::string());
	}

	{
		tmodule::set_severity("/unit_test/modules/logger", tseverity::debug);

		LOG_T('T');
		LOG_D('D');
		LOG_I('I');
		LOG_W('W');
		LOG_E('E');
		LOG_F('F');

		BOOST_CHECK_EQUAL(output.stream().str(), "D\nI\nW\nE\nF\n");
		output.stream().str(std::string());
	}

	{
#ifdef ENABLE_TRACE_LOGGER
		tmodule::set_severity("/unit_test/modules/logger", tseverity::trace);

		LOG_T('T');
		LOG_D('D');
		LOG_I('I');
		LOG_W('W');
		LOG_E('E');
		LOG_F('F');

		BOOST_CHECK_EQUAL(output.stream().str(), "T\nD\nI\nW\nE\nF\n");
		output.stream().str(std::string());
#else
		std::cerr << "WARNING: compiled without -DENABLE_TRACE_LOGGER."
					 " The trace logger can't be tested.\n";
#endif
	}

	tmodule::set_severity("/unit_test/modules/logger", tseverity::warning);
}

BOOST_AUTO_TEST_CASE(test_modules_logger_logger)
{
	TRACE;

	log();
}
