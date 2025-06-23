#pragma once
#include "PokemonModel.h"
class FirePokeModel : public PokemonModel
{
public:

private:
    bool _isKuangBao = false;       // 是否处于狂暴状态
    int _KuangBaoZengShang;         // 狂暴增伤数值
};

