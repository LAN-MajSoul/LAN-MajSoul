cmake_minimum_required(VERSION 3.11)
project(LAN-MajSoul-Client VERSION 0.1.0 LANGUAGES C CXX)
project(LAN-MajSoul-Server VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(./library/network)
if(NOT TARGET SimpleNetwork)
    # Stand-alone build
    find_package(SimpleNetwork REQUIRED)
endif()

include(CTest)
enable_testing()

include_directories(./include)

# aux_source_directory(. sources)
# aux_source_directory(./source/ sources)

file(GLOB sources CONFIGURE_DEPENDS ./source/*.cpp)

add_executable(LAN-MajSoul-Client client.cpp)
target_sources(LAN-MajSoul-Client PUBLIC ${sources})
target_link_libraries(LAN-MajSoul-Client PUBLIC SimpleNetwork)

add_executable(LAN-MajSoul-Server server.cpp)
target_sources(LAN-MajSoul-Server PUBLIC ${sources})
target_link_libraries(LAN-MajSoul-Server PUBLIC SimpleNetwork)

SET(EXECUTABLE_OUTPUT_PATH ..)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
