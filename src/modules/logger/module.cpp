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

#include "modules/logger/module.hpp"

#include "lib/exception/validate.tpp"
#include "modules/logger/logger.hpp"

#include <boost/algorithm/string.hpp>

namespace logger
{

tmodule::tmodule(std::string id__) : id_{std::move(id__)}
{
	VALIDATE(!id_.empty());
	VALIDATE(id_.find('/') == std::string::npos);
	VALIDATE(id_.find('*') == std::string::npos);
}

/** @note This function looks quite similar to @ref register_logger_module. */
tmodule* tmodule::find(const std::string& path)
{
	VALIDATE(!path.empty());

	tmodule* result{&module()};

	/*
	 * Note lib::split returns 2 elements if path == "/".
	 * So handle this case manually. Since the register function can never
	 * have a non-existing root the test is not there.
	 */
	if(path == "/") {
		return result;
	}

	std::vector<std::string> walk;
	boost::split(walk, path, boost::is_any_of("/"));

	VALIDATE(!walk.empty());
	VALIDATE(walk.front().empty());

	walk.erase(walk.begin());
	while(!walk.empty()) {
		VALIDATE(!walk.front().empty());
		VALIDATE(walk.front().find('*') == std::string::npos);
		for(auto& child : result->children()) {
			if(child.id() == walk.front()) {
				result = &child;
				goto loop;
			}
		}

		/* Didn't find the path. */
		return nullptr;
	loop:
		walk.erase(walk.begin());
	}
	return result;
}

bool tmodule::set_severity(std::string path, const tseverity severity)
{
	VALIDATE(!path.empty());

	const bool recursive{path[path.size() - 1] == '*'};
	if(recursive) {
		path.erase(path.size() - 1);
	}

	tmodule* module{tmodule::find(path)};
	if(!module) {
		return false;
	}

	if(recursive) {
		module->set_severity_recursive(severity);
	} else {
		module->set_severity(severity);
	}

	return true;
}

static std::string build_tree(const tmodule& module, std::string path)
{
	std::string id{path + module.id()};
	const std::size_t wanted_width{40};
	if(id.size() < wanted_width) {
		id.resize(wanted_width, ' ');
	} else {
		id += ' ';
	}

	std::stringstream result;
	result << id << module.get_severity() << '\n';
	if(!module.id().empty()) {
		path += module.id() + '/';
	}
	for(const auto& child : module.children()) {
		result << build_tree(child, path);
	}
	return result.str();
}

std::string tmodule::tree()
{
	return build_tree(module(), "/");
}

const std::string& tmodule::id() const
{
	return id_;
}

void tmodule::set_severity(const tseverity severity)
{
	severity_ = severity;
}

tseverity tmodule::get_severity() const
{
	return severity_;
}

std::deque<tmodule>& tmodule::children()
{
	return children_;
}

const std::deque<tmodule>& tmodule::children() const
{
	return children_;
}

void tmodule::set_severity_recursive(const tseverity severity)
{
	set_severity(severity);
	for(auto& child : children_) {
		child.set_severity_recursive(severity);
	}
}

tmodule& module()
{
	static tmodule result;
	return result;
}

/** @note This function looks quite similar to @ref tmodule::find. */
tmodule& register_logger_module(const std::string& path)
{
	VALIDATE(!path.empty());

	tmodule* result{tmodule::find(path)};
	if(result) {
		return *result;
	}

	result = &module();

	std::vector<std::string> walk;
	boost::split(walk, path, boost::is_any_of("/"));

	VALIDATE(!walk.empty());
	VALIDATE(walk.front().empty());

	walk.erase(walk.begin());
	while(!walk.empty()) {
		VALIDATE(!walk.front().empty());
		VALIDATE(walk.front().find('*') == std::string::npos);
		for(auto& child : result->children()) {
			if(child.id() == walk.front()) {
				result = &child;
				goto loop;
			}
		}

		result->children().emplace_back(walk.front());
		result = &result->children().back();

	loop:
		walk.erase(walk.begin());
	}
	return *result;
}

} // namespace logger
