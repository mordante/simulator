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
#include "modules/logger/state.hpp"

#ifdef ENABLE_TRACE_LOGGER
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#endif

namespace logger
{

/** Helper class to do the actual logging for a module. */
class tlogger final
{
	/***** ***** ***** ***** Types. ***** ***** ***** *****/

	/** Small helper struct for the logging engine. */
	struct tproxy
	{
		~tproxy();

		boost::log::record_ostream& stream()
		{
			return stream_;
		}

		boost::log::record record_{record_constructor()};
		boost::log::record_ostream stream_{record_};

	private:
		boost::log::record record_constructor();
	};

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


	/***** ***** ***** ***** Operations. ***** ***** ***** *****/

	/**
	 * The log function.
	 *
	 * @note We expect that
	 * @code VALIDATE(static_cast<bool>(*this)); @endcode
	 * won't throw, but we will not test it. In multi-thread code the
	 * @ref logger::tseverity can be changed for the module between the test
	 * whether to log and this function call. So just log it. This also
	 * allows the logger to be used when the @ref logger::tseverity doesn't
	 * hold true.
	 *
	 * @tparam Pack               The type of the items to be logged.
	 *
	 * @param pack                The items to be logged.
	 */
	template <class... Pack>
	void log(Pack&&... pack)
	{
		tproxy proxy;
		header_writer()(proxy.stream(), severity_);
		log(proxy, std::forward<Pack>(pack)...);
	}

	/** The zero parameter log function is not allowed. */
	void log() = delete;


	/***** ***** ***** ***** Members. ***** ***** ***** *****/
private:
	/**
	 * The logger's module.
	 *
	 * This is the module for which the log messages are generated.
	 */
	const tmodule& module_;

	/** The severity of the messages to write. */
	const tseverity severity_;


	/***** ***** ***** ***** Operations. ***** ***** ***** *****/

	/**
	 * The log function for one parameter.
	 *
	 * This is an internal function used for the real logging.
	 *
	 * @param proxy               The proxy used to get the output stream.
	 * @param rhs                 The parameter to write to the log.
	 */
	template <class T>
	void log(tproxy& proxy, T&& rhs)
	{
		proxy.stream() << rhs;
	}

	/**
	 * The log function for multiple parameter.
	 *
	 * This is an internal function used for the real logging.
	 *
	 * @param proxy               The proxy used to get the output stream.
	 * @param rhs                 The parameter to write to the log.
	 * @param pack                The other items to be logged.
	 */
	template <class T, class... Pack>
	void log(tproxy& proxy, T&& rhs, Pack&&... pack)
	{
		proxy.stream() << rhs;
		log(proxy, std::forward<Pack>(pack)...);
	}
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
