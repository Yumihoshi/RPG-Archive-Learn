#include "../../include/Managers/UIManager.h"
#include "../../include/Managers/PokeManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;
UIManager::UIManager() = default;
class PokemonGame {
private:
    auto & pokemon = PokeManager::GetInstance().GetAllPokes();

    // 初始化空可梦数据
    // TODO:huixing实现
    /*
    void initPokemon() {
        pokemons = {
            Pokemon(1, "皮卡丘"),
            Pokemon(2, "小火龙", "火焰铠甲", "力量护腕"),
            Pokemon(3, "杰尼龟", "水之护甲", ""),
            Pokemon(4, "妙蛙种子", "", "生命项链")
        };
    }*/
    void showMainMenu() {
        cout << "\n==============================" << endl;
        cout << "        空可梦管理系统       " << endl;
        cout << "==============================" << endl;
        cout << "输入 p 查看所有空可梦" << endl;
        cout << "输入 A 进入战斗" << endl;
        cout << "输入 s 存档" << endl;
        cout << "输入 exit 退出游戏" << endl;
        cout << "==============================" << endl;
    }

    // 显示所有空可梦
    void showAllPokes()
    {
        cout << "\n当前所有空可梦：" << endl;
        cout << "ID\t名称\t\t防具\t\t饰品" << endl;
        cout << "----------------------------------------------" << endl;
        for (const auto & p : pokemon)
        {
            cout << p.id << "\t" << p.name << "\t\t"
                 << (p.armor.empty() ? "无" : p.armor) << "\t\t"
                 << (p.accessory.empty() ? "无" : p.accessory) << endl;
        }
    }

    //TODO HUIXING
    /*
  // 根据ID查找空可梦
     Pokemon * findPokemonById(int id) {
    for (auto& p : pokemon) {
        if (p.id == id) {
            return &p;
        }
    }
    return nullptr;
}
  */
    //TODO huixing
    /*
    // 显示装备管理菜单
    void showEquipmentMenu(Pokemon* pokemon) {
        while (true) {
            cout << "\n当前空可梦: " << pokemon->name << endl;
            cout << "1. 防具: " << (pokemon->armor.empty() ? "无" : pokemon->armor) << endl;
            cout << "2. 饰品: " << (pokemon->decoration.empty() ? "无" : pokemon->decoration) << endl;
            cout << "-----------------------------" << endl;
            cout << "输入 A1 替换/装备防具" << endl;
            cout << "输入 A2 卸下防具" << endl;
            cout << "输入 D1 替换/装备饰品" << endl;
            cout << "输入 D2 卸下饰品" << endl;
            cout << "输入 exit 返回主菜单" << endl;

            string input;
            cout << "\n请输入指令: ";
            getline(cin, input);
            transform(input.begin(), input.end(), input.begin(), ::toupper);

            if (input == "EXIT") {
                break;
            }
            else if (input == "A1") {
                cout << "请输入新的防具名称: ";
                getline(cin, pokemon->armor);
                cout << "防具已装备!" << endl;
            }
            else if (input == "A2") {
                pokemon->armor = "";
                cout << "防具已卸下!" << endl;
            }
            else if (input == "D1") {
                cout << "请输入新的饰品名称: ";
                getline(cin, pokemon->decoration);
                cout << "饰品已装备!" << endl;
            }
            else if (input == "D2") {
                pokemon->accessory = "";
                cout << "饰品已卸下!" << endl;
            }
            else {
                cout << "无效指令，请重新输入!" << endl;
            }
        }
    }
*/
    int main()
    {
        PokemonGame game;
        return 0;
    }