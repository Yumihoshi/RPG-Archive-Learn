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
