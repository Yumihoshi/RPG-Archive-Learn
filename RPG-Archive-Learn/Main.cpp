#include <iostream>
#include "Singleton.h"

class GameManager : public Singleton<GameManager>
{
public:
    int GetLevel()
    {
        return level;
    }

private:
    int level = 1;
    friend class Singleton<GameManager>;

    GameManager() = default;
};

int main()
{
    std::cout << GameManager::GetInstance().GetLevel();
    return 0;
}
