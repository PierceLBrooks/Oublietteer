
// Author: Pierce Brooks

#ifndef OUBLIETTEER_PIXEL_HPP
#define OUBLIETTEER_PIXEL_HPP

#include <oublietteer/MathUtilities.hpp>

namespace oublietteer
{
    class Pixel
    {
        public:
            Pixel();
            Pixel(const Pixel& pixel);
            Pixel(Uint32 color);
            Pixel(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);
            Pixel getInversion(bool alpha = false) const;
            Uint32 getColor() const;
            Uint8 getRed() const;
            Uint8 getGreen() const;
            Uint8 getBlue() const;
            Uint8 getAlpha() const;
            bool compare(const Pixel& other) const;
            Uint8 r;
            Uint8 g;
            Uint8 b;
            Uint8 a;
            static Pixel TRANSPARENT;
            static Pixel BLACK;
            static Pixel WHITE;
            static Pixel RED;
            static Pixel GREEN;
            static Pixel BLUE;
            static Pixel CYAN;
            static Pixel MAGENTA;
            static Pixel YELLOW;
    };
}

#endif // OUBLIETTEER_PIXEL_HPP

