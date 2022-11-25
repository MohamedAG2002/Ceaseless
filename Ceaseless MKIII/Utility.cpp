#include "Utility.h"

const float& utl::Clamp(float& value, float min, float max)
{
    if (value > max) return value = max;
    else if (value < min) return value = min;
    else return value;
}
