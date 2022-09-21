
// Author: Pierce Brooks

#ifndef OUBLIETTEER_BITMAP_HPP
#define OUBLIETTEER_BITMAP_HPP

#include <oublietteer/Pixel.hpp>
#include <oublietteer/Vector2.hpp>
#include <oublietteer/MathUtilities.hpp>

namespace oublietteer
{
    class Bitmap
    {
        public:
            Bitmap();
            Bitmap(const Bitmap& bitmap);
            Bitmap(const Vector2u& size, const Pixel& fill = Pixel::TRANSPARENT);
            Bitmap(unsigned int width, unsigned int height, const Pixel& fill = Pixel::TRANSPARENT);
            virtual ~Bitmap();
            void copy(const Bitmap& bitmap);
            void copy(const Bitmap& bitmap, const Vector2u& destination);
            void create(const Vector2u& size, const Pixel& fill = Pixel::TRANSPARENT);
            void create(unsigned int width, unsigned int height, const Pixel& fill = Pixel::TRANSPARENT);
            void setPixel(const Vector2u& position, const Pixel& pixel);
            void setPixel(unsigned int x, unsigned int y, const Pixel& pixel);
            Pixel getPixel(const Vector2u& position) const;
            Pixel getPixel(unsigned int x, unsigned int y) const;
            const Uint32* getPixels() const;
            const Vector2u& getSize() const;
        private:
            Uint32* pixels;
            Vector2u size;
    };
}

#endif // OUBLIETTEER_BITMAP_HPP

