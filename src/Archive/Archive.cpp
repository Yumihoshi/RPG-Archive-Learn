/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/1 下午2:10
* @version: 1.0
* @description: 
*******************************************************************************/
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <string>
#include <ctime>
#include <chrono>
#include <vector>
#include "../../include/Archive/Archive.h"
#include "../../include/Managers/PokeManager.h"
#include "../../include/Managers/EquipManager.h"


namespace fs = std::filesystem;

// TODO: 根据用户更改
const std::string Archive::ARCHIVE_FILE_PRE_PATH = "../data/archives/";

#include <fstream>
#include <sstream>
#include <unordered_map>

struct PokeData
{
    int id;
    std::string name;
    int eleType;
    int campType;
    int maxHp;
    int maxMp;
    int damage;
    float fleeRate;
    float critRate;
    int curExp;
    int maxExp;
    int curLevel;
    int maxLevel;
    int decorationId;
    int armorId;
};

// 构造函数
Archive::Archive(unsigned int id, const std::shared_ptr<UserModel> &user)
{
    if (!CheckIdValid(id))
        throw std::out_of_range("存档ID必须在1-3的闭区间！");
    _id = id;
    _user = user;
}

// 检查id是否在1-3的闭区间
bool Archive::CheckIdValid(unsigned int id)
{
    return id >= 1 && id <= 3;
}

// 保存存档
void Archive::Save()
{
    SetSaveTimeNow();

    std::ofstream archiveFile(GetPokeArchivePath(), std::ios::trunc);
    std::ofstream equipFile(GetEquipArchivePath(), std::ios::trunc);
    auto &pkm = PokeManager::GetInstance();
    auto &eqm = EquipManager::GetInstance();
    auto &pokes = pkm.GetAllPokes();
    auto &equips = eqm.GetAllEquips();

    // 保存宝可梦
    if (archiveFile.is_open())
    {
        // 写入存档数据
        archiveFile << "ArchiveID:" << _id << std::endl;
        archiveFile << "SaveTime:" << _saveTime << std::endl << std::endl;
        for (const auto &p: pokes)
        {
            for (const auto &poke: p.second)
            {
                archiveFile << "PokeID:" << poke->GetId() << std::endl;
                archiveFile << "Name:" << poke->GetName() << std::endl;
                archiveFile << "EleType:" << (int) (poke->GetElement())
                            << std::endl;
                archiveFile << "CampType:" << (int) (poke->GetCamp())
                            << std::endl;
                archiveFile << "MaxHp:" << poke->GetMaxHp() << std::endl;
                archiveFile << "MaxMp:" << poke->GetMaxMp() << std::endl;
                archiveFile << "Damage:" << poke->GetDamage() << std::endl;
                archiveFile << "FleeRate:" << poke->GetFleeRate() << std::endl;
                archiveFile << "CritRate:" << poke->GetCritRate() << std::endl;
                archiveFile << "CurExp:" << poke->GetCurExp() << std::endl;
                archiveFile << "MaxExp:" << poke->GetMaxExp() << std::endl;
                archiveFile << "CurLevel:" << poke->GetCurLevel() << std::endl;
                archiveFile << "MaxLevel:" << poke->GetMaxLevel() << std::endl;
                archiveFile << "DecorationID:" << poke->GetDecoration()->Id
                            << std::endl;
                archiveFile << "ArmorID:" << poke->GetArmor()->Id << std::endl;
                archiveFile << std::endl;
            }
        }
        archiveFile.close();
    }
    else
        std::cerr << "无法打开存档文件：" << GetPokeArchivePath() << std::endl;

    // 保存装备
    if (equipFile.is_open())
    {
        // 写入存档数据
        equipFile << "ArchiveID:" << _id << std::endl;
        equipFile << "SaveTime:" << _saveTime << std::endl << std::endl;
        for (const auto &e: equips)
        {
            for (const auto &equip: e.second)
            {
                equipFile << "EquipID:" << equip->Id << std::endl;
                equipFile << "Name:" << equip->Name << std::endl;
                equipFile << "Type:" << (int) (equip->EqType) << std::endl;
                switch (equip->EqType)
                {
                    case EquipType::Decoration:
                    {
                        auto dec = std::dynamic_pointer_cast<Decoration>(equip);
                        equipFile << "AttackBonus:" << dec->AttackBonus
                                  << std::endl;
                        equipFile << "MaxMpBonus:" << dec->MaxMpBonus
                                  << std::endl;
                        equipFile << "CritRateBonus:" << dec->CritRateBonus
                                  << std::endl;
                        equipFile << "FleeRateBonus:" << dec->FleeRateBonus
                                  << std::endl;
                        equipFile << "OwnerID:" << dec->Owner->GetId()
                                  << std::endl;
                        equipFile << std::endl;
                        break;
                    }
                    case EquipType::Armor:
                    {
                        auto arm = std::dynamic_pointer_cast<Armor>(equip);
                        equipFile << "MaxHpBonus:" << arm->MaxHpBonus
                                  << std::endl;
                        equipFile << "FleeRateBonus:" << arm->FleeRateBonus
                                  << std::endl;
                        equipFile << "OwnerID:" << arm->Owner->GetId()
                                  << std::endl;
                        equipFile << std::endl;
                        break;
                    }
                }
            }
        }
        equipFile.close();
    }
    else
        std::cerr << "无法打开存档文件：" << GetEquipArchivePath() << std::endl;

}

