#include <iostream>
#include "Singleton.h"
#include "LogManager.h"

using namespace std;

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
    LogManager::GetInstance().PrintTurnStart();
    cout << "回合数：" << GameManager::GetInstance().GetLevel() << endl;
    LogManager::GetInstance().PrintTurnEnd();
    return 0;
}
