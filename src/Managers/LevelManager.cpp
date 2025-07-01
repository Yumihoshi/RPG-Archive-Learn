#include "../../include/Managers/LevelManager.h"

LevelManager::LevelManager() = default;

void LevelManager::Init()
{
    _levels.push_back({1, ElementType::Grass});
    _levels.push_back({2, ElementType::Fire});
    _levels.push_back({3, ElementType::Ice});
    _levels.push_back({4, ElementType::Fly});
    _levels.push_back({5, ElementType::Ghost});
    _levels.push_back({6, ElementType::None}); // Boss level
}

const Level* LevelManager::GetLevel(int levelNumber) const
{
    for (const auto& level : _levels)
    {
        if (level.levelNumber == levelNumber)
        {
            return &level;
        }
    }
    return nullptr;
}