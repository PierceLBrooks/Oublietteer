
// Author: Pierce Brooks

#ifndef OUBLIETTEER_MATH_UTILITIES_HPP
#define OUBLIETTEER_MATH_UTILITIES_HPP

#include <oublietteer/Vector2.hpp>
#include <vector>
#include <complex>
#include <cmath>
#include <cstdint>

namespace oublietteer
{
    typedef uint8_t Uint8;
    typedef uint16_t Uint16;
    typedef uint32_t Uint32;
    typedef uint64_t Uint64;
    typedef int8_t Int8;
    typedef int16_t Int16;
    typedef int32_t Int32;
    typedef int64_t Int64;
    
    namespace util
    {
        extern const float SQRT_TWO;
        extern const float SQRT_THREE;
        extern const float EULER;
        extern const float PI;
        extern const float HALF_PI;
        extern const float QUARTER_PI;
        extern const float TWO_PI;
        extern const float RAD_TO_DEG;
        extern const float DEG_TO_RAD;
        extern const float INFIN;

        float sqr(float num);
        std::complex<float> sqr(const std::complex<float>& num);
        float sqrt(float num);
    }
}

#endif // OUBLIETTEER_MATH_UTILITIES_HPP

