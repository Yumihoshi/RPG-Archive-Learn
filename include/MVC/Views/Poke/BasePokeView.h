#pragma once

#include <iostream>
#include <string>
#include <utility>
#include "../../../Managers/LogManager.h"
#include "../../../Common/Common.h"
#include "../../Models/Poke/BasePokeModel.h"

class BasePokeView
{
public:
    std::shared_ptr<BasePokeModel> ModelPtr;

    explicit BasePokeView(std::shared_ptr<BasePokeModel> model) : ModelPtr(
            std::move(model))
    {
    }

    /// <summary>
    /// 显示宝可梦当前状态信息
    /// </summary>
    virtual void ShowPokeInfo()
    {
        ShowPokeInfoTitle();
        ShowPokeInfoBasicAttr();
        ShowPokeInfoOther();
    }

protected:
    virtual void ShowPokeInfoTitle()
    {
        // 显示标题
        LogManager::PrintByChar("\n======");
        LogManager::PrintByChar("宝可梦信息面板", LogColor::Yellow);
        LogManager::PrintByChar("======\n");
    }

    virtual void ShowPokeInfoBasicAttr()
    {
        // 输出信息
        LogManager::PrintByChar("名称：" + ModelPtr->GetName() + "\n");

        LogManager::PrintByChar(
                "属性：" + Common::GetElementName(ModelPtr->GetElement()) +
                "\n");
        LogManager::PrintByChar("血量：", LogColor::Red);
        LogManager::PrintByChar(std::to_string(ModelPtr->GetCurHp()) +
                                "/" + std::to_string(ModelPtr->GetMaxHp()) +
                                "\n");
        LogManager::PrintByChar("魔法值：", LogColor::Blue);
        LogManager::PrintByChar(std::to_string(ModelPtr->GetCurMp()) + "/" +
                                std::to_string(ModelPtr->GetMaxMp()) + "\n");
        LogManager::PrintByChar(
                "伤害：" + std::to_string(ModelPtr->GetDamage()) + "\n");
    }

    virtual void ShowPokeInfoOther()
    {
        // 格式化百分号
        LogManager::PrintByChar("闪避率：" + Common::GetFormattedFloat(
                ModelPtr->GetFleeRate() * 100) + "%\n");
        LogManager::PrintByChar("暴击率：" + Common::GetFormattedFloat(
                ModelPtr->GetCritRate() * 100) + "%\n");
        LogManager::PrintByChar("特性&背景：" + ModelPtr->GetStory() + "\n\n");
    }
};

