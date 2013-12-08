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

#include "unit_test/exception.hpp"

#include "modules/logger/logger.hpp"

REGISTER_LOGGER_MODULE("/unit_test")

bool exception_type_predicate(const lib::texception& exception,
							  const lib::texception::ttype type)
{
	TRACE_PARAMETERS(type);

	if(exception.type != type) {
		LOG_E("Exception type mismatch, expected »",
			  type,
			  "« received »",
			  exception.type,
			  "«.\n");

		return false;
	}

	return true;
}

bool exception_type_predicate_message(const lib::texception& exception,
									  const lib::texception::ttype type,
									  const std::string& message)
{
	TRACE_PARAMETERS(type, message);

	if(exception.type != type) {
		LOG_E("Exception type mismatch, expected »",
			  type,
			  "« received »",
			  exception.type,
			  "«.\n");

		return false;
	}

	if(exception.message != message) {
		LOG_E("Exception message mismatch,\nexpected »",
			  message,
			  "«\nreceived »",
			  exception.message,
			  "«.\n");

		return false;
	}

	return true;
}
