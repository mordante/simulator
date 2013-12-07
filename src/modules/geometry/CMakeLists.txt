###
# The geometry library.
#
# This library allows several calculations in a coordinate system, some things
# are easier to calculate in a cartesian coordinate system other is a polar
# coordinate system. The code also allows to switch between the models.
#
# Status:
# - Code          Finished
# - Unit tests    Finished
# - Documentation Finished
#
# Todo:
# - Nothing

add_library(geometry STATIC
	modules/geometry/cartesian.cpp
	modules/geometry/orbit.cpp
	modules/geometry/polar.cpp
	modules/geometry/stream.cpp
)

target_link_libraries(geometry
	exception
	logger
)
