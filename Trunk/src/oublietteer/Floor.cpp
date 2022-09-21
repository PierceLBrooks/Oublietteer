
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

const oublietteer::Vector2u& oublietteer::Floor::getSize() const
{
    return size;
}

oublietteer::Bounds<int> oublietteer::Floor::getBounds() const
{
    return oublietteer::Bounds<int>(-static_cast<int>(size.x/2), -static_cast<int>(size.y/2), static_cast<int>(size.x), static_cast<int>(size.y));
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
    oublietteer::Vector2i previous = room->getPosition();
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
                        oublietteer::Vector2u first;
                        oublietteer::Vector2u last;
                        oublietteer::Vector2i current = room->getPosition();
                        oublietteer::Vector2i difference = previous-current;
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
                                        if (first == oublietteer::Vector2u(x*(room->getSize().x-1), y*(room->getSize().y-1)))
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
                                        if (last == oublietteer::Vector2u(x*(rooms[i]->getSize().x-1), y*(rooms[i]->getSize().y-1)))
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

oublietteer::Vector2u oublietteer::Floor::getRoomSize() const
{
    int width = static_cast<int>(sqrtf(static_cast<float>(size.x)));
    int height = static_cast<int>(sqrtf(static_cast<float>(size.y)));
    return oublietteer::Vector2u(oublietteer::Vector2i(getRandom()->getInt(width/2, width), getRandom()->getInt(height/2, height)));
}

oublietteer::Pixel oublietteer::Floor::getRoomColor() const
{
    return oublietteer::Pixel::WHITE;
}

oublietteer::Bitmap* oublietteer::Floor::getImage() const
{
    oublietteer::Bounds<int> bounds = getBounds();
    oublietteer::Bitmap* image = new oublietteer::Bitmap();
    oublietteer::Pixel background = oublietteer::Pixel::TRANSPARENT;
    oublietteer::Pixel color = getRoomColor();
    oublietteer::Vector2u position;
    unsigned int dissimilar;
    unsigned int similar;
    bool check;
    Room* room;
    image->create(size.x, size.y, background);
    color = oublietteer::Pixel(static_cast<oublietteer::Uint8>(255-static_cast<int>(color.r)),
                      static_cast<oublietteer::Uint8>(255-static_cast<int>(color.g)),
                      static_cast<oublietteer::Uint8>(255-static_cast<int>(color.b)),
                      color.a);
    for (unsigned int i = 0; i != rooms.size(); ++i)
    {
        room = rooms[i];
        if ((bounds.contains(room->getPosition())) &&
            (bounds.contains(room->getPosition()+oublietteer::Vector2i(0, static_cast<int>(room->getSize().y)))) &&
            (bounds.contains(room->getPosition()+oublietteer::Vector2i(static_cast<int>(room->getSize().x), 0))) &&
            (bounds.contains(room->getPosition()+oublietteer::Vector2i(room->getSize()))))
        {
            for (unsigned int x = 0; x != room->getSize().x; ++x)
            {
                for (unsigned int y = 0; y != room->getSize().y; ++y)
                {
                    position = oublietteer::Vector2u(x, y)+oublietteer::Vector2u(room->getPosition()+oublietteer::Vector2i(oublietteer::Vector2u(size.x/2, size.y/2)));
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
            if (image->getPixel(x, y).compare(color))
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
                                position = oublietteer::Vector2u(oublietteer::Vector2i(oublietteer::Vector2u(x, y))+oublietteer::Vector2i(i, j));
                                if (image->getPixel(position.x, position.y).compare(background))
                                {
                                    check = false;
                                    break;
                                }
                                if (image->getPixel(position.x, position.y).compare(color))
                                {
                                    ++similar;
                                }
                                else
                                {
                                    if (image->getPixel(position.x, position.y).compare(getRoomColor()))
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
    color = oublietteer::Pixel(static_cast<oublietteer::Uint8>((static_cast<int>(color.r)+static_cast<int>(getRoomColor().r))/2),
                      static_cast<oublietteer::Uint8>((static_cast<int>(color.g)+static_cast<int>(getRoomColor().g))/2),
                      static_cast<oublietteer::Uint8>((static_cast<int>(color.b)+static_cast<int>(getRoomColor().b))/2),
                      color.a);
    for (unsigned int i = 0; i != rooms.size(); ++i)
    {
        room = rooms[i];
        for (unsigned int j = 0; j != room->getNeighborCount(); ++j)
        {
            position = std::get<1>(room->getNeighbor(j))+oublietteer::Vector2u(room->getPosition()+oublietteer::Vector2i(oublietteer::Vector2u(size.x/2, size.y/2)));
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

float oublietteer::Floor::getMagnitude(const oublietteer::Vector2f& target) const
{
    return util::sqrt(powf(target.x, 2.0f)+powf(target.y, 2.0f));
}

float oublietteer::Floor::getDistance(const oublietteer::Vector2f& first, const oublietteer::Vector2f& last) const
{
    return util::sqrt(powf(first.x-last.x, 2.0f)+powf(first.y-last.y, 2.0f));
}

oublietteer::Vector2u oublietteer::Floor::getRoomNeighborPosition(Room* first, Room* last) const
{
    bool neighbor;
    oublietteer::Vector2i position;
    oublietteer::Vector2f distance;
    oublietteer::Vector2f firstPosition;
    oublietteer::Vector2f lastPosition;
    oublietteer::Bounds<int> firstBounds = first->getBounds();
    oublietteer::Bounds<int> lastBounds = last->getBounds();
    //distance.y = std::numeric_limits<float>::infinity();
    for (int x0 = firstBounds.x; x0 != firstBounds.x+firstBounds.width; ++x0)
    {
        for (int y0 = firstBounds.y; y0 != firstBounds.y+firstBounds.height; ++y0)
        {
            for (int x1 = lastBounds.x; x1 != lastBounds.x+lastBounds.width; ++x1)
            {
                for (int y1 = lastBounds.y; y1 != lastBounds.y+lastBounds.height; ++y1)
                {
                    firstPosition = oublietteer::Vector2f(oublietteer::Vector2i(x0, y0));
                    lastPosition = oublietteer::Vector2f(oublietteer::Vector2i(x1, y1));
                    distance.x = getDistance(firstPosition, first->getCenter());
                    distance.x += getDistance(lastPosition, last->getCenter());
                    distance.x += 1.0f/powf(getDistance(firstPosition, lastPosition)/powf(getMagnitude(oublietteer::Vector2f(first->getSize()))+getMagnitude(oublietteer::Vector2f(last->getSize())), 2.0f), 2.0f);
                    if (distance.x > distance.y)
                    {
                        position = oublietteer::Vector2i(x0, y0);
                        distance.y = distance.x;
                    }
                }
            }
        }
    }
    for (int x = firstBounds.x; x <= firstBounds.x+firstBounds.width; x += firstBounds.width-1)
    {
        for (int y = firstBounds.y; y <= firstBounds.y+firstBounds.height; y += firstBounds.height-1)
        {
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    if ((i%2 == 0) == (j%2 == 0))
                    {
                        continue;
                    }
                    if ((!lastBounds.contains(position+oublietteer::Vector2i(i, j))) && (firstBounds.contains(position+oublietteer::Vector2i(i, j))))
                    {
                        for (int k = -1; k <= 1; ++k)
                        {
                            for (int l = -1; l <= 1; ++l)
                            {
                                if ((k%2 == 0) == (l%2 == 0))
                                {
                                    continue;
                                }
                                if ((lastBounds.contains(position+oublietteer::Vector2i(i, j)+oublietteer::Vector2i(k, l))) && (!firstBounds.contains(position+oublietteer::Vector2i(i, j)+oublietteer::Vector2i(k, l))))
                                {
                                    return oublietteer::Vector2u((position+oublietteer::Vector2i(i, j))-oublietteer::Vector2i(firstBounds.x, firstBounds.y));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int x = lastBounds.x; x <= lastBounds.x+lastBounds.width; x += lastBounds.width-1)
    {
        for (int y = lastBounds.y; y <= lastBounds.y+lastBounds.height; y += lastBounds.height-1)
        {
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    if ((i%2 == 0) == (j%2 == 0))
                    {
                        continue;
                    }
                    if (position+oublietteer::Vector2i(i, j) == oublietteer::Vector2i(x, y))
                    {
                        for (int k = -1; k <= 1; ++k)
                        {
                            for (int l = -1; l <= 1; ++l)
                            {
                                if ((k%2 == 0) == (l%2 == 0))
                                {
                                    continue;
                                }
                                if ((!lastBounds.contains(position+oublietteer::Vector2i(k, l))) && (firstBounds.contains(position+oublietteer::Vector2i(k, l))))
                                {
                                    for (int m = -1; m <= 1; ++m)
                                    {
                                        for (int n = -1; n <= 1; ++n)
                                        {
                                            if ((m%2 == 0) == (n%2 == 0))
                                            {
                                                continue;
                                            }
                                            if ((lastBounds.contains(position+oublietteer::Vector2i(k, l)+oublietteer::Vector2i(m, n))) && (!firstBounds.contains(position+oublietteer::Vector2i(k, l)+oublietteer::Vector2i(m, n))))
                                            {
                                                return oublietteer::Vector2u((position+oublietteer::Vector2i(k, l))-oublietteer::Vector2i(firstBounds.x, firstBounds.y));
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
    return oublietteer::Vector2u(position-oublietteer::Vector2i(firstBounds.x, firstBounds.y));
}
