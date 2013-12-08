cmake_minimum_required(VERSION 2.8.9)
#set(CMAKE_VERBOSE_MAKEFILE on)
project(simulator)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost
	1.55
	REQUIRED
	COMPONENTS
		unit_test_framework)

############ Build options. ###########

option(MAKE_UNIT_TESTS "Make the unit tests for the libraries and modules" OFF)


############ Add subdirectories. ###########

add_subdirectory(src)
