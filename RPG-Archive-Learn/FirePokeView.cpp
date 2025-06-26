#include <string>
#include "Common.h"
#include "FirePokeView.h"
#include "LogManager.h"


FirePokeView::FirePokeView(std::shared_ptr<FirePokeModel> model)
{
    ModelPtr = model;
}

void FirePokeView::ShowPokemonInfo()
{
    BasePokeView::ShowPokemonInfo();
    auto& logger = LogManager::GetInstance();  // 缓存日志管理器实例
    FirePokeModel& pokemon = *ModelPtr;              // 使用引用避免重复解引用

    // 输出信息
    logger.PrintByChar("名称：" + pokemon.GetName() + "\n");

    logger.PrintByChar("血量：", LogColor::Red);
    logger.PrintByChar(std::to_string((*ModelPtr).GetCurHp()) +
        "/" + std::to_string((*ModelPtr).GetMaxHp()) + "\n");
    logger.PrintByChar("魔法值：", LogColor::Blue);
    logger.PrintByChar(std::to_string((*ModelPtr).GetCurMp()) + "/" +
        std::to_string((*ModelPtr).GetMaxMp()) + "\n");
    logger.PrintByChar("伤害：" + std::to_string((*ModelPtr).GetDamage()) + "\n");
    logger.PrintByChar("属性：火\n");

    // 格式化百分号
    logger.PrintByChar("闪避率：" + Common::GetInstance().GetFormattedFloat(pokemon.GetFleeRate() * 100) + "%\n");
    logger.PrintByChar("暴击率：" + Common::GetInstance().GetFormattedFloat(pokemon.GetCritRate() * 100) + "%\n");
    logger.PrintByChar("详情：高生命值，低魔法值，在某次洪灾中牺牲自己，救下了人们，后被念时复活。\n\n");
}

void FirePokeView::ShowPokemonSkillInfo()
{
    FirePokeModel& pokemon = *ModelPtr;              // 使用引用避免重复解引用
    // TODO: 完善技能信息显示
    BasePokeView::ShowPokemonSkillInfo();
}
