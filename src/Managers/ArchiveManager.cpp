
#include "../../include/Managers/ArchiveManager.h"
#include "../../include/Managers/PokeManager.h"
#include "../../include/Managers/UserManager.h"
#include "../../include/MVC/Models/User/UserModel.h"
#include "../../include/MVC/Models/Poke/BasePokeModel.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include <filesystem>

namespace fs = std::filesystem;

void ArchiveManager::Save(const std::string& slotId)
{
    auto currentUser = UserManager::GetInstance().GetCurrentUser();
    if (!currentUser)
    {
        std::cerr << "No user logged in to save data." << std::endl;
        return;
    }

    json userData;
    userData["user"] = *currentUser;

    json pokeData = json::array();
    for (const auto& pair : PokeManager::GetInstance().GetAllPokes()) {
        for (const auto& poke : pair.second) {
            pokeData.push_back(*poke);
        }
    }

    json archive;
    archive["user_data"] = userData;
    archive["poke_data"] = pokeData;

    fs::path archivePath = "data/archives/" + slotId + ".json";
    std::ofstream ofs(archivePath);
    if (ofs.is_open())
    {
        ofs << std::setw(4) << archive << std::endl;
        std::cout << "Game saved successfully to " << archivePath << std::endl;
    }
    else
    {
        std::cerr << "Failed to open file for saving: " << archivePath << std::endl;
    }
}

std::pair<std::shared_ptr<UserModel>, std::map<ElementType, std::vector<std::shared_ptr<BasePokeModel>>>> ArchiveManager::Load(const std::string& slotId)
{
    fs::path archivePath = "data/archives/" + slotId + ".json";
    std::ifstream ifs(archivePath);
    if (!ifs.is_open())
    {
        std::cerr << "Failed to open file for loading: " << archivePath << std::endl;
        return {nullptr, {}};
    }

    json archive;
    ifs >> archive;

    auto user = std::make_shared<UserModel>(archive["user_data"]["user"].get<UserModel>());

    std::map<ElementType, std::vector<std::shared_ptr<BasePokeModel>>> loadedPokes;
    for (const auto& pokeJson : archive["poke_data"]) {
        auto poke = BasePokeModel::CreateFromJson(pokeJson);
        if (poke) {
            loadedPokes[poke->GetElement()].push_back(poke);
        }
    }

    std::cout << "Game loaded successfully from " << archivePath << std::endl;
    return {user, loadedPokes};
}
