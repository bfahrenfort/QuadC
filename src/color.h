#ifndef QUIRKTYPER_COLOR_H
#define QUIRKTYPER_COLOR_H

class Color
{
public:
    Color();
    Color(int r, int g, int b);
    Color(const Color& color);
    void printColor();

private:
    int red, green, blue;
};

#endif //QUIRKTYPER_COLOR_H
