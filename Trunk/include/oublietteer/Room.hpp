
// Author: Pierce Brooks

#ifndef OUBLIETTEER_ROOM_HPP
#define OUBLIETTEER_ROOM_HPP

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace oublietteer
{
    class Floor;

    class Room
    {
        public:
            Room(Floor* owner, unsigned int index, const sf::Vector2u& size, float position);
            virtual ~Room();
            Floor* getOwner() const;
            unsigned int getIndex() const;
            const sf::Vector2u& getSize() const;
            const sf::Vector2i& getPosition() const;
            sf::IntRect getBounds() const;
        private:
            Floor* owner;
            unsigned int index;
            sf::Vector2u size;
            sf::Vector2i position;
    };
}

#endif
