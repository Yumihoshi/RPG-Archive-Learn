#pragma once

#include "../Base/Singleton.h"
#include "../Common/Types.h"
#include <vector>
#include <memory>

class BasePokeModel;

struct Level
{
    int levelNumber;
    ElementType enemyType;
};

class LevelManager : public Singleton<LevelManager>
{
public:
    LevelManager();
    void Init();
    const std::vector<Level>& GetLevels() const { return _levels; }
    const Level* GetLevel(int levelNumber) const;

private:
    std::vector<Level> _levels;
    friend class Singleton<LevelManager>;
};