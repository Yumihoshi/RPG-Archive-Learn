#include <iostream>
#include <string>
#include "../../../../include/MVC/Views/Poke/IcePokeView.h"
#include "../../../../include/Managers/LogManager.h"

void IcePokeView::ShowPokeInfo()
{
    auto m = std::dynamic_pointer_cast<IcePokeModel>(ModelPtr);
    ShowPokeInfoTitle();
    ShowPokeInfoBasicAttr();
    LogManager::PrintByChar(
            "防御力：" + std::to_string(m->GetDefendValue()) + "\n");
    ShowPokeInfoOther();
}
