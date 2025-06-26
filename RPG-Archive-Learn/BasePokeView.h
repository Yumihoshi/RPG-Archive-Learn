#pragma once

#include <iostream>
#include <string>
#include "LogManager.h"
#include "Common.h"

template<typename T>
class BasePokeView
{
public:
    std::shared_ptr<T> ModelPtr;

    BasePokeView(std::shared_ptr<T> model) : ModelPtr(model)
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
        LogManager::GetInstance().PrintByChar("\n======");
        LogManager::GetInstance().PrintByChar("宝可梦信息面板", LogColor::Yellow);
        LogManager::GetInstance().PrintByChar("======\n");
    }

    virtual void ShowPokeInfoBasicAttr()
    {
        auto& logger = LogManager::GetInstance();  // 缓存日志管理器实例
        T& pokemon = *ModelPtr;              // 使用引用避免重复解引用
        // 输出信息
        logger.PrintByChar("名称：" + pokemon.GetName() + "\n");

        logger.PrintByChar("属性：" + Common::GetInstance().GetElementName(pokemon.GetElement()) + "\n");
        logger.PrintByChar("血量：", LogColor::Red);
        logger.PrintByChar(std::to_string(pokemon.GetCurHp()) +
            "/" + std::to_string(pokemon.GetMaxHp()) + "\n");
        logger.PrintByChar("魔法值：", LogColor::Blue);
        logger.PrintByChar(std::to_string(pokemon.GetCurMp()) + "/" +
            std::to_string(pokemon.GetMaxMp()) + "\n");
        logger.PrintByChar("伤害：" + std::to_string(pokemon.GetDamage()) + "\n");
    }

    virtual void ShowPokeInfoOther()
    {
        auto& logger = LogManager::GetInstance();  // 缓存日志管理器实例
        T& pokemon = *ModelPtr;              // 使用引用避免重复解引用
        // 格式化百分号
        logger.PrintByChar("闪避率：" + Common::GetInstance().GetFormattedFloat(pokemon.GetFleeRate() * 100) + "%\n");
        logger.PrintByChar("暴击率：" + Common::GetInstance().GetFormattedFloat(pokemon.GetCritRate() * 100) + "%\n");
        logger.PrintByChar("特性&背景：" + pokemon.GetStory() + "\n\n");
    }
};

