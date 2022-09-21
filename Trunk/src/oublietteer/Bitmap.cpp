
// Author: Pierce Brooks

#include <oublietteer/Bitmap.hpp>

oublietteer::Bitmap::Bitmap() :
    pixels(nullptr)
{
    create(1,1);
}

oublietteer::Bitmap::Bitmap(const Bitmap& bitmap) :
    pixels(nullptr)
{
    create(bitmap.getSize());
    copy(bitmap);
}

oublietteer::Bitmap::Bitmap(const Vector2u& size, const Pixel& fill) :
    pixels(nullptr)
{
    create(size,fill);
}

oublietteer::Bitmap::Bitmap(unsigned int width, unsigned int height, const Pixel& fill) :
    pixels(nullptr)
{
    create(width,height,fill);
}

oublietteer::Bitmap::~Bitmap()
{
    delete[] pixels;
}

void oublietteer::Bitmap::copy(const Bitmap& bitmap)
{
    if ((size.x != bitmap.getSize().x) || (size.y != bitmap.getSize().y))
    {
        create(bitmap.getSize());
    }
    for (unsigned int x = 0; x != bitmap.getSize().x; ++x)
    {
        for (unsigned int y = 0; y != bitmap.getSize().y; ++y)
        {
            setPixel(x,y,bitmap.getPixel(x, y));
        }
    }
}

void oublietteer::Bitmap::copy(const Bitmap& bitmap, const Vector2u& destination)
{
    for (unsigned int x = 0; x != bitmap.getSize().x; ++x)
    {
        if (x == size.x)
        {
            break;
        }
        for (unsigned int y = 0; y != bitmap.getSize().y; ++y)
        {
            if (y == size.y)
            {
                break;
            }
            setPixel(x+destination.x,y+destination.y,bitmap.getPixel(x, y));
        }
    }
}

void oublietteer::Bitmap::create(const Vector2u& size, const Pixel& fill)
{
    create(size.x,size.y,fill);
}

void oublietteer::Bitmap::create(unsigned int width, unsigned int height, const Pixel& fill)
{
    unsigned int size = width*height;
    int color = fill.getColor();
    this->size = Vector2u(width,height);
    delete[] pixels;
    pixels = new Uint32[size];
    for (unsigned int i = 0; i != size; ++i)
    {
        pixels[i] = color;
    }
}

void oublietteer::Bitmap::setPixel(const Vector2u& position, const Pixel& pixel)
{
    setPixel(position.x,position.y,pixel);
}

void oublietteer::Bitmap::setPixel(unsigned int x, unsigned int y, const Pixel& pixel)
{
    pixels[(y*size.x)+x] = pixel.getColor();
}

oublietteer::Pixel oublietteer::Bitmap::getPixel(const Vector2u& position) const
{
    return getPixel(position.x,position.y);
}

oublietteer::Pixel oublietteer::Bitmap::getPixel(unsigned int x, unsigned int y) const
{
    return Pixel(pixels[(y*size.x)+x]);
}

const oublietteer::Uint32* oublietteer::Bitmap::getPixels() const
{
    return pixels;
}

const oublietteer::Vector2u& oublietteer::Bitmap::getSize() const
{
    return size;
}
