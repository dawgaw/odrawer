cmake_minimum_required(VERSION 3.2)

project(online-drawer)

add_subdirectory(libs/SFML)

include_directories(libs/bitsery/include)
include_directories(libs/SFML/include)

include_directories(include)


add_executable(odrawer
src/main.cpp
src/shapes/Circle.cpp
src/shapes/Line.cpp
src/shapes/Rectangle.cpp
src/shapes/LinesPath.cpp
src/tools/BaseTool.cpp
src/tools/LinesTool.cpp
src/tools/CircleTool.cpp
src/tools/RectangleTool.cpp
src/elements/Button.cpp

)

target_link_directories(odrawer PRIVATE libs/SFML/lib)
target_link_libraries(odrawer sfml-graphics sfml-window sfml-system sfml-network)
