#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "Common.h"

std::string Common::GetFormattedFloat(float num, int wei)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(wei) << num;
    return oss.str();
}