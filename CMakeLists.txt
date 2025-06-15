set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 4.0)
project(HelloWorld)

include(makehello.cmake)

if(WIN32)
  message(STATUS "Including windows_specific.cpp")
  set(EXTRA_SOURCES windows_specific.cpp)
else()
  message(STATUS "Including unix_specific.cpp")
  set(EXTRA_SOURCES unix_specific.cpp)
endif()

add_executable(HelloWorld main.cpp ${EXTRA_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/hello.h)

target_include_directories(HelloWorld PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set(MY_VARIABLE "Hello, CMake!")
message(STATUS "MY_VARIABLE is set to ${MY_VARIABLE}")

option(ENABLE_FEATURE "Enable a feature" ON)
if(ENABLE_FEATURE)
  message(STATUS "Feature is enabled")
else()
  message(STATUS "Feature is disabled")
endif()

find_package(Threads REQUIRED)
target_link_libraries(HelloWorld PRIVATE Threads::Threads)

add_library(MyLibrary STATIC my_library.cpp)
target_link_libraries(HelloWorld PRIVATE MyLibrary)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

target_link_libraries(HelloWorld PRIVATE gtest_main)

add_custom_command(
  TARGET HelloWorld POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo "Build succeeded!"
  COMMENT "Running post-build step"
)
