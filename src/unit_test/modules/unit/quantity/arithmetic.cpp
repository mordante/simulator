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

#include "modules/unit/quantity/arithmetic.tpp"

#include "modules/logger/logger.hpp"
#include "modules/unit/quantity/stream.hpp"
#include "modules/unit/quantity/comparison.tpp"
#include "modules/unit/types.tpp"

#include <boost/test/unit_test.hpp>

#include <type_traits>

REGISTER_LOGGER_MODULE("/unit_test/modules/unit")

using namespace unit;

#define EXECUTE(function)                                                      \
	do {                                                                       \
		function<int>();                                                       \
		function<double>();                                                    \
		function<unit::tinteger>();                                            \
		function<unit::tfloat>();                                              \
	} while(0)

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
add()
{
	TRACE;

	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		const tquantity<INPUT, T> q1{1};
		const tquantity<INPUT, T> q2{2};
		const tquantity<RESULT, T> qr{3};

		BOOST_CHECK_EQUAL(q1 + q2, qr);
	}

	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		tquantity<INPUT, T> q1{1};
		q1 += tquantity<INPUT, T>{2};
		const tquantity<RESULT, T> qr{3};

		BOOST_CHECK_EQUAL(q1, qr);
	}

	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		tquantity<INPUT, T> q1{2};
		++q1;
		const tquantity<RESULT, T> qr{3};

		BOOST_CHECK_EQUAL(q1, qr);
	}
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
add()
{
	TRACE;

	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		const tquantity<INPUT, T> q1{1.125};
		const tquantity<INPUT, T> q2{1.5};
		const tquantity<RESULT, T> qr{2.625};

		BOOST_CHECK_EQUAL(q1 + q2, qr);
	}

	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		tquantity<INPUT, T> q1{1.125};
		q1 += tquantity<INPUT, T>{1.5};
		const tquantity<RESULT, T> qr{2.625};

		BOOST_CHECK_EQUAL(q1, qr);
	}
#if 0
	/* This version should fail to compile. */
	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		tquantity<INPUT, T> q1{2};
		++q1;
		const tquantity<RESULT, T> qr{3};

		BOOST_CHECK_EQUAL(q1, qr);
	}
