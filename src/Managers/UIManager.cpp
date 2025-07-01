#include <iostream>
#include <string>
#include "../../include/Managers/UIManager.h"
#include "../../include/Managers/PokeManager.h"
#include "../../include/Managers/LogManager.h"
#include "../../include/Common/Common.h"
#include "../../include/MVC/Models/User/UserModel.h"
#include "../../include/Managers/UserManager.h"
#include "../../include/Managers/GameManager.h"

void UIManager::ShowArchiveMenu()
{
    while (true)
    {
        LogManager::PrintByChar("\n====== 存档管理 ======\n");
        LogManager::PrintByChar("1. 保存游戏\n");
        LogManager::PrintByChar("2. 添加宝可梦
");
        LogManager::PrintByChar("3. 删除宝可梦
");        LogManager::PrintByChar("4. 修改宝可梦
");        LogManager::PrintByChar("exit. 返回管理员菜单
");
        LogManager::PrintByChar("请输入指令：");

        std::string input;
        getline(std::cin, input);

        if (input == "1")
        {
            LogManager::PrintByChar("请输入存档ID (例如: 1, 2, 3): ");
            std::string slotId;
            getline(std::cin, slotId);
            ArchiveManager::GetInstance().Save(slotId);
        }
        else if (input == "2")
        {
            LogManager::PrintByChar("请选择要添加的宝可梦属性：\n");
            LogManager::PrintByChar("1. 火属性\n");
            LogManager::PrintByChar("2. 草属性\n");
            LogManager::PrintByChar("3. 冰属性\n");
            LogManager::PrintByChar("4. 飞行属性\n");
            LogManager::PrintByChar("5. 幽灵属性\n");
            std::string elementTypeInput;
            getline(std::cin, elementTypeInput);
            ElementType elementType = ElementType::None;
            if (elementTypeInput == "1") elementType = ElementType::Fire;
            else if (elementTypeInput == "2") elementType = ElementType::Grass;
            else if (elementTypeInput == "3") elementType = ElementType::Ice;
            else if (elementTypeInput == "4") elementType = ElementType::Fly;
            else if (elementTypeInput == "5") elementType = ElementType::Ghost;

            if (elementType != ElementType::None)
            {
                auto newPoke = PokeManager::GetInstance().CreatePoke(elementType, CampType::Friend);
                if (newPoke)
                {
                    // Load existing data, add new poke, then save
                    auto loadedData = ArchiveManager::GetInstance().Load(std::to_string(user->GetId()));
                    std::map<ElementType, std::vector<std::shared_ptr<BasePokeModel>>> pokesToSave;
                    if (loadedData.first) { // If there's existing data, use it
                        pokesToSave = loadedData.second;
                    }
                    pokesToSave[newPoke->GetElement()].push_back(newPoke);

                    json archive;
                    archive["user_data"]["user"] = *user;
                    json pokeData = json::array();
                    for (const auto& pair : pokesToSave) {
                        for (const auto& poke : pair.second) {
                            pokeData.push_back(*poke);
                        }
                    }
                    archive["poke_data"] = pokeData;

                    fs::path archivePath = "data/archives/" + std::to_string(user->GetId()) + ".json";
                    std::ofstream ofs(archivePath);
                    if (ofs.is_open())
                    {
                        ofs << std::setw(4) << archive << std::endl;
                        LogManager::PrintByChar("宝可梦添加成功！\n");
                    }
                    else
                    {
                        LogManager::PrintByChar("保存用户数据失败！\n", LogColor::Red);
                    }
                }
                else
                {
                    LogManager::PrintByChar("创建宝可梦失败！\n", LogColor::Red);
                }
            }
            else
            {
                LogManager::PrintByChar("无效的属性选择！\n", LogColor::Red);
            }
        }
        else if (input == "exit")
        {
            break;
        }
        else
        {
            LogManager::PrintByChar("无效指令！\n", LogColor::Red);
        }
    }
}

UIManager::UIManager() = default;

// 显示主菜单
void UIManager::ShowPokeManagerMainMenu()
{
    LogManager::PrintByChar("\n==============================\n");
    LogManager::PrintByChar("        空可梦管理系统       \n",
                            LogColor::Yellow);
    LogManager::PrintByChar("==============================\n"
                            "输入 p 查看所有空可梦\n"
                            "输入 f 进入战斗\n"
                            "输入 c 选择出战宝可梦\n"
                            "输入 s 存档\n"
                            "输入 exit 退出游戏\n"
                            "==============================\n");
}

// 显示所有空可梦
void UIManager::ShowAllPokesInfo()
{
    auto &pokeMap = PokeManager::GetInstance().GetAllPokes();
    LogManager::PrintByChar("\n当前所有空可梦：\n"
                            "ID\t名称\t\t防具\t\t饰品\n"
                            "----------------------------------------------");
    for (const auto &p: pokeMap)
    {
        for (const auto &poke: p.second)
        {
            LogManager::PrintByChar(std::to_string(poke->GetId()));
            LogManager::PrintByChar("\t" + poke->GetName());

            if (poke->GetArmor() == nullptr)
                LogManager::PrintByChar("无\n");
            else
                LogManager::PrintByChar(poke->GetArmor()->Name + "\n");
            if (poke->GetDecoration() == nullptr)
                LogManager::PrintByChar("无\n");
            else
                LogManager::PrintByChar(poke->GetDecoration()->Name + "\n");
        }
    }
}

void UIManager::ShowEquipManagerMenu(const std::shared_ptr<BasePokeModel> &model)
{
    while (true)
    {
        LogManager::PrintByChar("\n当前空可梦: " + model->GetName() + "\n");
        LogManager::PrintByChar("1. 防具: ");
        if (model->GetArmor() == nullptr)
            LogManager::PrintByChar("无\n");
        else
            LogManager::PrintByChar(model->GetArmor()->Name + "\n");

        LogManager::PrintByChar("2. 饰品: ");
        if (model->GetDecoration() == nullptr)
            LogManager::PrintByChar("无\n");
        else
            LogManager::PrintByChar(model->GetDecoration()->Name + "\n");

        LogManager::PrintByChar("-----------------------------\n"
                                "输入 a1 替换/装备防具\n"
                                "输入 a2 卸下防具\n"
                                "输入 d1 替换/装备饰品\n"
                                "输入 d2 卸下饰品\n"
                                "输入 exit 返回主菜单\n");

        std::string input;
        LogManager::PrintByChar("\n请输入指令:");
        getline(std::cin, input);
        input = Common::ToLower(input);

        if (input == "exit")
            break;
        else if (input == "a1")
        {
            LogManager::PrintByChar("请输入新的防具id: ");
            std::string equipIdInput;
            getline(std::cin, equipIdInput);
            try
            {
                int equipId = std::stoi(equipIdInput);
                EquipManager::GetInstance().Equip(model, equipId, EquipType::Armor);
                LogManager::PrintByChar("防具已装备！\n");
            }
            catch (const std::invalid_argument &e)
            {
                LogManager::PrintByChar("无效输入，请输入数字ID!\n", LogColor::Red);
            }
        }
        else if (input == "a2")
        {
            model->Unequip(EquipType::Armor);
            LogManager::PrintByChar("防具已卸下！\n");
        }
        else if (input == "d1")
        {
            LogManager::PrintByChar("请输入新的饰品id: ");
            std::string equipIdInput;
            getline(std::cin, equipIdInput);
            try
            {
                int equipId = std::stoi(equipIdInput);
                EquipManager::GetInstance().Equip(model, equipId, EquipType::Decoration);
                LogManager::PrintByChar("饰品已装备！\n");
            }
            catch (const std::invalid_argument &e)
            {
                LogManager::PrintByChar("无效输入，请输入数字ID!\n", LogColor::Red);
            }
        }
        else if (input == "d2")
        {
            model->Unequip(EquipType::Decoration);
            LogManager::PrintByChar("饰品已卸下！\n");
        }
        else
        {
            LogManager::PrintByChar("无效指令!\n", LogColor::Red);
        }
    }
}

// 根据当前用户权限类型，显示不同的菜单
void UIManager::ShowCurUserSpecificMenu()
{
    switch (UserManager::GetInstance().GetCurrentUser()->GetUserType())
    {
        case UserType::NormalPlayer:
            ShowPlayerMenu();
            break;
        case UserType::Admin:
            ShowAdminMenu();
            // TODO: 显示用户宝可梦及操作
            break;
    }
}

#include "../../include/Managers/LevelManager.h"
#include "../../include/Managers/FightManager.h"

// 新增玩家菜单
void UIManager::ShowPlayerMenu()
{
    while (true)
    {
        ShowPokeManagerMainMenu();
        std::string input;
        getline(std::cin, input);
        if (input == "p")
        {
            ShowAllPokesInfo();
            LogManager::PrintByChar("请输入要操作的宝可梦ID (输入exit返回):\n");
            std::string pokeIdInput;
            getline(std::cin, pokeIdInput);
            if (pokeIdInput == "exit")
            {
                continue;
            }
            try
            {
                int pokeId = std::stoi(pokeIdInput);
                auto poke = PokeManager::GetInstance().GetPokeById(pokeId);
                if (poke)
                {
                    ShowEquipManagerMenu(poke);
                }
                else
                {
                    LogManager::PrintByChar("无效的宝可梦ID!\n", LogColor::Red);
                }
            }
            catch (const std::invalid_argument &e)
            {
                LogManager::PrintByChar("无效输入，请输入数字ID!\n", LogColor::Red);
            }
        }
        else if (input == "f")
        {
            ShowLevelSelection();
        }
        else if (input == "c")
        {
            ShowSelectFightingPokeMenu();
        }
        else if (input == "s")
        {
            ShowArchiveMenu();
        }
        else if (input == "exit")
        {
            std::exit(0);
        }
        else
        {
            LogManager::PrintByChar("无效输入！\n");
            continue;
        }
    }
}

void UIManager::ShowSelectFightingPokeMenu()
{
    while (true)
    {
        ShowAllPokesInfo();
        LogManager::PrintByChar("\n请输入要设置为出战宝可梦的ID (输入exit返回):\n");
        std::string pokeIdInput;
        getline(std::cin, pokeIdInput);
        if (pokeIdInput == "exit")
        {
            break;
        }
        try
        {
            int pokeId = std::stoi(pokeIdInput);
            auto poke = PokeManager::GetInstance().GetPokeById(pokeId);
            if (poke)
            {
                FightManager::GetInstance().SetPlayerFightPoke(poke);
                LogManager::PrintByChar("已将 " + poke->GetName() + " 设置为出战宝可梦！\n");
                break;
            }
            else
            {
                LogManager::PrintByChar("无效的宝可梦ID!\n", LogColor::Red);
            }
        }
        catch (const std::invalid_argument &e)
        {
            LogManager::PrintByChar("无效输入，请输入数字ID!\n", LogColor::Red);
        }
    }
}
