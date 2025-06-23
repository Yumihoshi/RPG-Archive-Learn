#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "Common.h"

using namespace std;

string Common::GetFormattedFloat(float num, int wei)
{
    ostringstream oss;
    oss << std::fixed << setprecision(wei) << num;
    return oss.str();
}