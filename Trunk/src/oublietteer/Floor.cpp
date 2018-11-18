
// Author: Pierce Brooks

#include <oublietteer/Floor.hpp>
#include <oublietteer/Room.hpp>
#include <oublietteer/Oubliette.hpp>
#include <iostream>

oublietteer::Floor::Floor(Oubliette* owner, int identifier) :
    owner(owner),
    identifier(identifier),
    isManual(false),
    size(owner->getSize())
{
    std::cout << "FLOORING" << this << std::endl;
}

oublietteer::Floor::~Floor()
{
    for (unsigned int i = 0; i != rooms.size(); ++i)
    {
        delete rooms[i];
    }
    rooms.clear();
    std::cout << "FLOORED" << this << std::endl;
}

oublietteer::Oubliette* oublietteer::Floor::getOwner() const
{
    return owner;
}

int oublietteer::Floor::getIdentifier() const
{
    return identifier;
}

const sf::Vector2u& oublietteer::Floor::getSize() const
{
    return size;
}

sf::IntRect oublietteer::Floor::getBounds() const
{
    return sf::IntRect(-static_cast<int>(size.x/2), -static_cast<int>(size.y/2), static_cast<int>(size.x), static_cast<int>(size.y));
}

unsigned int oublietteer::Floor::getRoomCount() const
{
    return rooms.size();
}

bool oublietteer::Floor::addRoom(bool manual)
{
    if (isManual)
    {
        return false;
    }
    Room* room = new Room(this, rooms.size(), getRoomSize(), 0.0f);
    rooms.push_back(room);
    isManual = true;
    if (!manual)
    {
        while (isManual)
        {
            if (!settleRoom(room))
            {
                break;
            }
        }
        isManual = false;
    }
    return true;
}

oublietteer::Room* oublietteer::Floor::getRoom(unsigned int index) const
{
    if (index >= rooms.size())
    {
        return nullptr;
    }
    return rooms[index];
}

bool oublietteer::Floor::settleRoom(Room* room)
{

}

sf::Vector2u oublietteer::Floor::getRoomSize() const
{
    return sf::Vector2u(sf::Vector2i(4, 4));
}

sf::Color oublietteer::Floor::getRoomColor() const
{
    return sf::Color::Black;
}

sf::Image* oublietteer::Floor::getImage() const
{
    sf::IntRect bounds = getBounds();
    sf::Image* image = new sf::Image();
    sf::Vector2u position;
    Room* room;
    image->create(size.x, size.y, sf::Color::Transparent);
    for (unsigned int i = 0; i != rooms.size(); ++i)
    {
        room = rooms[i];
        if ((bounds.contains(room->getPosition())) &&
            (bounds.contains(room->getPosition()+sf::Vector2i(0, static_cast<int>(room->getSize().y)))) &&
            (bounds.contains(room->getPosition()+sf::Vector2i(static_cast<int>(room->getSize().x), 0))) &&
            (bounds.contains(room->getPosition()+sf::Vector2i(room->getSize()))))
        {
            for (unsigned int x = 0; x != room->getSize().x; ++x)
            {
                for (unsigned int y = 0; y != room->getSize().y; ++y)
                {
                    position = sf::Vector2u(x, y)+sf::Vector2u(room->getPosition()+sf::Vector2i(size.x/2, size.y/2));
                    image->setPixel(position.x, position.y, getRoomColor());
                }
            }
        }
    }
    return image;
}
