#include <string>

#ifndef QUIRKTYPER_COLOR_HPP
#define QUIRKTYPER_COLOR_HPP

class Color
{
public:
    Color();
    Color(int r, int g, int b);
    Color(const Color& color);
    void PrintColor();
    std::string ToString() const;

private:
    int red, green, blue;
};

#endif //QUIRKTYPER_COLOR_HPP