#endif
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
subtract()
{
	TRACE;

	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		const tquantity<INPUT, T> q1{1};
		const tquantity<INPUT, T> q2{2};
		const tquantity<RESULT, T> qr{-1};

		BOOST_CHECK_EQUAL(q1 - q2, qr);
		BOOST_CHECK_EQUAL(-q1, qr);
		BOOST_CHECK_EQUAL(-(-q1), q1);
	}

	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		tquantity<INPUT, T> q1{1};
		q1 -= tquantity<INPUT, T>{2};
		const tquantity<RESULT, T> qr{-1};

		BOOST_CHECK_EQUAL(q1, qr);
	}
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
subtract()
{
	TRACE;

	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		const tquantity<INPUT, T> q1{1.125};
		const tquantity<INPUT, T> q2{1.5};
		const tquantity<RESULT, T> qr{-0.375};
		const tquantity<RESULT, T> neg{-1.125};

		BOOST_CHECK_EQUAL(q1 - q2, qr);
		BOOST_CHECK_EQUAL(-q1, neg);
		BOOST_CHECK_EQUAL(-(-q1), q1);
	}

	{
		using INPUT = tunit<1, 0, 0, 0, 0>;
		using RESULT = INPUT;

		tquantity<INPUT, T> q1{1.125};
		q1 -= tquantity<INPUT, T>{1.5};
		const tquantity<RESULT, T> qr{-0.375};

		BOOST_CHECK_EQUAL(q1, qr);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
multiply()
{
	TRACE;

	{
		using INPUT1 = tunit<1, 2, 4, 8, 16>;
		using INPUT2 = tunit<2, 4, 8, 16, 32>;
		using RESULT = tunit<3, 6, 12, 24, 48>;

		const tquantity<INPUT1, T> q1{-2};
		const tquantity<INPUT2, T> q2{4};
		const tquantity<RESULT, T> qr{-8};

		BOOST_CHECK_EQUAL(q1 * q2, qr);
	}

	{
		using INPUT = tunit<1, 2, 4, 8, 16>;
		using RESULT = INPUT;

		const tquantity<INPUT, T> q1{-2};
		const T q2{4};
		const tquantity<RESULT, T> qr{-8};

		BOOST_CHECK_EQUAL(q1 * q2, qr);
		BOOST_CHECK_EQUAL(q2 * q1, qr);
	}

	{
		using INPUT = tunit<1, 2, 4, 8, 16>;
		using RESULT = INPUT;

		tquantity<INPUT, T> q1{-2};
		q1 *= tquantity<NONE, T>{4};
		const tquantity<RESULT, T> qr{-8};

		BOOST_CHECK_EQUAL(q1, qr);
	}

	{
		using INPUT = tunit<1, 2, 4, 8, 16>;
		using RESULT = INPUT;

		tquantity<INPUT, T> q1{-2};
		q1 *= T{4};
		const tquantity<RESULT, T> qr{-8};

		BOOST_CHECK_EQUAL(q1, qr);
	}
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
multiply()
{
	TRACE;

	{
		using INPUT1 = tunit<1, 2, 4, 8, 16>;
		using INPUT2 = tunit<2, 4, 8, 16, 32>;
		using RESULT = tunit<3, 6, 12, 24, 48>;

		const tquantity<INPUT1, T> q1{2.5};
		const tquantity<INPUT2, T> q2{-1.5};
		const tquantity<RESULT, T> qr{-1.5 * 2.5};

		BOOST_CHECK_EQUAL(q1 * q2, qr);
	}

	{
		using INPUT = tunit<1, 2, 4, 8, 16>;
		using RESULT = INPUT;

		const tquantity<INPUT, T> q1{2.5};
		const T q2{-1.5};
		const tquantity<RESULT, T> qr{-1.5 * 2.5};

		BOOST_CHECK_EQUAL(q1 * q2, qr);
		BOOST_CHECK_EQUAL(q2 * q1, qr);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
divide()
{
	TRACE;

	{
		using INPUT = tunit<1, 2, 4, 8, 16>;
		using RESULT = INPUT;

		tquantity<INPUT, T> q1{-8};
		q1 /= 4;
		const tquantity<RESULT, T> qr{-2};

		BOOST_CHECK_EQUAL(q1, qr);
	}

	{
		using INPUT1 = tunit<3, 6, 12, 24, 48>;
		using INPUT2 = tunit<1, 2, 4, 8, 16>;
		using RESULT = tunit<2, 4, 8, 16, 32>;

		const tquantity<INPUT1, T> q1{-8};
		const tquantity<INPUT2, T> q2{4};
		const tquantity<RESULT, T> qr{-2};

		BOOST_CHECK_EQUAL(q1 / q2, qr);
	}

	{
		using INPUT = tunit<1, 2, 4, 8, 16>;
		using RESULT = INPUT;

		const tquantity<INPUT, T> q1{-8};
		const tquantity<RESULT, T> qr{-2};

		BOOST_CHECK_EQUAL(q1 / 4, qr);
	}
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
divide()
{
	TRACE;

	{
		using INPUT1 = tunit<3, 6, 12, 24, 48>;
		using INPUT2 = tunit<1, 2, 4, 8, 16>;
		using RESULT = tunit<2, 4, 8, 16, 32>;

		const tquantity<INPUT1, T> q1{-1.25 * 2.5};
		const tquantity<INPUT2, T> q2{-1.25};
		const tquantity<RESULT, T> qr{2.5};

		BOOST_CHECK_EQUAL(q1 / q2, qr);
	}
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
modulo()
{
	TRACE;

	using INPUT = tunit<3, 6, 12, 24, 48>;
	using RESULT = INPUT;

	const tquantity<INPUT, T> q1{10};
	const tquantity<INPUT, T> q2{3};
	const tquantity<RESULT, T> qr{1};

	BOOST_CHECK_EQUAL(q1 % q2, qr);
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
modulo()
{
	TRACE;

	using INPUT = tunit<3, 6, 12, 24, 48>;
	using RESULT = INPUT;

	const tquantity<INPUT, T> q1{1.0};
	const tquantity<INPUT, T> q2{0.375};
	const tquantity<RESULT, T> qr{0.25};

	BOOST_CHECK_EQUAL(q1 % q2, qr);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
sqrt()
{
	TRACE;

	using INPUT = tunit<2, 4, 8, 16, 32>;
	using RESULT = tunit<1, 2, 4, 8, 16>;

	const tquantity<INPUT, T> q1{9};
	const tquantity<RESULT, T> qr{3};

	BOOST_CHECK_EQUAL(sqrt(q1), qr);
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
sqrt()
{
	TRACE;

	using INPUT = tunit<2, 4, 8, 16, 32>;
	using RESULT = tunit<1, 2, 4, 8, 16>;

	const tquantity<INPUT, T> q1{1.5625};
	const tquantity<RESULT, T> qr{1.25};

	BOOST_CHECK_EQUAL(sqrt(q1), qr);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent == 0>::type
abs()
{
	TRACE;

	using INPUT = tunit<2, 4, 8, 16, 32>;
	using RESULT = INPUT;

	const tquantity<INPUT, T> pos{42};
	const tquantity<RESULT, T> neg{-42};

	BOOST_CHECK_EQUAL(abs(pos), pos);
	BOOST_CHECK_EQUAL(abs(neg), pos);
}

template <class T>
static typename std::enable_if<std::numeric_limits<T>::min_exponent != 0>::type
abs()
{
	TRACE;

	using INPUT = tunit<2, 4, 8, 16, 32>;
	using RESULT = INPUT;

	const tquantity<INPUT, T> pos{3.141};
	const tquantity<RESULT, T> neg{-3.141};

	BOOST_CHECK_EQUAL(abs(pos), pos);
	BOOST_CHECK_EQUAL(abs(neg), pos);
}

/***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****/

/**
 * @todo Add test for mixing the types.
 *
 * Some functions use @c std::common_type to determine its result.
 */
BOOST_AUTO_TEST_CASE(test_modules_unit_arithmetic)
{
	TRACE;

	EXECUTE(add);
	EXECUTE(subtract);
	EXECUTE(multiply);
	EXECUTE(divide);
	EXECUTE(modulo);
	EXECUTE(sqrt);
	EXECUTE(abs);
}
