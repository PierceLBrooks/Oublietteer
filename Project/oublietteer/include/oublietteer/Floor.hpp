
// Author: Pierce Brooks

#ifndef OUBLIETTEER_FLOOR_HPP
#define OUBLIETTEER_FLOOR_HPP

#include <vector>
#include <oublietteer/Bitmap.hpp>
#include <oublietteer/Bounds.hpp>
#include <oublietteer/Vector2.hpp>
#include <oublietteer/Random.hpp>

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
            const Vector2u& getSize() const;
            Bounds<int> getBounds() const;
            unsigned int getRoomCount() const;
            bool addRoom(bool manual = false);
            Room* getRoom(unsigned index) const;
            bool settleRoom(Room* room);
            virtual Vector2u getRoomSize() const;
            virtual Pixel getRoomColor() const;
            Bitmap* getImage() const;
            bool getIsManual() const;
            Random* getRandom() const;
        private:
            float getMagnitude(const Vector2f& target) const;
            float getDistance(const Vector2f& first, const Vector2f& last) const;
            Vector2u getRoomNeighborPosition(Room* first, Room* last) const;
            Vector2u size;
            bool isManual;
            Oubliette* owner;
            int identifier;
            std::vector<Room*> rooms;
    };
}

#endif
