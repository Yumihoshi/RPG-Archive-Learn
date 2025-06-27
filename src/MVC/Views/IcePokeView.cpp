#include <iostream>
#include <string>
#include "../../../include/MVC/Views/IcePokeView.h"
#include "../../../include/Managers/LogManager.h"

void IcePokeView::ShowPokeInfo()
{
    ShowPokeInfoTitle();
    ShowPokeInfoBasicAttr();
    LogManager::PrintByChar("防御力：" + std::to_string(ModelPtr->GetDefendValue()) + "\n");
    ShowPokeInfoOther();
}
