cmake_minimum_required(VERSION 3.0.0)
project(LAN-MajSoul-Client VERSION 0.1.0 LANGUAGES C CXX)
project(LAN-MajSoul-Server VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(./include)

# aux_source_directory(. sources)
# aux_source_directory(./source/ sources)

file(GLOB sources CONFIGURE_DEPENDS ./source/*.cpp)

add_executable(LAN-MajSoul-Client client.cpp)
target_sources(LAN-MajSoul-Client PUBLIC ${sources})

add_executable(LAN-MajSoul-Server server.cpp)
target_sources(LAN-MajSoul-Server PUBLIC ${sources})

SET(EXECUTABLE_OUTPUT_PATH ..)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
