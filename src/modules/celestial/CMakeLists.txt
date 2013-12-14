###
# The celestial library.
#
# This library contains all celestial elements and their container; the
# universe.
#
# Status:
# - Code          Busy
# - Unit tests    Busy
# - Documentation Busy
#
# Todo:
# - Finish the code.

add_library(celestial STATIC
	modules/celestial/sun.cpp
	modules/celestial/moon.cpp
	modules/celestial/universe.cpp
)

target_link_libraries(celestial
	geometry
	logger
	unit
)
