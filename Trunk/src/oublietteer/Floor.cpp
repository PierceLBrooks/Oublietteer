
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
    float pi = 22.0f/7.0f;
    Room* room = new Room(this, rooms.size(), getRoomSize(), getRandom()->getFloat(-pi, pi));
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
    if (!isManual)
    {
        return false;
    }
    sf::Vector2i previous = room->getPosition();
    if (room->settle())
    {
        bool settle = false;
        bool check = false;
        bool intersection;
        do
        {
            intersection = false;
            for (unsigned int i = 0; i != rooms.size(); ++i)
            {
                if (room->getIndex() != i)
                {
                    if (room->getBounds().intersects(rooms[i]->getBounds()))
                    {
                        sf::Vector2i current = room->getPosition();
                        sf::Vector2i difference = previous-current;
                        if (difference.x != 0)
                        {
                            difference.x /= abs(difference.x);
                        }
                        if (difference.y != 0)
                        {
                            difference.y /= abs(difference.y);
                        }
                        do
                        {
                            current += difference;
                            room->setPosition(current);
                        } while (room->getBounds().intersects(rooms[i]->getBounds()));
                        check = true;
                        intersection = true;
                        break;
                    }
                }
            }
            if (check)
            {
                if (!intersection)
                {
                    check = false;
                    settle = true;
                }
            }
        } while ((check != settle) && (!settle));
        if (settle)
        {
            isManual = false;
            return false;
        }
        return true;
    }
    isManual = false;
    return false;
}

sf::Vector2u oublietteer::Floor::getRoomSize() const
{
    int width = static_cast<int>(sqrtf(static_cast<float>(size.x)));
    int height = static_cast<int>(sqrtf(static_cast<float>(size.y)));
    return sf::Vector2u(sf::Vector2i(getRandom()->getInt(width/2, width), getRandom()->getInt(height/2, height)));
}

sf::Color oublietteer::Floor::getRoomColor() const
{
    return sf::Color::White;
}

sf::Image* oublietteer::Floor::getImage() const
{
    sf::IntRect bounds = getBounds();
    sf::Image* image = new sf::Image();
    sf::Color background = sf::Color::Transparent;
    sf::Color color = getRoomColor();
    sf::Vector2u position;
    unsigned int dissimilar;
    unsigned int similar;
    bool check;
    Room* room;
    image->create(size.x, size.y, background);
    color = sf::Color(static_cast<sf::Uint8>(255-static_cast<int>(color.r)),
                      static_cast<sf::Uint8>(255-static_cast<int>(color.g)),
                      static_cast<sf::Uint8>(255-static_cast<int>(color.b)),
                      color.a);
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
                    position = sf::Vector2u(x, y)+sf::Vector2u(room->getPosition()+sf::Vector2i(sf::Vector2u(size.x/2, size.y/2)));
                    if ((x == 0) || (y == 0) || (x == room->getSize().x-1) || (y == room->getSize().y-1))
                    {
                        image->setPixel(position.x, position.y, color);
                    }
                    else
                    {
                        image->setPixel(position.x, position.y, getRoomColor());
                    }
                }
            }
        }
    }
    for (unsigned int x = 0; x != image->getSize().x; ++x)
    {
        for (unsigned int y = 0; y != image->getSize().y; ++y)
        {
            if (image->getPixel(x, y) == color)
            {
                if ((x != 0) && (y != 0) && (x != image->getSize().x-1) && (image->getSize().y-1))
                {
                    check = true;
                    similar = 0;
                    dissimilar = 0;
                    for (int i = -1; i != 2; ++i)
                    {
                        for (int j = -1; j != 2; ++j)
                        {
                            if ((i != 0) || (j != 0))
                            {
                                position = sf::Vector2u(sf::Vector2i(sf::Vector2u(x, y))+sf::Vector2i(i, j));
                                if (image->getPixel(position.x, position.y) == background)
                                {
                                    check = false;
                                    break;
                                }
                                if (image->getPixel(position.x, position.y) == color)
                                {
                                    ++similar;
                                }
                                else
                                {
                                    if (image->getPixel(position.x, position.y) == getRoomColor())
                                    {
                                        ++dissimilar;
                                    }
                                }
                            }
                        }
                        if (!check)
                        {
                            break;
                        }
                    }
                    if (check)
                    {
                        if ((similar >= 2) || (dissimilar >= 5))
                        {
                            image->setPixel(x, y, getRoomColor());
                        }
                    }
                }
            }
        }
    }
    return image;
}

bool oublietteer::Floor::getIsManual() const
{
    return isManual;
}

oublietteer::Random* oublietteer::Floor::getRandom() const
{
    return owner->getRandom();
}
