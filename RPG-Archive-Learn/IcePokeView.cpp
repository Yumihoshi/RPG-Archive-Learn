#include <iostream>
#include <string>
#include "IcePokeView.h"
#include "LogManager.h"

void IcePokeView::ShowPokeInfo()
{
    ShowPokeInfoTitle();
    ShowPokeInfoBasicAttr();
    LogManager::GetInstance().PrintByChar("防御力：" + std::to_string(ModelPtr->GetDefendValue()) + "\n");
    ShowPokeInfoOther();
}
