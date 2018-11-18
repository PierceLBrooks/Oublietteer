
// Author: Pierce Brooks

#ifndef OUBLIETTEER_ROOM_HPP
#define OUBLIETTEER_ROOM_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <oublietteer/Random.hpp>

namespace oublietteer
{
    class Floor;

    class Room
    {
        public:
            Room(Floor* owner, unsigned int index, const sf::Vector2u& size, float direction);
            virtual ~Room();
            Floor* getOwner() const;
            unsigned int getIndex() const;
            const sf::Vector2u& getSize() const;
            const sf::Vector2i& getPosition() const;
            sf::Vector2f getCenter() const;
            sf::IntRect getBounds() const;
            bool settle();
            Random* getRandom() const;
        private:
            friend Floor;
            void setPosition(const sf::Vector2i& position);
            Floor* owner;
            unsigned int index;
            sf::Vector2u size;
            sf::Vector2i position;
            sf::Vector2f direction;
    };
}

#endif
