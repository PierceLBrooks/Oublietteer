
// Author: Pierce Brooks

#include <oublietteer/MathUtilities.hpp>
#include <algorithm>

const float oublietteer::util::SQRT_TWO = sqrtf(2.0f);

const float oublietteer::util::SQRT_THREE = sqrtf(3.0f);

const float oublietteer::util::EULER = 2.718281828f;

const float oublietteer::util::PI = 3.14159256359f;

const float oublietteer::util::HALF_PI = 3.14159256359f*0.5f;

const float oublietteer::util::QUARTER_PI = 3.14159256359f*0.25f;

const float oublietteer::util::TWO_PI = 3.14159256359f*2.0f;

const float oublietteer::util::RAD_TO_DEG = 180.0f/3.14159256359f;

const float oublietteer::util::DEG_TO_RAD = 3.14159256359f/180.0f;

const float oublietteer::util::INFIN = std::numeric_limits<float>::infinity();

float oublietteer::util::sqr(float num)
{
    return num*num;
}

std::complex<float> oublietteer::util::sqr(const std::complex<float>& num)
{
    return num*num;
}

float oublietteer::util::sqrt(float num)
{
    if (num != fabsf(num))
    {
        return -sqrtf(fabsf(num));
    }
    return sqrtf(num);
}

