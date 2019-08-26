include(clock.cmake)

add_library(clock ${CLOCK_SOURCES})

target_include_directories(clock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(clock
	infrastructure
)
