#pragma once

class PokemonView
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

