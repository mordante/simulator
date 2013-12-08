cmake_minimum_required(VERSION 2.8.9)
#set(CMAKE_VERBOSE_MAKEFILE on)
project(simulator)

include(CheckCXXCompilerFlag)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost
	1.55
	REQUIRED
	COMPONENTS
		unit_test_framework)


############ Compiler flags. ###########

# This macro checks whether a compiler supports a compiler flag.
#
# If the flag is supported the flag will be added to the target compiler flags.
# GCC seems to be quite happy to accept flags it does not support when there is
# a `no' in it e.g. -Wno-not_supported_flag but will fail to compile with
# -Wnot_supported_flag. For that case all not-named parameters will be added to
# the target instead.
#
# param target                    The variable to add the compiler flag to.
# param flag                      The compiler flag to test.
# param variable                  The test macro needs a variable to store the
#                                 result of the test, this paramter holds that
#                                 variable.
# param ...                       If this variable is set it will be added to
#                                 target instead of flag when the compiler
#                                 supports flag.
macro(check_compiler_has_flag target flag variable)
	check_cxx_compiler_flag(${flag} ${variable})
	if(${variable})
		if(${ARGC} GREATER 3)
			set(${target} "${${target}} ${ARGN}")
		else(${ARGC} GREATER 3)
			set(${target} "${${target}} ${flag}")
		endif(${ARGC} GREATER 3)
	endif(${variable})
endmacro(check_compiler_has_flag)

if(NOT DEFINED CXX_FLAGS_USER)

	message(STATUS "Environment compiler flags set to »${CXX_FLAGS_USER}«")
	set(CXX_FLAGS_USER
		"$ENV{CXXFLAGS}"
		CACHE
		STRING
		"The CXXFLAGS environment variable used for the initial generation."
		FORCE
	)

endif(NOT DEFINED CXX_FLAGS_USER)

set(CXX_FLAGS_PROJECT "-std=c++1y -W -Wall -Wextra")

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Winit-self"
	HAS_COMPILER_FLAG_WINIT_SELF
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wlogical-op"
	HAS_COMPILER_FLAG_WLOGICAL_OP
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wmissing-declarations"
	HAS_COMPILER_FLAG_WMISSING_DECLARATIONS
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wredundant-decls"
	HAS_COMPILER_FLAG_WREDUNDANT_DECLS
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wctor-dtor-privacy"
	HAS_COMPILER_FLAG_WCTOR_DTOR_PRIVACY
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wnon-virtual-dtor"
	HAS_COMPILER_FLAG_WNON_VIRTUAL_DTOR
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Woverloaded-virtual"
	HAS_COMPILER_FLAG_WNON_VIRTUAL_DTOR
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wdouble-promotion"
	HAS_COMPILER_FLAG_WDOUBLE_PROMOTION
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wmismatched-tags"
	HAS_COMPILER_FLAG_WMISMATCHED_TAGS
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wuseless-cast"
	HAS_COMPILER_FLAG_WUSELESS_CAST
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wnoexcept"
	HAS_COMPILER_FLAG_WNOEXCEPT
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wdocumentation"
	HAS_COMPILER_FLAG_WDOCUMENTATION
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-pedantic"
	HAS_COMPILER_FLAG_PEDANTIC
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wformat-security"
	HAS_COMPILER_FLAG_WFORMAT_SECURITY
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wformat=2"
	HAS_COMPILER_FLAG_WFORMAT
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wmissing-format-attribute"
	HAS_COMPILER_FLAG_WMISSING_FORMAT_ATTRIBUTE
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wshadow"
	HAS_COMPILER_FLAG_WSHADOW
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Weffc++"
	HAS_COMPILER_FLAG_WEFFCPP
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wconversion"
	HAS_COMPILER_FLAG_WCONVERSION
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Weverything"
	HAS_COMPILER_FLAG_WEVERYTHING
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wc++98-compat"
	HAS_COMPILER_FLAG_WCPP98_COMPAT
	"-Wno-c++98-compat"
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wc++98-compat-pedantic"
	HAS_COMPILER_FLAG_WCPP98_COMPAT_PEDANTIC
	"-Wno-c++98-compat-pedantic"
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wfloat-equal"
	HAS_COMPILER_FLAG_WFLOAT_EQUAL
	"-Wno-float-equal"
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wdocumentation-unknown-command"
	HAS_COMPILER_FLAG_WDOCUMENTATION_UNKNOWN_COMMAND
	"-Wno-documentation-unknown-command"
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wglobal-constructors"
	HAS_COMPILER_FLAG_WGLOBAL_CONSTRUCTORS
	"-Wno-global-constructors"
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wexit-time-destructors"
	HAS_COMPILER_FLAG_WEXIT_TIME_DESTRUCTORS
	"-Wno-exit-time-destructors"
)

check_compiler_has_flag(
	CXX_FLAGS_PROJECT
	"-Wpadded"
	HAS_COMPILER_FLAG_WPADDED
	"-Wno-padded"
)


############ Build options. ###########

option(MAKE_UNIT_TESTS "Make the unit tests for the libraries and modules" OFF)
option(ENABLE_STRICT_COMPILATION "Enables the strict compilation of the code" OFF)


############ Process options. ###########

if(ENABLE_STRICT_COMPILATION)
	set(CXX_FLAGS_PROJECT "${CXX_FLAGS_PROJECT} -Werror ${CXX_FLAGS_USER}")
else()
	set(CXX_FLAGS_PROJECT "${CXX_FLAGS_PROJECT} ${CXX_FLAGS_USER}")
endif()

if(NOT "${CMAKE_CXX_FLAGS}" STREQUAL "${CXX_FLAGS_PROJECT}")
	message(STATUS "CMake compiler flags set to »${CXX_FLAGS_PROJECT}«")
	set(CMAKE_CXX_FLAGS
		"${CXX_FLAGS_PROJECT}"
		CACHE
		STRING
		"Global flags used by the CXX compiler during all builds."
		FORCE
	)
endif()


############ Add subdirectories. ###########

add_subdirectory(src)
