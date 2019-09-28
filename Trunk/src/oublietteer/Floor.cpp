
// Author: Pierce Brooks

#include <oublietteer/Floor.hpp>
#include <oublietteer/Room.hpp>
#include <oublietteer/Oubliette.hpp>
#include <limits>
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
                        sf::Vector2u first;
                        sf::Vector2u last;
                        sf::Vector2i current = room->getPosition();
                        sf::Vector2i difference = previous-current;
                        bool neighborhood = true;
                        bool neighbors;
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
                        if (neighborhood)
                        {
                            neighbors = false;
                            for (unsigned int j = 0; j != room->getNeighborCount(); ++j)
                            {
                                if (std::get<0>(room->getNeighbor(j)) == rooms[i])
                                {
                                    neighbors = true;
                                    break;
                                }
                            }
                            if (!neighbors)
                            {
                                first = getRoomNeighborPosition(room, rooms[i]);
                                for (unsigned int x = 0; x <= 1; ++x)
                                {
                                    for (unsigned int y = 0; y <= 1; ++y)
                                    {
                                        if (first == sf::Vector2u(x*(room->getSize().x-1), y*(room->getSize().y-1)))
                                        {
                                            neighborhood = false;
                                            break;
                                        }
                                    }
                                }
                                if (neighborhood)
                                {
                                    room->setNeighbor(room->getNeighborCount(), rooms[i], first);
                                }
                            }
                        }
                        if (neighborhood)
                        {
                            neighbors = false;
                            for (unsigned int j = 0; j != rooms[i]->getNeighborCount(); ++j)
                            {
                                if (std::get<0>(rooms[i]->getNeighbor(j)) == room)
                                {
                                    neighbors = true;
                                    break;
                                }
                            }
                            if (!neighbors)
                            {
                                last = getRoomNeighborPosition(rooms[i], room);
                                for (unsigned int x = 0; x <= 1; ++x)
                                {
                                    for (unsigned int y = 0; y <= 1; ++y)
                                    {
                                        if (last == sf::Vector2u(x*(rooms[i]->getSize().x-1), y*(rooms[i]->getSize().y-1)))
                                        {
                                            neighborhood = false;
                                            break;
                                        }
                                    }
                                }
                                if (neighborhood)
                                {
                                    rooms[i]->setNeighbor(rooms[i]->getNeighborCount(), room, last);
                                }
                            }
                        }
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
        room->finish();
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
    color = sf::Color(static_cast<sf::Uint8>((static_cast<int>(color.r)+static_cast<int>(getRoomColor().r))/2),
                      static_cast<sf::Uint8>((static_cast<int>(color.g)+static_cast<int>(getRoomColor().g))/2),
                      static_cast<sf::Uint8>((static_cast<int>(color.b)+static_cast<int>(getRoomColor().b))/2),
                      color.a);
    for (unsigned int i = 0; i != rooms.size(); ++i)
    {
        room = rooms[i];
        for (unsigned int j = 0; j != room->getNeighborCount(); ++j)
        {
            position = std::get<1>(room->getNeighbor(j))+sf::Vector2u(room->getPosition()+sf::Vector2i(sf::Vector2u(size.x/2, size.y/2)));
            image->setPixel(position.x, position.y, color);
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

float oublietteer::Floor::getMagnitude(const sf::Vector2f& target) const
{
    return sqrtf(powf(target.x, 2.0f)+powf(target.y, 2.0f));
}

float oublietteer::Floor::getDistance(const sf::Vector2f& first, const sf::Vector2f& last) const
{
    return sqrtf(powf(first.x-last.x, 2.0f)+powf(first.y-last.y, 2.0f));
}

sf::Vector2u oublietteer::Floor::getRoomNeighborPosition(Room* first, Room* last) const
{
    bool neighbor;
    sf::Vector2i position;
    sf::Vector2f distance;
    sf::Vector2f firstPosition;
    sf::Vector2f lastPosition;
    sf::IntRect firstBounds = first->getBounds();
    sf::IntRect lastBounds = last->getBounds();
    //distance.y = std::numeric_limits<float>::infinity();
    for (int x0 = firstBounds.left; x0 != firstBounds.left+firstBounds.width; ++x0)
    {
        for (int y0 = firstBounds.top; y0 != firstBounds.top+firstBounds.height; ++y0)
        {
            for (int x1 = lastBounds.left; x1 != lastBounds.left+lastBounds.width; ++x1)
            {
                for (int y1 = lastBounds.top; y1 != lastBounds.top+lastBounds.height; ++y1)
                {
                    firstPosition = sf::Vector2f(sf::Vector2i(x0, y0));
                    lastPosition = sf::Vector2f(sf::Vector2i(x1, y1));
                    distance.x = getDistance(firstPosition, first->getCenter());
                    distance.x += getDistance(lastPosition, last->getCenter());
                    distance.x += 1.0f/powf(getDistance(firstPosition, lastPosition)/powf(getMagnitude(sf::Vector2f(first->getSize()))+getMagnitude(sf::Vector2f(last->getSize())), 2.0f), 2.0f);
                    if (distance.x > distance.y)
                    {
                        position = sf::Vector2i(x0, y0);
                        distance.y = distance.x;
                    }
                }
            }
        }
    }
    for (int x = firstBounds.left; x <= firstBounds.left+firstBounds.width; x += firstBounds.width-1)
    {
        for (int y = firstBounds.top; y <= firstBounds.top+firstBounds.height; y += firstBounds.height-1)
        {
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    if ((i%2 == 0) == (j%2 == 0))
                    {
                        continue;
                    }
                    if ((!lastBounds.contains(position+sf::Vector2i(i, j))) && (firstBounds.contains(position+sf::Vector2i(i, j))))
                    {
                        for (int k = -1; k <= 1; ++k)
                        {
                            for (int l = -1; l <= 1; ++l)
                            {
                                if ((k%2 == 0) == (l%2 == 0))
                                {
                                    continue;
                                }
                                if ((lastBounds.contains(position+sf::Vector2i(i, j)+sf::Vector2i(k, l))) && (!firstBounds.contains(position+sf::Vector2i(i, j)+sf::Vector2i(k, l))))
                                {
                                    return sf::Vector2u((position+sf::Vector2i(i, j))-sf::Vector2i(firstBounds.left, firstBounds.top));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int x = lastBounds.left; x <= lastBounds.left+lastBounds.width; x += lastBounds.width-1)
    {
        for (int y = lastBounds.top; y <= lastBounds.top+lastBounds.height; y += lastBounds.height-1)
        {
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    if ((i%2 == 0) == (j%2 == 0))
                    {
                        continue;
                    }
                    if (position+sf::Vector2i(i, j) == sf::Vector2i(x, y))
                    {
                        for (int k = -1; k <= 1; ++k)
                        {
                            for (int l = -1; l <= 1; ++l)
                            {
                                if ((k%2 == 0) == (l%2 == 0))
                                {
                                    continue;
                                }
                                if ((!lastBounds.contains(position+sf::Vector2i(k, l))) && (firstBounds.contains(position+sf::Vector2i(k, l))))
                                {
                                    for (int m = -1; m <= 1; ++m)
                                    {
                                        for (int n = -1; n <= 1; ++n)
                                        {
                                            if ((m%2 == 0) == (n%2 == 0))
                                            {
                                                continue;
                                            }
                                            if ((lastBounds.contains(position+sf::Vector2i(k, l)+sf::Vector2i(m, n))) && (!firstBounds.contains(position+sf::Vector2i(k, l)+sf::Vector2i(m, n))))
                                            {
                                                return sf::Vector2u((position+sf::Vector2i(k, l))-sf::Vector2i(firstBounds.left, firstBounds.top));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return sf::Vector2u(position-sf::Vector2i(firstBounds.left, firstBounds.top));
}
