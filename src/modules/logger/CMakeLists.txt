### Logger

# The logger module acting as front-end for boost log.
#
# Status:
# - Code          Finished
# - Unit tests    Finished
# - Documentation Finished
#
# Todo:
# - Note entirely happy with the implementation of the log overloads. It would
#   be nice to have another look at them later.

add_library(logger STATIC
	modules/logger/logger.cpp
	modules/logger/module.cpp
	modules/logger/severity.cpp
	modules/logger/state.cpp
)

target_link_libraries(logger
	exception
	pthread
	${Boost_DATE_TIME_LIBRARY}
	${Boost_LOG_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_THREAD_LIBRARY}
)
