cmake_minimum_required(VERSION 3.28)

project(RPG_Archive_Learn)

set(CMAKE_CXX_STANDARD 17)

# Integrate vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE SOURCRES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_subdirectory(src)
