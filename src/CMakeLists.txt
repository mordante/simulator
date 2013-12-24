########### Common include paths. ###############

### external includes
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

### Own directory
include_directories(${PROJECT_SOURCE_DIR}/src/)

### For the generated files
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)


########### Common library paths. ###############

### External libraries
link_directories(${Boost_LIBRARY_DIRS})


########### Libraries. ###############

include(lib/exception/CMakeLists.txt)


########### Modules. ###############

include(modules/celestial/CMakeLists.txt)
include(modules/logger/CMakeLists.txt)
include(modules/geometry/CMakeLists.txt)
include(modules/grid/CMakeLists.txt)
include(modules/simulation/CMakeLists.txt)
include(modules/unit/CMakeLists.txt)


########### Programs. ###############

### Simulator

add_executable(simulator
	simulator/simulator.cpp
	simulator/options.cpp
)

target_link_libraries(simulator
	simulation
)

###Unit test

if(MAKE_UNIT_TESTS)

	add_executable(unit_test
		unit_test/exception.cpp
		unit_test/lib/utility/concatenate.cpp
		unit_test/modules/celestial/moon.cpp
		unit_test/modules/celestial/planet.cpp
		unit_test/modules/celestial/sun.cpp
		unit_test/modules/geometry/coordinate.cpp # For both cartesian and polar.
		unit_test/modules/geometry/orbit.cpp
		unit_test/modules/grid/line.cpp
		unit_test/modules/grid/circle.cpp
		unit_test/modules/grid/point.cpp
		unit_test/modules/grid/sphere.cpp
		unit_test/modules/logger/logger.cpp
		unit_test/modules/logger/module.cpp
		unit_test/modules/simulation/moon.cpp
		unit_test/modules/simulation/simulator.cpp
		unit_test/modules/simulation/sun.cpp
		unit_test/modules/unit/quantity.cpp
		unit_test/modules/unit/quantity/arithmetic.cpp
		unit_test/modules/unit/quantity/comparison.cpp
		unit_test/modules/unit/quantity/stream.cpp
		unit_test/modules/unit/quantity/trigonometry.cpp
		unit_test/unit_test.cpp
	)

	set_target_properties(unit_test
		PROPERTIES
		COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	)

	target_link_libraries(unit_test
		celestial
		geometry
		grid
		logger
		simulation
		unit
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	)

endif()
