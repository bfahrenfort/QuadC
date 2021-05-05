#include "color.h"
#include <iostream>
#include "quirk.hpp"

Color::Color()
{
    red = green = blue = 0;
}
Color::Color(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
}
Color::Color(const Color& color)
{
    red = color.red;
    green = color.green;
    blue = color.blue;
}

void Color::printColor()
{
    std::cout << red << ' ' << green << ' ' << blue EL;
}
