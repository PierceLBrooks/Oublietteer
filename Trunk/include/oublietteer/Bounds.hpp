
// Author: Pierce Brooks

#ifndef OUBLIETTEER_BOUNDS_HPP
#define OUBLIETTEER_BOUNDS_HPP

#include <oublietteer/Vector2.hpp>

namespace oublietteer
{
    template <typename T>
    class Bounds
    {
        public:
            T x;
            T y;
            T width;
            T height;
            
            Bounds() : x(), y(), width(), height() {}
            Bounds(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {}
            Bounds(const Bounds& other) : x(other.x), y(other.y), width(other.width), height(other.height) {}
            template <typename U>
            explicit Bounds(const Bounds<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), width(static_cast<T>(other.width)), height(static_cast<T>(other.height)) {}
            
            bool contains(const Vector2<T>& point) const
            {
                if ((point.x >= x) && (point.y >= y) && (point.x < x+width) && (point.y < y+height))
                {
                    return true;
                }
                return false;
            }
            
            bool intersects(const Bounds& other) const
            {
                if ((contains(other.getNorthwest())) || (contains(other.getNortheast())) || (contains(other.getSouthwest())) || (contains(other.getSoutheast())) || (other.contains(getNorthwest())) || (other.contains(getNortheast())) || (other.contains(getSouthwest())) || (other.contains(getSoutheast())))
                {
                    return true;
                }
                return false;
            }
            
            Vector2<T> getNorthwest() const
            {
                return Vector2<T>(x, y);
            }
            
            Vector2<T> getNortheast() const
            {
                return Vector2<T>(x+width, y);
            }
            
            Vector2<T> getSouthwest() const
            {
                return Vector2<T>(x, y+height);
            }
            
            Vector2<T> getSoutheast() const
            {
                return Vector2<T>(x+width, y+height);
            }
    };
}

#endif // OUBLIETTEER_BOUNDS_HPP

