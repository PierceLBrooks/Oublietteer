
// Author: Pierce Brooks

#include <oublietteer/Oubliette.hpp>
#include <oublietteer/Floor.hpp>
#include <iostream>

oublietteer::Oubliette::Oubliette(const sf::Vector2u& size) :
    size(size)
{
    std::cout << "OUBLIETTEERING" << this << std::endl;
}

oublietteer::Oubliette::~Oubliette()
{
    for (std::map<int, Floor*>::iterator iter = floors.begin(); iter != floors.end(); ++iter)
    {
        delete iter->second;
    }
    floors.clear();
    std::cout << "OUBLIETTEERED" << this << std::endl;
}

bool oublietteer::Oubliette::createFloor(int identifier)
{
    Floor* floor = getFloor(identifier);
    if (floor != nullptr)
    {
        return false;
    }
    floor = new Floor(this, identifier);
    floors[identifier] = floor;
    return true;
}

oublietteer::Floor* oublietteer::Oubliette::getFloor(int identifier) const
{
    std::map<int, Floor*>::const_iterator iter = floors.find(identifier);
    if (iter != floors.end())
    {
        return iter->second;
    }
    return nullptr;
}

const sf::Vector2u& oublietteer::Oubliette::getSize() const
{
    return size;
}

sf::IntRect oublietteer::Oubliette::getBounds() const
{
    return sf::IntRect(-static_cast<int>(size.x/2), -static_cast<int>(size.y/2), static_cast<int>(size.x), static_cast<int>(size.y));
}
