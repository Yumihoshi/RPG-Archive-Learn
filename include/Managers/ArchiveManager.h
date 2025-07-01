
#pragma once

#include "../Base/Singleton.h"
#include <string>

class ArchiveManager : public Singleton<ArchiveManager>
{
public:
    void Save(const std::string& slotId);
    std::pair<std::shared_ptr<UserModel>, std::map<ElementType, std::vector<std::shared_ptr<BasePokeModel>>>> Load(const std::string& slotId);

private:
    friend class Singleton<ArchiveManager>;
    ArchiveManager() = default;
};
