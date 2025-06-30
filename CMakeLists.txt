cmake_minimum_required(VERSION 3.28)
project(RPG_Archive_Learn)

set(CMAKE_CXX_STANDARD 17)

add_executable(RPG_Archive_Learn src/Main.cpp
        include/Base/Signal.h
        include/Managers/DialogueManager.h
        include/Managers/EquipManager.h
        include/Managers/GameManager.h
        include/Managers/UIManager.h
        src/Common/Common.cpp
        src/Common/Signal.cpp
        src/Equipment/Armor.cpp
        src/Equipment/BaseEquipment.cpp
        src/Equipment/Decoration.cpp
        src/Managers/DialogueManager.cpp
        src/Managers/EquipManager.cpp
        src/Managers/GameManager.cpp
        src/Managers/LogManager.cpp
        src/Managers/PokeManager.cpp
        src/Managers/UIManager.cpp
        src/MVC/Controllers/BasePokeController.cpp
        src/MVC/Controllers/FirePokeController.cpp
        src/MVC/Controllers/FlyPokeController.cpp
        src/MVC/Controllers/GhostPokeController.cpp
        src/MVC/Controllers/GrassPokeController.cpp
        src/MVC/Controllers/IcePokeController.cpp
        src/MVC/Models/BasePokeModel.cpp
        src/MVC/Models/FirePokeModel.cpp
        src/MVC/Models/FlyPokeModel.cpp
        src/MVC/Models/GhostPokeModel.cpp
        src/MVC/Models/GrassPokeModel.cpp
        src/MVC/Models/IcePokeModel.cpp
        src/MVC/Views/BasePokeView.cpp
        src/MVC/Views/FirePokeView.cpp
        src/MVC/Views/FlyPokeView.cpp
        src/MVC/Views/GhostPokeView.cpp
        src/MVC/Views/GrassPokeView.cpp
        src/MVC/Views/IcePokeView.cpp
        src/Managers/UserManager.cpp
        include/Managers/UserManager.h
        src/User/UserModel.cpp
        include/User/UserModel.h
        src/Managers/FightManager.cpp
        include/Managers/FightManager.h
        include/Fsm/BaseState.h
        include/Fsm/BaseState.h
        include/Fsm/StateMachine.h
        src/Fight/PlayerFightState.cpp
        include/Fight/PlayerFightState.h
        src/Fight/EnemyFightState.cpp
        include/Fight/EnemyFightState.h
        src/Skills/Skills.cpp
        include/Skills/Skills.h
        src/Fight/DefaultFightState.cpp
        include/Fight/DefaultFightState.h
)
