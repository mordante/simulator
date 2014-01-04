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

#ifndef MODULES_LOGGER_MODULE_HPP_INCLUDED
#define MODULES_LOGGER_MODULE_HPP_INCLUDED

/**
 * @file
 * Defines the modules for the logging engine.
 *
 * See @ref logger_module.
 */

#include "modules/logger/severity.hpp"

#include <atomic>
#include <deque>

namespace logger
{

/**
 * The module structure for the logger.
 */
class tmodule final
{
private:
	/***** ***** Constructors, assignment and destructor. ***** *****/

	friend tmodule& module();

	/**
	 * Constructor.
	 *
	 * Only the default constructor can write a module with an empty
	 * @ref id_. This node is the root node. In order to avoid unwanted
	 * behaviour this constructor is private and only our friend @ref module
	 * is supposed to call us.
	 */
	tmodule() = default;

public:
	explicit tmodule(std::string id__);

	~tmodule() = default;

	tmodule& operator=(tmodule&&) = delete;
	tmodule(tmodule&&) = delete;

	tmodule& operator=(const tmodule&) = delete;
	tmodule(const tmodule&) = delete;


	/***** ***** Operations. ***** *****/

	/**
	 * Finds a module by using an absolute path lookup.
	 *
	 * @pre                       @p path contains a valid absolute path.
	 *
	 * @param path                The path of the module.
	 *
	 * @returns                   The module found.
	 * @retval nullptr            If no module found.
	 */
	static tmodule* find(const std::string& path);

	/**
	 * Sets the severity of a module by using an absolute path.
	 *
	 * Since it is intended that the configuration files can contain paths to
	 * invalid modules it will ignore invalid modules. (Of course it would be
	 * nice to validate in the schema whether a module is valid, but the
	 * modules are created in an ad hock fashion and may depend on the
	 * modules and libraries linked in an application.)
	 *
	 * If the last element of the @p path is an asterisk '*' it sets the
	 * severity recursively. E.g. '/modules*' sets the severity of:
	 * - /modules
	 * - /modules/logger
	 * - /modules/logger/foo
	 * - /modules/logger/bar
	 * - /modules/foo
	 * - /modules/foo/bar
	 * - /modules/bar
	 * - etc.
	 *
	 * In order to set the severity for all modules use "/\*" as @p path.
	 * This can be used to change the default severity.
	 *
	 * @pre                       @p path contains a valid absolute path or a
	 *                            valid wildcard path.
	 *
	 * @param path                The path to a module.
	 * @param severity            The new severity.
	 *
	 * @returns                   Whether the path pointed to a module,
	 *                            @c true, means 'yes' and @c false means
	 *                            'no'.
	 */
	static bool set_severity(std::string path, const tseverity severity);

	/**
	 * Debug function to display the module tree.
	 *
	 * The function is added for debugging purposes and the format of the
	 * output is not part of the function's contract.
	 *
	 * @returns                   A string with the module tree.
	 */
	static std::string tree();


	/***** ***** Setters and getters. ***** *****/

	const std::string& id() const;

	void set_severity(const tseverity severity);

	tseverity get_severity() const;

	std::deque<tmodule>& children();

	const std::deque<tmodule>& children() const;


	/***** ***** Members. ***** *****/

private:
	/**
	 * The id of the module.
	 *
	 * The name of a module shall not contain a forward slash '/' or a
	 * asterisk. It may only contain an empty string for the root node.
	 * (Therefore the default constructor is @c private.)
	 */
	std::string id_{};

	/** The logging severity of this module. */
	std::atomic<tseverity> severity_{tseverity::warning};

	/**
	 * The sub-modules belonging to this module.
	 *
	 * @note The children are stored in a @c std::deque to avoid adding a child
	 * invalidating pointers to existing items. This is required to avoid
	 * invalidating pointers returned by @ref find.
	 */
	std::deque<tmodule> children_{};


	/***** ***** Operations. ***** *****/

	/**
	 * Sets the severity of a module in a recursive fashion.
	 */
	void set_severity_recursive(const tseverity severity);
};

/**
 * Returns the module singleton for an application.
 */
tmodule& module();

/**
 * Registers a module.
 *
 * It is safe to register a single module multiple times. Doing so will not
 * result in multiple modules with the same name, instead the existing module
 * is returned.
 *
 * @pre                           @p path contains a valid absolute path.
 *
 * @param path                    The path of the module.
 *
 * @returns                       The module.
 */
tmodule& register_logger_module(const std::string& path);

/**
 * Helper macro to register a module.
 *
 * This macro registers a module and creates helper variable that is used in
 * the LOG_<i>x</i> macros.
 *
 * @param ID                      Forwarded to
 *                                @ref logger::register_logger_module.
 */
#define REGISTER_LOGGER_MODULE(ID)                                             \
	namespace                                                                  \
	{                                                                          \
	::logger::tmodule& module_logger{ ::logger::register_logger_module(ID)};   \
	}

#define LOGGER_MODULE ::module_logger

} // namespace logger

#endif
