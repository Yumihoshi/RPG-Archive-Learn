/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午1:41
* @version: 1.0
* @description: 
*******************************************************************************/
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "../../../../include/Managers/PokeManager.h"
#include "../../../../include/MVC/Models/User/UserModel.h"

// TODO: 修复存档bug

UserModel::UserModel() : _userType(UserType::NormalPlayer)
{
    // 获取当前时间并转换为无符号整数作为 _id
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    _id = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
}

UserModel::UserModel(std::string username, std::string password, UserType type)
        : _username(std::move(username)),
          _password(std::move(password)),
          _userType(type)
{
    // 获取当前时间并转换为无符号整数作为 _id
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    _id = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
}

std::string UserModel::Encrypt(const std::string &password)
{
    std::string encrypted = password;
    for (char &c: encrypted)
    {
        c = (c + 7) % 128; // 简单的移位加密
    }
    return encrypted;
}

// Getter实现
unsigned int UserModel::GetId() const
{ return _id; }

std::string UserModel::GetUsername() const
{ return _username; }

UserType UserModel::GetUserType() const
{ return _userType; }

std::string UserModel::GetPassword() const
{ return _password; }

std::string UserModel::GetEncryptedPassword() const
{ return Encrypt(_password); }

// Setter实现
void UserModel::SetUsername(const std::string &username)
{ _username = username; }

void UserModel::SetPassword(const std::string &password)
{ _password = password; }

void UserModel::SetUserType(UserType type)
{ _userType = type; }


// 从文件加载用户数据
std::vector<UserModel> UserModel::LoadUsersFromFile(const std::string &filePath)
{
    std::vector<UserModel> users;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string username, password;
            unsigned int id; // 不再使用该变量
            int userTypeInt;
            if (iss >> id >> username >> password >> userTypeInt)
            {
                auto userType = static_cast<UserType>(userTypeInt);
                // 构造用户对象时自动生成 _id
                UserModel user(username, password, userType);
                users.push_back(user);
            }
        }
        file.close();
    }
    return users;
}

// 将用户数据保存到文件
void UserModel::SaveUsersToFile(const std::vector<UserModel> &users,
                                const std::string &filePath)
{
    std::ofstream file(filePath);
    if (file.is_open())
    {
        for (const auto &user: users)
        {
            file << user._id << " " << user._username << " " << user._password
                 << " " << static_cast<int>(user._userType) << "\n";
        }
        file.close();
    }
}

// 在SaveUsersToFile和LoadUsersFromFile中添加存档处理逻辑
const std::string UserModel::ARCHIVE_FILE_PREFIX = "../data/archives/";

