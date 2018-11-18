
// Author: Pierce Brooks

#include <oublietteer/Random.hpp>

oublietteer::Random::Random(unsigned int seed)
{
    initialize(seed);
}

oublietteer::Random::~Random()
{

}

void oublietteer::Random::initialize(unsigned int seed)
{
    rng.seed(seed);
}

bool oublietteer::Random::getBool()
{
    return (getInt(0,1)==0);
}

bool oublietteer::Random::getBool(float chance)
{
    if ((chance < 0.0f) || (chance > 1.0f))
    {
        return false;
    }
    return (getFloat(0.0f,1.0f)<chance);
}

int oublietteer::Random::getInt(int minimum, int maximum)
{
    distributorInt = std::uniform_int_distribution<int>(minimum, maximum);
    return distributorInt(rng);
}

float oublietteer::Random::getFloat(float minimum, float maximum)
{
    distributorFloat = std::uniform_real_distribution<float>(minimum, maximum);
    return distributorFloat(rng);
}
