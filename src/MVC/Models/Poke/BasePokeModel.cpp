#include "../../../include/MVC/Models/Poke/BasePokeModel.h"
#include "../../../include/MVC/Models/Poke/FirePokeModel.h"
#include "../../../include/MVC/Models/Poke/GrassPokeModel.h"
#include "../../../include/MVC/Models/Poke/IcePokeModel.h"
#include "../../../include/MVC/Models/Poke/FlyPokeModel.h"
#include "../../../include/MVC/Models/Poke/GhostPokeModel.h"

std::shared_ptr<BasePokeModel> BasePokeModel::CreateFromJson(const json& j) {
    ElementType type = j.at("_element").get<ElementType>();
    std::shared_ptr<BasePokeModel> poke;
    switch (type) {
        case ElementType::Fire:
            poke = std::make_shared<FirePokeModel>();
            break;
        case ElementType::Grass:
            poke = std::make_shared<GrassPokeModel>();
            break;
        case ElementType::Ice:
            poke = std::make_shared<IcePokeModel>();
            break;
        case ElementType::Fly:
            poke = std::make_shared<FlyPokeModel>();
            break;
        case ElementType::Ghost:
            poke = std::make_shared<GhostPokeModel>();
            break;
        default:
            // Handle unknown type or throw an error
            return nullptr;
    }
    from_json(j, *poke);
    return poke;
}