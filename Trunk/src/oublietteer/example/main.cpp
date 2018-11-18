
// Author: Pierce Brooks

#include <oublietteer/Oubliette.hpp>
#include <oublietteer/Floor.hpp>
#include <oublietteer/Room.hpp>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

typedef oublietteer::Oubliette Dungeon;

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    for (int i = 0; i != argc; ++i)
    {
        std::string argument = std::string(argv[i]);
        arguments.push_back(argument);
        std::cout << argument << std::endl;
    }
    std::cout << "Hi!" << std::endl;
    Dungeon* dungeon = nullptr;
    sf::Image* image = nullptr;
    sf::RenderWindow* window = new sf::RenderWindow();
    auto resolutions = sf::VideoMode::getFullscreenModes();
    window->create(resolutions[resolutions.size()/2], "Oublietteer Example");
    window->setFramerateLimit(60);
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
            }
        }
        if (dungeon == nullptr)
        {
            dungeon = new Dungeon(sf::Vector2u(sf::Vector2i(100, 100)));
            if (dungeon->createFloor(0))
            {
                oublietteer::Floor* floor = dungeon->getFloor(0);
                for (unsigned int i = 0; i != 10; ++i)
                {
                    floor->addRoom();
                }
            }
        }
        else
        {
            if (image == nullptr)
            {
                oublietteer::Floor* floor = dungeon->getFloor(0);
                if (floor != nullptr)
                {
                    image = floor->getImage();
                }
            }
        }
        window->clear(sf::Color::Black);
        window->display();
    }
    delete window;
    if (image != nullptr)
    {
        image->saveToFile("image.png");
    }
    delete image;
    delete dungeon;
    std::cout << "Bye!" << std::endl;
    arguments.clear();
    return 0;
}
