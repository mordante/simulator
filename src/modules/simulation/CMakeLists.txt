###
# The simulation library.
#
# This library contains the definition of the simulation.
#
# Status:
# - Code          Busy
# - Unit tests    Busy
# - Documentation Busy
#
# Todo:
# - Finish the module.

add_library(simulation STATIC
	modules/simulation/detail/moon.cpp
	modules/simulation/detail/state.cpp
	modules/simulation/detail/sun.cpp
	modules/simulation/simulator.cpp
)

target_link_libraries(simulation
	celestial
)
