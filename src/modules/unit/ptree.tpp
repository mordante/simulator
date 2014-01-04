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

#ifndef MODULES_UNIT_PTREE_TPP_INCLUDED
#define MODULES_UNIT_PTREE_TPP_INCLUDED

/**
 * @file
 * Contains the @ref boost::property_tree converters.
 *
 * The code is based on the code for the converters in the code of @ref
 * boost::property_tree.
 *
 * See @ref unit_module for more information.
 */

#include <boost/property_tree/ptree.hpp>

namespace unit
{

template <typename Ch, typename Traits, typename Alloc, typename Q>
struct ptree_converter
{
	using T = typename Q::type;

	using customized = boost::property_tree::customize_stream<Ch, Traits, T>;
	using internal_type = std::basic_string<Ch, Traits, Alloc>;
	using external_type = Q;

	explicit ptree_converter(std::locale locale__ = std::locale())
		: locale_{locale__}
	{
	}

	boost::optional<external_type> get_value(const internal_type& string)
	{
		std::basic_istringstream<Ch, Traits, Alloc> iss{string};
		iss.imbue(locale_);
		T value;
		customized::extract(iss, value);
		if(iss.fail() || iss.bad() || iss.get() != Traits::eof()) {
			return boost::optional<external_type>{};
		}
		return boost::optional<external_type>{external_type{value}};
	}

	boost::optional<internal_type> put_value(const external_type& quantity)
	{
		std::basic_ostringstream<Ch, Traits, Alloc> oss;
		oss.imbue(locale_);
		customized::insert(oss, quantity.value);
		if(oss) {
			return oss.str();
		}
		return boost::optional<internal_type>{};
	}

private:
	std::locale locale_;
};

} // namespace unit

namespace boost
{
namespace property_tree
{

template <typename Ch, typename Traits, typename Alloc, class U, class T>
struct translator_between<std::basic_string<Ch, Traits, Alloc>,
						  unit::tquantity<U, T>>
{
	using type
			= unit::ptree_converter<Ch, Traits, Alloc, unit::tquantity<U, T>>;
};

} // namespace property_tree
} // namespace boost

#endif
