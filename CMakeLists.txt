cmake_minimum_required(VERSION 3.0)
project(Skyblockers)
set (CMAKE_CXX_STANDARD 20)
add_executable(main src/main.cpp src/resource/resource_manager.cpp src/world/world.cpp src/util/util.cpp src/input/mouse.cpp src/input/keyboard.cpp src/world/chunk.cpp src/world/input_handler.cpp src/gui/gui_handler.cpp src/gui/gui_base.cpp src/gui/inventory.cpp src/resource/blocks.cpp lib/simdjson.cpp)
target_link_libraries(main sfml-graphics sfml-window sfml-system)
