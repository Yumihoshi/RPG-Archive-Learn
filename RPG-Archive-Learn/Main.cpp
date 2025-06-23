#include <iostream>
#include "Singleton.h"
#include "PokemonModel.h"
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
    PokemonModel c("muliao", ElementType::Fire, 100, 100, 1, CampType::Friend, 100, 20, 0.3, 0.3);
    c.Heal(-5);
    c.TakeDamage(-9);
    return 0;
}
