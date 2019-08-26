include(carmate.cmake)

add_executable(carmate ${CARMATE_SOURCES})

target_include_directories(carmate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(carmate 
	infrastructure
	gps_reader
	tracker
	clock
	syncer
)

install(TARGETS carmate DESTINATION ${CMAKE_INSTALL_BINDIR})
