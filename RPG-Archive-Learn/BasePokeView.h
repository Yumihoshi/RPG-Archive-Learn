#pragma once

class BasePokeView
{
public:
    /// <summary>
    /// 显示宝可梦当前状态信息
    /// </summary>
    virtual void ShowPokemonInfo();

    /// <summary>
    /// 显示宝可梦所有技能信息
    /// </summary>
    virtual void ShowPokemonSkillInfo();
protected:
};

