
// Author: Pierce Brooks

#include <oublietteer/Room.hpp>
#include <oublietteer/Floor.hpp>
#include <cmath>
#include <iostream>

oublietteer::Room::Room(Floor* owner, unsigned int index, const sf::Vector2u& size, float direction) :
    owner(owner),
    index(index),
    size(size)
{
    std::cout << "ROOMING" << this << std::endl;
    this->direction.x = -cosf(direction);
    this->direction.y = -sinf(direction);
    position.x = static_cast<int>(this->direction.x*static_cast<float>(owner->getSize().x));
    position.y = static_cast<int>(this->direction.y*static_cast<float>(owner->getSize().y));
}

oublietteer::Room::~Room()
{
    std::cout << "ROOMED" << this << std::endl;
}

oublietteer::Floor* oublietteer::Room::getOwner() const
{
    return owner;
}

unsigned int oublietteer::Room::getIndex() const
{
    return index;
}

const sf::Vector2u& oublietteer::Room::getSize() const
{
    return size;
}

const sf::Vector2i& oublietteer::Room::getPosition() const
{
    return position;
}

sf::Vector2f oublietteer::Room::getCenter() const
{
    return sf::Vector2f(position)+(sf::Vector2f(size)*0.5f);
}

sf::IntRect oublietteer::Room::getBounds() const
{
    return sf::IntRect(position.x, position.y, static_cast<int>(size.x), static_cast<int>(size.y));
}

bool oublietteer::Room::settle()
{
    sf::Vector2f direction = sf::Vector2f()-getCenter();
    direction *= 1.0f/sqrtf((direction.x*direction.x)+(direction.y*direction.y));
    if ((direction.x*this->direction.x)+(direction.y*this->direction.y) >= 0.0f)
    {
        return false;
    }
    direction.x *= static_cast<float>(size.x);
    direction.y *= static_cast<float>(size.y);
    position += sf::Vector2i(direction);
    return true;
}

oublietteer::Random* oublietteer::Room::getRandom() const
{
    return owner->getRandom();
}

void oublietteer::Room::setPosition(const sf::Vector2i& position)
{
    this->position = position;
}
