#include "color.hpp"
#include <iostream>
#include <string>
#include <sstream>
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

std::string Color::toString() const
{
    std::ostringstream is;
    is << red << " " << green << " " << blue;
    return is.str();
}
