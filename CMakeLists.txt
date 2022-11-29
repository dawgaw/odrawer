cmake_minimum_required(VERSION 3.2)

project(online-drawer)

set(SFML_BUILD_AUDIO FALSE)
set(BUILD_SHARED_LIBS FALSE)

add_subdirectory(libs/SFML)

include_directories(libs/bitsery/include)
include_directories(libs/SFML/include)
include_directories(libs/argh)


include_directories(include)


add_executable(odrawer
src/main.cpp

src/elements/Button.cpp

src/network/Client.cpp
src/network/Server.cpp

src/shapes/Circle.cpp
src/shapes/Line.cpp
src/shapes/Rectangle.cpp
src/shapes/LinesPath.cpp

src/tools/BaseTool.cpp
src/tools/LinesTool.cpp
src/tools/CircleTool.cpp
src/tools/RectangleTool.cpp

src/utils/SerializeUtils.cpp
)

target_precompile_headers(odrawer PUBLIC
include/elements/Button.hpp

include/network/Client.hpp
include/network/Server.hpp
include/network/NetworkInterface.hpp

include/shapes/BaseShape.hpp
include/shapes/Circle.hpp
include/shapes/Line.hpp
include/shapes/LinesPath.hpp
include/shapes/Rectangle.hpp

include/tools/BaseTool.hpp
include/tools/LinesTool.hpp
include/tools/CircleTool.hpp
include/tools/RectangleTool.hpp

include/utils/SerializableColor.hpp
include/utils/SerializableFloatVector.hpp
include/utils/SerializeUtils.hpp
)

target_link_directories(odrawer PRIVATE libs/SFML/lib)
target_link_libraries(odrawer sfml-graphics sfml-window sfml-network)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/resources
        COMMENT "Copying resources into binary directory")

add_dependencies(odrawer copy_resources)
