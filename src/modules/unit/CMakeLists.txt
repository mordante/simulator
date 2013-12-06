###
# The unit library.
#
# This library contains the basic unit and quantity class these allow to
# calculate values retaining their units.
#
# Note most of the library is header only.
#
# Status:
# - Code          Finished
# - Unit tests    Finished
# - Documentation Finished
#
# Todo:
# - Nothing

add_library(unit STATIC
	modules/unit/quantity/stream.cpp
)

target_link_libraries(unit
	logger
)
