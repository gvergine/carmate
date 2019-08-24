include(syncer.cmake)

add_library(syncer ${SYNCER_SOURCES})

target_include_directories(syncer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(syncer 
	infrastructure
)