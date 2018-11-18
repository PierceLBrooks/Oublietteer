
// Author: Pierce Brooks

#include <oublietteer/Oubliette.hpp>
#include <oublietteer/Floor.hpp>
#include <oublietteer/Room.hpp>
#include <iostream>

typedef oublietteer::Oubliette Dungeon;

int main()
{
    std::cout << "Hi!" << std::endl;
    Dungeon* dungeon = new Dungeon(sf::Vector2u(sf::Vector2i(100, 100)));
    if (dungeon->createFloor(0))
    {
        oublietteer::Floor* floor = dungeon->getFloor(0);
        for (unsigned int i = 0; i != 10; ++i)
        {
            floor->addRoom();
        }
    }
    delete dungeon;
    std::cout << "Bye!" << std::endl;
    return 0;
}
