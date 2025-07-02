#include <iostream>
#include <windows.h>
#include "../include/Singletons/Game.h"

int main() {
    SetConsoleOutputCP(65001);
    Game::GetInstance().run();
    return 0;
}
