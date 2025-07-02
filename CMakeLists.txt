cmake_minimum_required(VERSION 3.28)
project(RPG CXX)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows;${CMAKE_PREFIX_PATH}")
find_package(nlohmann_json REQUIRED)

find_package(nlohmann_json CONFIG REQUIRED)
add_executable(RPG src/main.cpp src/Poke/Pokemon.cpp src/Equip/Equipment.cpp src/User/User.cpp src/Singletons/Game.cpp
        src/Equip/Accessory.cpp
        include/Equip/Accessory.h
        src/Equip/Armor.cpp
        include/Equip/Armor.h
        src/Singletons/UI.cpp
        include/Singletons/UI.h
        include/Base/Singleton.h
        include/Base/Signal.h
        src/Singletons/UserManager.cpp
        include/Singletons/UserManager.h
        
        src/Singletons/PokemonFactory.cpp
        include/Singletons/PokemonFactory.h
        src/Poke/FirePokemon.cpp
        src/Poke/GrassPokemon.cpp
        src/Poke/IcePokemon.cpp
        src/Poke/FlyingPokemon.cpp
        src/Poke/GhostPokemon.cpp
        include/Common/Types.h)
target_link_libraries(RPG PRIVATE nlohmann_json::nlohmann_json)
