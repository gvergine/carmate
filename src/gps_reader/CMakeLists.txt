include(gps_reader.cmake)

add_library(gps_reader ${GPS_READER_SOURCES})
target_include_directories(gps_reader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(gps_reader 
	infrastructure
)