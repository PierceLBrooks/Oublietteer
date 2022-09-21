
// Author: Pierce Brooks

#include <oublietteer/Pixel.hpp>

oublietteer::Pixel::Pixel() :
    r(0),
    g(0),
    b(0),
    a(0)
{
    
}

oublietteer::Pixel::Pixel(const Pixel& pixel) :
    r(pixel.getRed()),
    g(pixel.getGreen()),
    b(pixel.getBlue()),
    a(pixel.getAlpha())
{
    
}

oublietteer::Pixel::Pixel(Uint32 color) :
    r(color&(255)),
    g(color&(255<<8)),
    b(color&(255<<16)),
    a(color&(255<<24))
{
    
}

oublietteer::Pixel::Pixel(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) :
    r(red),
    g(green),
    b(blue),
    a(alpha)
{
    
}

oublietteer::Pixel oublietteer::Pixel::getInversion(bool alpha) const
{
    return Pixel(255-r,255-g,255-b,((alpha)?255-a:a));
}

oublietteer::Uint32 oublietteer::Pixel::getColor() const
{
    Uint32 color = 0;
    color |= ((Uint32)r);
    color |= ((Uint32)g)<<8;
    color |= ((Uint32)b)<<16;
    color |= ((Uint32)a)<<24;
    return color;
}

oublietteer::Uint8 oublietteer::Pixel::getRed() const
{
    return r;
}

oublietteer::Uint8 oublietteer::Pixel::getGreen() const
{
    return g;
}

oublietteer::Uint8 oublietteer::Pixel::getBlue() const
{
    return b;
}

oublietteer::Uint8 oublietteer::Pixel::getAlpha() const
{
    return a;
}

bool oublietteer::Pixel::compare(const Pixel& other) const
{
    if ((getRed() == other.getRed()) && (getGreen() == other.getGreen()) && (getBlue() == other.getBlue()) && (getAlpha() == other.getAlpha()))
    {
        return true;
    }
    return false;
}

oublietteer::Pixel oublietteer::Pixel::TRANSPARENT = Pixel(0,0,0,0);

oublietteer::Pixel oublietteer::Pixel::BLACK = Pixel(0,0,0);

oublietteer::Pixel oublietteer::Pixel::WHITE = Pixel(255,255,255);

oublietteer::Pixel oublietteer::Pixel::RED = Pixel(255,0,0);

oublietteer::Pixel oublietteer::Pixel::GREEN = Pixel(0,255,0);

oublietteer::Pixel oublietteer::Pixel::BLUE = Pixel(0,0,255);

oublietteer::Pixel oublietteer::Pixel::CYAN = Pixel(0,255,255);

oublietteer::Pixel oublietteer::Pixel::MAGENTA = Pixel(255,0,255);

oublietteer::Pixel oublietteer::Pixel::YELLOW = Pixel(255,255,0);
