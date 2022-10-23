
// Author: Pierce Brooks

#ifndef OUBLIETTEER_ROOM_HPP
#define OUBLIETTEER_ROOM_HPP

#include <oublietteer/Bounds.hpp>
#include <oublietteer/Vector2.hpp>
#include <oublietteer/Random.hpp>
#include <vector>

namespace oublietteer
{
    class Floor;

    class Room
    {
        public:
            Room(Floor* owner, unsigned int index, const Vector2u& size, float direction);
            virtual ~Room();
            Floor* getOwner() const;
            unsigned int getIndex() const;
            const Vector2u& getSize() const;
            const Vector2i& getPosition() const;
            Vector2f getCenter() const;
            Bounds<int> getBounds() const;
            bool settle();
            void finish();
            Random* getRandom() const;
            std::pair<Room*, Vector2u> getNeighbor(unsigned int index) const;
            unsigned int getNeighborCount() const;
        private:
            friend Floor;
            void setPosition(const Vector2i& position);
            void setNeighbor(unsigned int index, Room* room, const Vector2u& position);
            Floor* owner;
            unsigned int index;
            Vector2u size;
            Vector2i position;
            Vector2f direction;
            std::vector<std::pair<Room*, Vector2u>> neighbors;
    };
}

#endif
