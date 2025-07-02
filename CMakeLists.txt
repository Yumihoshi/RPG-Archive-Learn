cmake_minimum_required(VERSION 3.28)
project(RPG CXX)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows;${CMAKE_PREFIX_PATH}")
find_package(nlohmann_json REQUIRED)

find_package(nlohmann_json CONFIG REQUIRED)
add_executable(RPG main.cpp src/Pokemon.cpp src/Equipment.cpp src/User.cpp src/Game.cpp)
target_link_libraries(RPG PRIVATE nlohmann_json::nlohmann_json)
