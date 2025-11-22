cmake_minimum_required(VERSION 3.16)
project(ZenithDB)


# Find the installed spdlog package configuration file
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)


add_executable(Zenith src/main.cpp)

target_link_libraries(Zenith PRIVATE spdlog::spdlog)
target_link_libraries(Zenith PRIVATE fmt::fmt)
