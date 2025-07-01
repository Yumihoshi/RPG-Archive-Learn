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
#include "../../include/Archive/Archive.h"


namespace fs = std::filesystem;

// TODO: 根据用户更改
const std::string Archive::ARCHIVE_FILE_PRE_PATH = "../data/archives/";

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

    // 构建用户专属存档路径
    std::string userId = std::to_string(_user->GetId());
    fs::path archiveFolder = ARCHIVE_FILE_PRE_PATH + userId;

    // 创建存档文件（如：archive_1.dat）
    for (int i = 1; i <= 3; ++i)
    {
        std::string fileName = "archive_" + std::to_string(i) + ".xlsx";
        fs::path filePath = archiveFolder / fileName;

        xlnt::workbook wb;
        auto pokeWs = wb.active_sheet();
        auto equipWs = wb.create_sheet(1);

        // 不存在，则初始化表头等数据
        if (!fs::exists(archiveFolder))
        {
            // 宝可梦数据表
            pokeWs.title("宝可梦数据");
            pokeWs.cell("A1").value("ID");
            pokeWs.cell("B1").value("名称");
            pokeWs.cell("C1").value("属性");
            pokeWs.cell("D1").value("阵营");
            pokeWs.cell("E1").value("最大血量");
            pokeWs.cell("F1").value("最大魔法值");
            pokeWs.cell("G1").value("每回合回复魔法值");

            pokeWs.cell("H1").value("防御力");
            pokeWs.cell("J1").value("闪避率");
            pokeWs.cell("K1").value("暴击率");
            pokeWs.cell("L1").value("攻击力（附带装备加成后）");

            pokeWs.cell("M1").value("当前经验值");
            pokeWs.cell("N1").value("最大经验值");
            pokeWs.cell("O1").value("当前等级");
            pokeWs.cell("P1").value("最大等级");

            pokeWs.cell("Q1").value("武器id");
            pokeWs.cell("R1").value("防具id");
            // 装备表
            equipWs.title("装备数据");

        }
        wb.save(filePath.string());
    }
}

// 读取存档
void Archive::Load()
{

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