// 读取存档
void Archive::Load()
{
    // 打开宝可梦和装备存档文件
    std::ifstream archiveFile(GetPokeArchivePath());
    std::ifstream equipFile(GetEquipArchivePath());
    auto &pkm = PokeManager::GetInstance();
    auto &eqm = EquipManager::GetInstance();
    pkm.ClearAllPokes();
    eqm.ClearAllEquips();

    if (!archiveFile.is_open())
    {
        std::cerr << "无法打开存档文件：" << GetPokeArchivePath() << std::endl;
        return;
    }
    // 载入宝可梦
    std::string line;
    std::vector<PokeData> pokeDataList;

    // 读取前两行头部信息
    std::getline(archiveFile, line);
    if (line.find("ArchiveID:") != std::string::npos)
        _id = std::stoi(line.substr(line.find(":") + 1));
    std::getline(archiveFile, line);
    if (line.find("SaveTime:") != std::string::npos)
        _saveTime = line.substr(line.find(":") + 1);
    std::getline(archiveFile, line); // 跳过空行
    // 读取宝可梦数据
    PokeData curPokeData;
    bool inPokeDataBlock = false;
    while (std::getline(archiveFile, line))
    {
        // 遇到空行表示一个宝可梦数据块结束
        if (line.empty())
        {
            if (inPokeDataBlock)
            {
                pokeDataList.push_back(curPokeData);
                curPokeData = PokeData(); // 重置数据
                inPokeDataBlock = false;
            }
            continue;
        }
        // 解析数据
        inPokeDataBlock = true;
        size_t colonPos = line.find(":");
        if (colonPos == std::string::npos) continue;

        std::string key = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 1);

        if (key == "PokeID") curPokeData.id = std::stoi(value);
        else if (key == "Name") curPokeData.name = value;
        else if (key == "EleType") curPokeData.eleType = std::stoi(value);
        else if (key == "CampType") curPokeData.campType = std::stoi(value);
        else if (key == "MaxHp") curPokeData.maxHp = std::stoi(value);
        else if (key == "MaxMp") curPokeData.maxMp = std::stoi(value);
        else if (key == "Damage") curPokeData.damage = std::stoi(value);
        else if (key == "FleeRate") curPokeData.fleeRate = std::stof(value);
        else if (key == "CritRate") curPokeData.critRate = std::stof(value);
        else if (key == "CurExp") curPokeData.curExp = std::stoi(value);
        else if (key == "MaxExp") curPokeData.maxExp = std::stoi(value);
        else if (key == "CurLevel") curPokeData.curLevel = std::stoi(value);
        else if (key == "MaxLevel") curPokeData.maxLevel = std::stoi(value);
        else if (key == "DecorationID")
            curPokeData.decorationId = std::stoi(value);
        else if (key == "ArmorID") curPokeData.armorId = std::stoi(value);
    }

    // 处理最后一个块（如果文件末尾没有空行）
    if (inPokeDataBlock)
        pokeDataList.push_back(curPokeData);

    // 宝可梦管理器加载数据
    for (const auto &data: pokeDataList)
    {
        auto poke = std::make_shared<BasePokeModel>(
                data.id,
                data.name,
                static_cast<ElementType>(data.eleType),
                static_cast<CampType>(data.campType),
                data.maxHp,
                data.maxMp,
                data.damage,
                data.fleeRate,
                data.critRate
        );
        poke->SetCurExp(data.curExp);
        poke->SetMaxExp(data.maxExp);
        poke->SetCurLevel(data.curLevel);
        pkm.AddPoke(poke); // 添加到管理器
    }

    // 载入装备（新增装备解析逻辑）
    std::vector<std::shared_ptr<Equip>> equipDataList;
    if (equipFile.is_open())
    {
        std::string line;
        std::shared_ptr<Equip> curEquip;

        while (std::getline(equipFile, line))
        {
            if (line.empty()) continue;

            size_t colonPos = line.find(':');
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);

            if (key == "EquipID")
            {
                curEquip = std::make_shared<Equip>();
                curEquip->Id = std::stoi(value);
            }
            else if (key == "Type")
            {
                auto type = static_cast<EquipType>(std::stoi(value));
                if (type == EquipType::Decoration)
                {
                    curEquip = std::make_shared<Decoration>();
                }
                else
                {
                    curEquip = std::make_shared<Armor>();
                }
            }
                // 解析装备属性
            else if (key == "AttackBonus")
            {
                auto dec = std::dynamic_pointer_cast<Decoration>(curEquip);
                if (dec) dec->AttackBonus = std::stoi(value);
            }
            else if (key == "OwnerID")
            {
                auto owner = pkm.GetPokeById(std::stoi(value));
                if (auto dec = std::dynamic_pointer_cast<Decoration>(curEquip))
                {
                    dec->Owner = owner;
                }
                else if (auto arm = std::dynamic_pointer_cast<Armor>(curEquip))
                {
                    arm->Owner = owner;
                }
            }
            // ... 其他属性解析 ...
        }
        eqm.AddEquip(curEquip); // 添加到装备管理器
    }
}

