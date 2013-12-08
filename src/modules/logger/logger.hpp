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

#ifndef MODULES_LOGGER_LOGGER_HPP_INCLUDED
#define MODULES_LOGGER_LOGGER_HPP_INCLUDED

/**
 * @file
 * Defines the logging engine.
 *
 * See @ref logger_module.
 */

#include "modules/logger/module.hpp"

#ifdef ENABLE_TRACE_LOGGER
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#endif
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/common.hpp>

namespace logger
{

/** Helper class to do the actual logging for a module. */
class tlogger final
{
public:
	/***** Constructors, assign operators, destructor. *****/

	explicit constexpr tlogger(const tmodule& module__,
							   const tseverity severity__)
		: module_{std::move(module__)}, severity_{severity__}
	{
	}

	~tlogger() = default;

	tlogger& operator=(tlogger&&) = delete;
	tlogger(tlogger&&) = delete;

	tlogger& operator=(const tlogger&) = delete;
	tlogger(const tlogger&) = delete;


	/***** ***** ***** ***** Conversion operators. ***** ***** ***** *****/

	/**
	 * The bool operator.
	 *
	 * Depending on the @ref severity_ and the current @ref tseverity of the
	 * @ref module_, messages are allowed or not allowed to be written. This
	 * operator returns @c true if the messages are allowed, and @c false
	 * otherwise.
	 */
	explicit constexpr operator bool() const
	{
		return module_.get_severity() >= severity_;
	}

	/**
	 * The log function.
	 *
	 * There are several overloads for more parameters, they all behave the
	 * same in logging all their parameters.
	 *
	 * @note The number of log functions is determined by the number required
	 * by the compiler.
	 *
	 * @note We expect that
	 * @code VALIDATE(static_cast<bool>(*this)); @endcode
	 * won't throw, but we will not test it. In multi-thread code the
	 * @ref logger::tseverity can be changed for the module between the test
	 * whether to log and this function call. So just log it. This also
	 * allows the logger to be used when the @ref logger::tseverity doesn't
	 * hold true.
	 *
	 * @tparam T0                 The type of the item to be logged.
	 *
	 * @param p0                  The item to be logged.
	 */
	template <class T0>
	void log(const T0& p0)
	{
		BOOST_LOG_SEV(stream(), severity_) << p0;
	}

	template <class T0, class T1>
	void log(const T0& p0, const T1& p1)
	{
		BOOST_LOG_SEV(stream(), severity_) << p0 << p1;
	}
#if 1
#define BUILD_LOG_FUNCTION_SHIFT(UNUSED, N, PARAM) << PARAM##N

#define BUILD_LOG_FUNCTION(UNUSED1, N, UNUSED2)                                \
	template <BOOST_PP_ENUM_PARAMS(N, class T)>                                \
	inline void log(BOOST_PP_ENUM_BINARY_PARAMS(N, const T, &p))               \
	{                                                                          \
		BOOST_LOG_SEV(stream(), severity_)                                     \
				BOOST_PP_REPEAT(N, BUILD_LOG_FUNCTION_SHIFT, p);               \
	}

#define BUILD_LOG_FUNCTION_MAX 16

	/**
	 * Generates the log functions.
	 *
	 * It generates them for 3 to BUILD_LOG_FUNCTION_MAX - 1 parameters.
	 */
	BOOST_PP_REPEAT_FROM_TO(3, BUILD_LOG_FUNCTION_MAX, BUILD_LOG_FUNCTION, )

#undef BUILD_LOG_FUNCTION_MAX
#undef BUILD_LOG_FUNCTION
#undef BUILD_LOG_FUNCTION_SHIFT
#endif

private:
	/**
	 * The logger's module.
	 *
	 * This is the module for which the log messages are generated.
	 */
	const tmodule& module_;

	/** The severity of the messages to write. */
	const tseverity severity_;

	/** The stream to log to. */
	static boost::log::sources::severity_logger_mt<tseverity>& stream();
};

} // namespace logger

/**
 * Basic logger macro.
 *
 * @warning The data to be logged is expected to have
 * @code std::ostream& operator<<(std::ostream&, const T&); @endcode
 *
 * @note The macro uses lazy evaluation of its arguments, so if the message
 * is not logged, the @c __VA_ARGS__ are not evaluated, so make sure they
 * have no side effects.
 *
 * @note This macro is not intended for direct usage, use the LOG_<i>x</i>
 * macros instead.
 *
 * @param severity                The severity to log.
 * @param ...                     The data to log.
 */
#define LOG(severity, ...)                                                     \
	do {                                                                       \
		::logger::tlogger logger{ ::module_logger, severity};                  \
		if(logger) {                                                           \
			logger.log(__VA_ARGS__);                                           \
		}                                                                      \
	} while(0)

#ifdef ENABLE_TRACE_LOGGER
#define LOG_T(...) LOG(::logger::tseverity::trace, __VA_ARGS__)

/** Expands a boost macro to the actual textual value of the string. */
#define TRACE_PARAMETER_STRINGIFY(PARAMETER) #PARAMETER

/**
 * Does the magic for the parameters.
 *
 * Turns a variable foo into
 * " FOO »", foo, "«"
 * where FOO stands for the stringified name of the variable.
 *
 * Note it dumps several string literals without a comma, the compiler will
 * concatenate them and thus reduce the number of function calls.
 */
#define TRACE_PARAMETER(UNUSED1, UNUSED2, PARAMETER)                           \
	" " TRACE_PARAMETER_STRINGIFY(PARAMETER) " »", PARAMETER, "«"


/**
 * Turns a set of function parameters into a nice trace message.
 *
 * The parameters are <i>only</i> the parameters to print, no string literals.
 */
#define TRACE_PARAMETERS(...)                                                  \
	LOG(::logger::tseverity::trace,                                            \
		__PRETTY_FUNCTION__,                                                   \
		" [PARAMETERS]" BOOST_PP_SEQ_FOR_EACH(                                 \
				TRACE_PARAMETER, , BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) ".")


#define TRACE LOG(::logger::tseverity::trace, __PRETTY_FUNCTION__, ".")

#define TRACE_SETTER(current, argument)                                        \
	LOG(::logger::tseverity::trace,                                            \
		__PRETTY_FUNCTION__,                                                   \
		" [SETTER] current value »",                                           \
		current,                                                               \
		"« new value »",                                                       \
		argument,                                                              \
		"«.")

#define TRACE_GETTER(current)                                                  \
	LOG(::logger::tseverity::trace,                                            \
		__PRETTY_FUNCTION__,                                                   \
		" [GETTER] current value »",                                           \
		current,                                                               \
		"«.")
#else
#define LOG_T(...)                                                             \
	do {                                                                       \
	} while(0)
#define TRACE                                                                  \
	do {                                                                       \
	} while(0)
#define TRACE_PARAMETERS(...)                                                  \
	do {                                                                       \
	} while(0)
#define TRACE_SETTER(current, argument)                                        \
	do {                                                                       \
	} while(0)
#define TRACE_GETTER(current)                                                  \
	do {                                                                       \
	} while(0)
#endif

#define LOG_D(...) LOG(::logger::tseverity::debug, __VA_ARGS__)
#define LOG_I(...) LOG(::logger::tseverity::information, __VA_ARGS__)
#define LOG_W(...) LOG(::logger::tseverity::warning, __VA_ARGS__)
#define LOG_E(...) LOG(::logger::tseverity::error, __VA_ARGS__)
#define LOG_F(...) LOG(::logger::tseverity::fatal, __VA_ARGS__)

#endif
