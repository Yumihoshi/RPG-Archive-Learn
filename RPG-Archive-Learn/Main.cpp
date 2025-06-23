#include <iostream>
#include "Singleton.h"
#include "CharacterModel.h"
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
    CharacterModel c("muliao", ProfessionType::Warrior, 100, 100, 1);
    c.Heal(-5);
    return 0;
}
