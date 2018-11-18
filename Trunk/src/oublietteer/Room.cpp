
// Author: Pierce Brooks

#include <oublietteer/Room.hpp>
#include <oublietteer/Floor.hpp>
#include <cmath>
#include <iostream>

oublietteer::Room::Room(Floor* owner, unsigned int index, const sf::Vector2u& size, float position) :
    owner(owner),
    index(index),
    size(size)
{
    std::cout << "ROOMING" << this << std::endl;
    this->position.x = static_cast<int>(cosf(position)*static_cast<float>(owner->getSize().x)*0.5f);
    this->position.y = static_cast<int>(sinf(position)*static_cast<float>(owner->getSize().y)*0.5f);
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

sf::IntRect oublietteer::Room::getBounds() const
{
    return sf::IntRect(position.x, position.y, static_cast<int>(size.x), static_cast<int>(size.y));
}