// 保存存档
void UserModel::SaveArchive(int slot) {
    if (_userType == UserType::Admin) return;

    std::string filename = ARCHIVE_FILE_PREFIX + std::to_string(_id) + "_" + std::to_string(slot) + ".dat";
    std::ofstream file(filename);

    if (file.is_open()) {
        // 获取当前时间
        auto now = std::time(nullptr);
        _archives[slot].saveDate = std::put_time(std::localtime(&now), "%F %T");
        file << _archives[slot].saveDate << "\n";

        // 获取用户拥有的宝可梦
        auto& pokeManager = PokeManager::GetInstance();
        auto& allPokes = pokeManager.GetAllPokes();

    if (file.is_open()) {
        std::string saveDate;
        std::getline(file, saveDate);
        _archives[slot].saveDate = saveDate;

        auto& pokeManager = PokeManager::GetInstance();
        _archives[slot].pokeIds.clear();
        _archives[slot].pokeStates.clear();

        unsigned int pokeId;
        while (file >> pokeId) {
            _archives[slot].pokeIds.push_back(pokeId);
            std::string state;
            std::getline(file, state);
            state = state.substr(1); // 去掉开头的空格
            _archives[slot].pokeStates[pokeId] = state;

            if (auto poke = pokeManager.GetPokeById(pokeId)) {
                std::istringstream iss(state);
                int curHp, maxHp, curMp, maxMp, curExp, maxExp, curLevel, maxLevel, damage;
                float fleeRate, critRate;
                std::string decorationName, armorName;
                int attackBonus, maxMpBonus, maxHpBonus;
                float critRateBonus, fleeRateBonus;

                iss >> curHp >> maxHp >> curMp >> maxMp >> curExp >> maxExp >> curLevel >> maxLevel >> fleeRate >> critRate >> damage;

                poke->SetCurHp(curHp);
                poke->SetMaxHp(maxHp);
                poke->SetCurMp(curMp);
                poke->SetMaxMp(maxMp);
                poke->SetCurExp(curExp);
                poke->SetMaxExp(maxExp);
                poke->SetCurLevel(curLevel);
                poke->SetMaxLevel(maxLevel);
                poke->SetFleeRate(fleeRate);
                poke->SetCritRate(critRate);
                poke->SetDamage(damage);

                // 反序列化饰品
                iss >> decorationName;
                if (decorationName != "null") {
                    iss >> attackBonus >> maxMpBonus >> critRateBonus >> fleeRateBonus;
                    auto decoration = std::make_shared<Decoration>(decorationName, attackBonus, maxMpBonus, critRateBonus, fleeRateBonus);
                    poke->Equip(decoration);
                } else {
                    poke->Unequip(EquipType::Decoration);
                }

                // 反序列化防具
                iss >> armorName;
                if (armorName != "null") {
                    iss >> maxHpBonus >> fleeRateBonus;
                    auto armor = std::make_shared<Armor>(armorName, maxHpBonus, fleeRateBonus);
                    poke->Equip(armor);
                } else {
                    poke->Unequip(EquipType::Armor);
                }
            }
        }

        file.close();
    }
}

// 删除存档
void UserModel::DeleteArchive(int slot) {
    if (_userType == UserType::Admin) return;

    std::string filename = ARCHIVE_FILE_PREFIX + std::to_string(_id) + "_" + std::to_string(slot) + ".dat";
    std::remove(filename.c_str());
    _archives[slot] = {};
}

// 显示存档信息
void UserModel::ShowArchiveInfo() const {
    for (int i = 0; i < 3; ++i) {
        std::cout << "存档槽位 " << i << ":\n";
        std::cout << "保存日期: " << _archives[i].saveDate << "\n";
        std::cout << "宝可梦数量: " << _archives[i].pokeIds.size() << "\n\n";
    }
    std::string filename = ARCHIVE_FILE_PREFIX + std::to_string(_id) + "_" + std::to_string(slot) + ".dat";
// 加载存档
        _archives[slot].pokeIds.clear();
        _archives[slot].pokeStates.clear();

        for (const auto& [element, pokeList] : allPokes) {
            for (const auto& poke : pokeList) {
                // 假设每个用户有自己的宝可梦列表，这里简单处理
                _archives[slot].pokeIds.push_back(poke->GetId());
                // 序列化宝可梦状态
                std::ostringstream oss;
                oss << poke->GetCurHp() << " " << poke->GetMaxHp() << " "
                    << poke->GetCurMp() << " " << poke->GetMaxMp() << " "
                    << poke->GetCurExp() << " " << poke->GetMaxExp() << " "
                    << poke->GetCurLevel() << " " << poke->GetMaxLevel() << " "
                    << poke->GetFleeRate() << " " << poke->GetCritRate() << " "
                    << poke->GetDamage() << " ";

                // 序列化饰品
                if (auto decoration = poke->GetDecoration()) {
                    oss << decoration->Name << " "
                        << decoration->AttackBonus << " "
                        << decoration->MaxMpBonus << " "
                        << decoration->CritRateBonus << " "
                        << decoration->FleeRateBonus << " ";
                } else {
                    oss << "null ";
                }

                // 序列化防具
                if (auto armor = poke->GetArmor()) {
                    oss << armor->Name << " "
                        << armor->MaxHpBonus << " "
                        << armor->FleeRateBonus << " ";
                } else {
                    oss << "null ";
                }

                _archives[slot].pokeStates[poke->GetId()] = oss.str();
                file << poke->GetId() << " " << oss.str() << "\n";
            }
        }

        file.close();
    }
    // TODO:装备信息序列化...
}

void UserModel::LoadArchive(int slot) {
    if (_userType == UserType::Admin) return;

    std::string filename = ARCHIVE_FILE_PREFIX + std::to_string(_id) + "_" + std::to_string(slot);
    std::ifstream file(filename);
    // TODO:反序列化逻辑...
}
