
// Author: Pierce Brooks

#ifndef OUBLIETTEER_FLOOR_HPP
#define OUBLIETTEER_FLOOR_HPP

#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace oublietteer
{
    class Room;
    class Oubliette;

    class Floor
    {
        public:
            Floor(Oubliette* owner, int identifier);
            virtual ~Floor();
            Oubliette* getOwner() const;
            int getIdentifier() const;
            const sf::Vector2u& getSize() const;
            sf::IntRect getBounds() const;
            unsigned int getRoomCount() const;
            bool addRoom(bool manual = false);
            Room* getRoom(unsigned index) const;
            bool settleRoom(Room* room);
            virtual sf::Vector2u getRoomSize() const;
            virtual sf::Color getRoomColor() const;
            sf::Image* getImage() const;
        private:
            sf::Vector2u size;
            bool isManual;
            Oubliette* owner;
            int identifier;
            std::vector<Room*> rooms;
    };
}

#endif
