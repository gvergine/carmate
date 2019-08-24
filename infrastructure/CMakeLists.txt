project(infrastructure VERSION 0.1 LANGUAGES C)

include(GNUInstallDirs)

find_package(Threads REQUIRED)

add_library(infrastructure
    src/queue.c
)

target_include_directories(infrastructure PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
    
target_link_libraries (infrastructure ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS infrastructure EXPORT InfrastructureConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT InfrastructureConfig DESTINATION share/infrastructure/cmake)
export(TARGETS infrastructure FILE InfrastructureConfig.cmake)


