cmake_minimum_required(VERSION 3.2)

project(online-drawer)

add_subdirectory(libs/SFML)

include_directories(libs/bitsery/include)
include_directories(libs/SFML/include)

add_executable(odrawer main.cpp)

target_link_directories(odrawer PRIVATE libs/SFML/lib)
target_link_libraries(odrawer sfml-graphics sfml-window sfml-system)
