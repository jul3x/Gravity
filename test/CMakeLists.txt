#
# Created by jprolejko on 16.07.19.
#

cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Common build
include_directories(../include)

set(EXECUTABLE_NAME "GravityTest")
set(TEST_MAIN "gtest.cpp")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build_test")

file(GLOB_RECURSE TEST_SRC "src/*Test.cpp")
file(GLOB_RECURSE GRAVITY_MAIN_SRC "../src/*.cpp")
list(FILTER GRAVITY_MAIN_SRC EXCLUDE REGEX "main")

add_executable(${EXECUTABLE_NAME} ${TEST_MAIN} ${TEST_SRC} ${GRAVITY_MAIN_SRC})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)
target_link_libraries(${EXECUTABLE_NAME} gtest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})


