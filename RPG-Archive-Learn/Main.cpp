#include <iostream>
#include "Singleton.h"
#include "LogManager.h"

class GameManager : public Singleton<GameManager>
{
public:
    int GetLevel()
    {
        // ajlfkjdaslkjf
        return level;
    }

private:
    int level = 1;
    friend class Singleton<GameManager>;

    GameManager() = default;
};

int main()
{
    LogManager::GetInstance().PrintTurnStart();
    std::cout << "回合数：" << GameManager::GetInstance().GetLevel() << std::endl;
    LogManager::GetInstance().PrintTurnEnd();
    return 0;
}
