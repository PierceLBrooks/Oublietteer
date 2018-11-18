
// Author: Pierce Brooks

#include <oublietteer/Oubliette.hpp>
#include <oublietteer/Floor.hpp>
#include <oublietteer/Room.hpp>
#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

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
    int index = -1;
    bool automatic = true;
    bool manual = false;
    bool change = false;
    Dungeon* dungeon = nullptr;
    sf::Sprite* sprite = nullptr;
    sf::Texture* texture = nullptr;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            manual = true;
        }
        else
        {
            manual = false;
        }
        if (dungeon == nullptr)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                dungeon = new Dungeon(sf::Vector2u(window->getSize().y/2, window->getSize().y/2));
                change = true;
                std::cout << "Welcome to the dungeon" << std::endl;
            }
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                oublietteer::Floor* floor = dungeon->getFloor(index);
                if (floor != nullptr)
                {
                    if (floor->addRoom(manual))
                    {
                        change = true;
                        std::cout << "Added room " << floor->getRoomCount()-1 << " of floor " << index << " (Manual mode: " << manual << ")" << std::endl;
                    }
                    else
                    {
                        std::cout << "Cannot add rooms while manually settling" << std::endl;
                    }
                }
                else
                {
                    std::cout << "No such floor " << index << "to add rooms on" << std::endl;
                }
            }
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    oublietteer::Floor* floor = dungeon->getFloor(index);
                    if (floor != nullptr)
                    {
                        if (floor->getIsManual())
                        {
                            if (floor->getRoomCount() != 0)
                            {
                                if (floor->settleRoom(floor->getRoom(floor->getRoomCount()-1)))
                                {
                                    change = true;
                                    std::cout << "Settling room " << floor->getRoomCount()-1 << " of floor " << index << std::endl;
                                }
                                else
                                {
                                    std::cout << "Settled room " << floor->getRoomCount()-1 << " of floor " << index << std::endl;
                                }
                            }
                            else
                            {
                                std::cout << "No rooms to settle in floor " << index << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Cannot settle rooms outside of manual mode" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "No such floor " << index << " to settle rooms in" << std::endl;
                    }
                }
                else
                {
                    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::I)) || ((change) && (automatic) && (index >= 0)))
                    {
                        if (change)
                        {
                            oublietteer::Floor* floor = dungeon->getFloor(index);
                            if (floor != nullptr)
                            {
                                change = false;
                                delete sprite;
                                delete texture;
                                delete image;
                                image = floor->getImage();
                                texture = new sf::Texture();
                                texture->loadFromImage(*image);
                                sprite = new sf::Sprite();
                                sprite->setTexture(*texture);
                                sprite->setOrigin(sf::Vector2f(texture->getSize())*0.5f);
                                sprite->setPosition(sf::Vector2f(window->getSize())*0.5f);
                                std::cout << "Got image for floor " << index << std::endl;
                            }
                            else
                            {
                                std::cout << "No such floor " << index << " to get an image for" << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "No changes to get a new image for" << std::endl;
                        }
                    }
                    else
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                        {
                            for (unsigned int i = static_cast<unsigned int>(sf::Keyboard::Num0); i <= static_cast<unsigned int>(sf::Keyboard::Num9); ++i)
                            {
                                if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
                                {
                                    index = static_cast<int>(i-static_cast<unsigned int>(sf::Keyboard::Num0));
                                    change = true;
                                    if (dungeon->createFloor(index))
                                    {
                                        std::cout << "Created floor " << index << std::endl;
                                    }
                                    else
                                    {
                                        std::cout << "Floor " << index << " exists" << std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        window->clear(sf::Color::White);
        if (sprite != nullptr)
        {
            window->draw(*sprite);
        }
        window->display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window->close();
        }
    }
    if (image != nullptr)
    {
        image->saveToFile("image.png");
    }
    delete sprite;
    delete texture;
    delete image;
    delete window;
    delete dungeon;
    std::cout << "Bye!" << std::endl;
    arguments.clear();
    return 0;
}
