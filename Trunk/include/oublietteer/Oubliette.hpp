
// Author: Pierce Brooks

#ifndef OUBLIETTEER_OUBLIETTE_HPP
#define OUBLIETTEER_OUBLIETTE_HPP

#include <map>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <oublietteer/Random.hpp>

namespace oublietteer
{
    class Floor;

    class Oubliette
    {
        public:
            Oubliette(const sf::Vector2u& size, unsigned int seed = 0);
            virtual ~Oubliette();
            bool createFloor(int identifier);
            Floor* getFloor(int identifier) const;
            const sf::Vector2u& getSize() const;
            sf::IntRect getBounds() const;
            Random* getRandom() const;
        private:
            Random* random;
            sf::Vector2u size;
            std::map<int, Floor*> floors;
    };
}

#endif
