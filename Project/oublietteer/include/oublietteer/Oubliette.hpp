
// Author: Pierce Brooks

#ifndef OUBLIETTEER_OUBLIETTE_HPP
#define OUBLIETTEER_OUBLIETTE_HPP

#include <map>
#include <oublietteer/Bounds.hpp>
#include <oublietteer/Vector2.hpp>
#include <oublietteer/Random.hpp>

namespace oublietteer
{
    class Floor;

    class Oubliette
    {
        public:
            Oubliette(const Vector2u& size, unsigned int seed = 0);
            virtual ~Oubliette();
            bool createFloor(int identifier);
            Floor* getFloor(int identifier) const;
            const Vector2u& getSize() const;
            Bounds<int> getBounds() const;
            Random* getRandom() const;
        private:
            Random* random;
            Vector2u size;
            std::map<int, Floor*> floors;
    };
}

#endif
