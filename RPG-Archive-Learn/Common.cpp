#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include "Common.h"

Common::Common()
{
    _gen = std::mt19937(std::random_device()());
}

std::string Common::GetFormattedFloat(float num, int wei)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(wei) << num;
    return oss.str();
}

float Common::GetRandomFloat(float min, float max)
{
    std::uniform_real_distribution<float> dis(min, max);
    // 创建一个随机数生成器，保留小数点后两位
    float result = dis(_gen);
    result = std::round(result * 100) / 100;

    return result;
}

std::string Common::GetElementName(ElementType type)
{
    switch (type)
    {
    case ElementType::Fire:
        return "火";
    case ElementType::Fly:
        return "飞行";
    case ElementType::Ghost:
        return "幽灵";
    case ElementType::Grass:
        return "草";
    case ElementType::Ice:
        return "冰";
    default:
        return "无";
    }
}
