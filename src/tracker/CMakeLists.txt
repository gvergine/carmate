include(tracker.cmake)

add_library(tracker ${TRACKER_SOURCES})

target_include_directories(tracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(tracker
	infrastructure
)
