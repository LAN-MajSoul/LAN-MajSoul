cmake_minimum_required(VERSION 3.11)
project(LAN-MajSoul-Client VERSION 0.1.0 LANGUAGES C CXX)
project(LAN-MajSoul-Server VERSION 0.1.0 LANGUAGES C CXX)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/network/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(./extern/network)
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
