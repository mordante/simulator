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

#include "modules/grid/line.hpp"
#include "modules/grid/stream.hpp"
#include "modules/grid/detail/basic.hpp"
#include "modules/grid/detail/template_multiplex.hpp"
#include "modules/grid/detail/template_lookup.hpp"
#include "modules/grid/detail/optimised.hpp"
#include "modules/grid/detail/vector.hpp"

#include <iostream>
#include <chrono>
#include <functional>

using namespace grid;

/*
 * This value determine the base number of repetitions.
 * It is choosen so the task is done in a few minutes on my system.
 *
 * The file speed.csv is taken with a value of 10'000'000 using -O2 and took
 * about 194 minutes.
 */
static constexpr int reps = 100'000;

static std::chrono::high_resolution_clock::duration
time(const int repetitions, const std::function<void()>& functor)
{
	auto start = std::chrono::high_resolution_clock::now();

	for(int i = 0; i < repetitions; ++i) {
		functor();
	}

	return std::chrono::high_resolution_clock::now() - start;
}

static void test(const int repetitions, tpoint begin, tpoint end)
{
	std::cerr << begin << '\t' << end << '\t' << repetitions << '\t'
			  << time(repetitions, [&]() { detail::line_basic(begin, end); })
						 .count() << '\t'
			  << time(repetitions, [&]() {
						  detail::line_template_multiplex(begin, end);
					  }).count() << '\t'
			  << time(repetitions, [&]() {
						  detail::line_template_lookup(begin, end);
					  }).count() << '\t'
			  << time(repetitions,
					  [&]() { detail::line_optimised(begin, end); }).count()
			  << '\t'
			  << time(repetitions, [&]() { detail::line_vector(begin, end); })
						 .count() << "\n";
}

int main()
{
	std::cerr << "Begin\tEnd\tRepetitions\tBasic\tMultiplex\tLookup\tOptimised"
				 "\tVector\n";

	for(int i = 1; i <= 10'000; i *= 10) {

		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 0 * i, 0 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 0 * i, 25 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 0 * i, 50 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 0 * i, 75 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 0 * i, 100 * i});

		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 25 * i, 0 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 25 * i, 25 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 25 * i, 50 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 25 * i, 75 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 25 * i, 100 * i});

		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 50 * i, 0 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 50 * i, 25 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 50 * i, 50 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 50 * i, 75 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 50 * i, 100 * i});

		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 75 * i, 0 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 75 * i, 25 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 75 * i, 50 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 75 * i, 75 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 75 * i, 100 * i});

		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 100 * i, 0 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 100 * i, 25 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 100 * i, 50 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 100 * i, 75 * i});
		test(reps / i, tpoint{0, 0, 0}, tpoint{100 * i, 100 * i, 100 * i});
	}
}