void Archive::InitNewUserArchive(const std::shared_ptr<UserModel> &user)
{
    InitNewUserArchiveFolder(user);
    for (int i = 1; i <= 3; ++i)
    {
        Archive archive(i, user);
        archive.Save();
    }
}

void Archive::InitNewUserArchiveFolder(const std::shared_ptr<UserModel> &user)
{
    std::string userid = std::to_string(user->GetId());
    fs::path archiveFolder =
            ARCHIVE_FILE_PRE_PATH + userid;
    // 递归创建目录（含父目录）
    if (!fs::exists(archiveFolder))
    {
        fs::create_directories(archiveFolder);  // 自动创建所有缺失的目录层级
    }
}

// 设置存档保存时间
void Archive::SetSaveTimeNow()
{
    auto now = std::chrono::system_clock::now(); // 高精度时间点
    time_t now_c = std::chrono::system_clock::to_time_t(now); // 转 time_t
    struct tm timeinfo{};
    localtime_s(&timeinfo, &now_c); // 转为本地时间

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%F %T",
             &timeinfo); // %F=%Y-%m-%d, %T=%H:%M:%S
    _saveTime = buffer;
}

fs::path Archive::GetArchiveFolder() const
{
    std::string userId = std::to_string(_user->GetId());
    fs::path archiveFolder = ARCHIVE_FILE_PRE_PATH + userId;
    return archiveFolder;
}

fs::path Archive::GetPokeArchivePath() const
{
    return GetArchiveFolder() /
           ("archive_poke_" + std::to_string(_id) + ".txt");
}

fs::path Archive::GetEquipArchivePath() const
{
    return GetArchiveFolder() /
           ("archive_equip_" + std::to_string(_id) + ".txt");
}
