cmake_minimum_required(VERSION 3.16)
project(ZenithDB)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the installed spdlog package configuration file
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(Zenith 
  src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/internal/logger/logger.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/internal/values/value_object.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/internal/async/thread_pool.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/internal/networking/socket.cpp
)

target_include_directories(Zenith PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/internal)

target_link_libraries(Zenith PRIVATE spdlog::spdlog)
target_link_libraries(Zenith PRIVATE fmt::fmt)

# Testing
find_package(GTest CONFIG REQUIRED)

add_executable(ZenithTests 
  tests/safe_queue_test.cpp
  tests/thread_pool_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/internal/async/thread_pool.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/internal/networking/socket.cpp
)

target_include_directories(ZenithTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/internal)
target_link_libraries(ZenithTests PRIVATE GTest::gtest GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(ZenithTests)

