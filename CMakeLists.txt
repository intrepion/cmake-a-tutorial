set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 4.0)
project(HelloWorld VERSION 1.0.0)

# add_subdirectory(src)
# add_subdirectory(lib)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    message(STATUS "Building on Windows")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    message(STATUS "Building on macOS")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "Building on Linux")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
        OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    message(STATUS "Using Clang")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Using MSVC")
else()
  message(STATUS "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

include(makehello.cmake)

if(WIN32)
  message(STATUS "Including windows_specific.cpp")
  set(EXTRA_SOURCES windows_specific.cpp)
else()
  message(STATUS "Including unix_specific.cpp")
  set(EXTRA_SOURCES unix_specific.cpp)
endif()

add_executable(HelloWorld main.cpp ${EXTRA_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/hello.h)
add_executable(HelloWorldTest test.cpp)

target_compile_definitions(HelloWorld PRIVATE
    $<$<CONFIG:Debug>:DEBUG_MODE>
)

target_compile_options(HelloWorld PRIVATE
    $<$<CONFIG:Debug>:-O0>
)

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

target_link_libraries(HelloWorldTest PRIVATE gtest_main)

add_custom_command(
  TARGET HelloWorld POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo "Build succeeded!"
  COMMENT "Running post-build step"
)

enable_testing()
add_test(NAME HelloWorldTest COMMAND HelloWorldTest)

install(TARGETS HelloWorld DESTINATION bin)

set(CPACK_PACKAGE_NAME "HelloWorld")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "A simple program packaged with CPack")

set(CPACK_PACKAGE_VENDOR "MyCompany")
set(CPACK_PACKAGE_CONTACT "support@mycompany.com")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION .)
install(FILES ${CMAKE_SOURCE_DIR}/README.md DESTINATION .)

set(CPACK_GENERATOR "DragNDrop;TGZ")
include(CPack)
