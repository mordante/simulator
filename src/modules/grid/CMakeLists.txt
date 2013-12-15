###
# The grid library.
#
# This library contains the code for a grid.
#
# Status:
# - Code          Finished
# - Unit tests    Finished
# - Documentation Finished

add_library(grid STATIC
	modules/grid/circle.cpp
	modules/grid/detail/basic.cpp
	modules/grid/detail/optimised.cpp
	modules/grid/detail/template_lookup.cpp
	modules/grid/detail/template_multiplex.cpp
	modules/grid/detail/vector.cpp
	modules/grid/line.cpp
	modules/grid/point.cpp
	modules/grid/sphere.cpp
	modules/grid/stream.cpp
)

target_link_libraries(grid
	logger
)

add_executable(speed_line_grid EXCLUDE_FROM_ALL
	modules/grid/detail/speed_line.cpp
)

target_link_libraries(speed_line_grid
	grid
)
