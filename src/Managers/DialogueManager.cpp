#include "../../include/Managers/DialogueManager.h"
#include "../../include/Managers/LogManager.h"

DialogueManager::DialogueManager() = default;

void DialogueManager::Init()
{
    _dialogues["battle_start"] = "战斗开始了！";
    _dialogues["battle_win"] = "你赢了！";
    _dialogues["battle_lose"] = "你输了！";
    _dialogues["game_intro_1"] = "欢迎来到宝可梦世界！";
    _dialogues["game_intro_2"] = "你将踏上一段成为宝可梦大师的旅程。";
    _dialogues["game_intro_3"] = "首先，你需要选择你的第一个伙伴。";
    _dialogues["level_1_intro"] = "你来到了森林的边缘，一只野生的宝可梦出现了！";
    _dialogues["level_2_intro"] = "你深入了森林，遇到了更强大的对手！";
    _dialogues["level_3_intro"] = "你来到了冰雪覆盖的山脉，寒冷的气息扑面而来。";
    _dialogues["level_4_intro"] = "你飞向了天空，与空中的霸主相遇！";
    _dialogues["level_5_intro"] = "你进入了幽灵塔，感受到了不寻常的气息。";
    _dialogues["boss_intro"] = "最终的挑战者，天星队的仙后，出现在你面前！";
}

void DialogueManager::ShowDialogue(const std::string& key)
{
    if (_dialogues.count(key))
    {
        LogManager::PrintByChar(_dialogues[key] + "\n");
    }
    else
    {
        LogManager::PrintByChar("未找到对话内容\n", LogColor::Red);
    }
}

void DialogueManager::ShowStory(const std::vector<std::string>& dialogueKeys)
{
    for (const auto& key : dialogueKeys)
    {
        ShowDialogue(key);
        // Optionally, wait for user input to continue
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}