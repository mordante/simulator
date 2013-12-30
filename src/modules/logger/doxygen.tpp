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

/**
 * @page logger_module The logger module
 *
 * Every application has a singleton module tree, retrieved by calling
 * @ref logger::module. Every file that uses the logger should include a line
 * like:
@code
REGISTER_LOGGER_MODULE(<path>)
@endcode
 * where @p \<path\> is a string literal containing an absolute path for the
 * module. This creates the path in the module tree. The path should look
 * like an absolute UNIX path, e.g. '/modules/logger'. The forward slash is
 * used as separator between the module parts and the path should not contain
 * an asterisk  '*'. The usage of '.' and '..' has no special meaning.
 *
 * In order to use the logger there are several logger macros:
 * - @ref LOG_F for logging fatal errors.
 * - @ref LOG_E for logging errors.
 * - @ref LOG_W for logging warnings.
 * - @ref LOG_I for logging information messages.
 * - @ref LOG_D for logging debug messages.
 * - @ref LOG_T for logging trace messages. Note whether or not the trace
 *   messages are available depends on compiler settings and there are also
 *   multiple helper macros for trace messages. Trace messages are intended
 *   to give a trace log of function calls. (Except in the logger module
 *   itself to avoid recursive messages.) There are several extra helper
 *   macros for the trace messages.
 *
 * Whether or not a message logged is also 'displayed' depends on the @ref
 * logger::tseverity of the @ref logger::tmodule. By default new domains are
 * set to @ref logger::tseverity::warning, but this can be changed by an
 * application. (This should be implemented in the application.)
 *
 * @warning It is expected that the module tree is build in the application
 * before @c main is called. The tree itself in intended to be static and
 * only the @ref logger::tseverity of the module is expected to be changed.
 * Other changes in a multi-threaded context may lead to <i>undefined
 * behaviour</i>.
 */
