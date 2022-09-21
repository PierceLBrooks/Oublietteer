
// Author: Pierce Brooks

#include <oublietteer/Room.hpp>
#include <oublietteer/Floor.hpp>
#include <cmath>
#include <iostream>

oublietteer::Room::Room(Floor* owner, unsigned int index, const oublietteer::Vector2u& size, float direction) :
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

const oublietteer::Vector2u& oublietteer::Room::getSize() const
{
    return size;
}

const oublietteer::Vector2i& oublietteer::Room::getPosition() const
{
    return position;
}

oublietteer::Vector2f oublietteer::Room::getCenter() const
{
    return oublietteer::Vector2f(position)+(oublietteer::Vector2f(size)*0.5f);
}

oublietteer::Bounds<int> oublietteer::Room::getBounds() const
{
    return oublietteer::Bounds<int>(position.x, position.y, static_cast<int>(size.x), static_cast<int>(size.y));
}

bool oublietteer::Room::settle()
{
    oublietteer::Vector2f direction = oublietteer::Vector2f()-getCenter();
    direction *= 1.0f/sqrtf((direction.x*direction.x)+(direction.y*direction.y));
    if ((direction.x*this->direction.x)+(direction.y*this->direction.y) >= 0.0f)
    {
        return false;
    }
    direction.x *= static_cast<float>(size.x);
    direction.y *= static_cast<float>(size.y);
    position += oublietteer::Vector2i(direction);
    return true;
}

void oublietteer::Room::finish()
{
    bool check;
    bool neighborhood;
    for (;;)
    {
        check = true;
        for (unsigned int i = 0; i != neighbors.size(); ++i)
        {
            std::pair<Room*, oublietteer::Vector2u> neighbor = neighbors[i];
            Room* room = std::get<0>(neighbor);
            oublietteer::Vector2i position = oublietteer::Vector2i(std::get<1>(neighbor));
            if (room == nullptr)
            {
                neighbors.erase(neighbors.begin()+i);
                check = false;
                break;
            }
            neighborhood = false;
            if (getBounds().contains(position))
            {
                for (int j = -1; j <= 1; ++j)
                {
                    for (int k = -1; k <= 1; ++k)
                    {
                        if ((j%2 == 0) == (k%2 == 0))
                        {
                            continue;
                        }
                        if (room->getBounds().contains(position+oublietteer::Vector2i(j, k)))
                        {
                            neighborhood = true;
                            break;
                        }
                    }
                }
            }
            if (!neighborhood)
            {
                neighbors.erase(neighbors.begin()+i);
                check = false;
                break;
            }
            neighborhood = false;
            for (unsigned int j = 0; j != room->getNeighborCount(); ++j)
            {
                if (std::get<0>(room->getNeighbor(j)) == this)
                {
                    neighborhood = true;
                    break;
                }
            }
            if (!neighborhood)
            {
                neighbors.erase(neighbors.begin()+i);
                check = false;
                break;
            }
        }
        if (check)
        {
            break;
        }
    }
}

oublietteer::Random* oublietteer::Room::getRandom() const
{
    return owner->getRandom();
}

unsigned int oublietteer::Room::getNeighborCount() const
{
    return neighbors.size();
}

std::pair<oublietteer::Room*, oublietteer::Vector2u> oublietteer::Room::getNeighbor(unsigned int index) const
{
    unsigned int counter = 0;
    for (std::vector<std::pair<Room*, oublietteer::Vector2u>>::const_iterator iter = neighbors.begin(); iter != neighbors.end(); ++iter)
    {
        if (counter == index)
        {
            return *iter;
        }
        ++counter;
    }
    return std::pair<Room*, oublietteer::Vector2u>(nullptr, oublietteer::Vector2u());
}

void oublietteer::Room::setPosition(const oublietteer::Vector2i& position)
{
    this->position = position;
}

void oublietteer::Room::setNeighbor(unsigned int index, Room* room, const oublietteer::Vector2u& position)
{
    while (neighbors.size() <= index)
    {
        neighbors.push_back(std::pair<Room*, oublietteer::Vector2u>(nullptr, oublietteer::Vector2u()));
    }
    std::get<0>(neighbors[index]) = room;
    std::get<1>(neighbors[index]) = position;
}
