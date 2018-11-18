
// Author: Pierce Brooks

#include <oublietteer/Oubliette.hpp>
#include <iostream>

typedef oublietteer::Oubliette Dungeon;

int main()
{
    std::cout << "Hi!" << std::endl;
    Dungeon* dungeon = new Dungeon();
    delete dungeon;
    std::cout << "Bye!" << std::endl;
    return 0;
}
