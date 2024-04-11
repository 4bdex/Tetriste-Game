#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class ShapeLibrary
{
private:
    static constexpr float size = 85.0f;
    static constexpr float radius = size / 2.0f;
public:
    // Define static methods to create predefined shapes
    static RectangleShape Square(int x, int y, const Color &color);
    static CircleShape Circle(int x, int y, const Color &color);
    static ConvexShape Triangle(int x, int y, const Color &color);
    static ConvexShape Diamond(int x, int y, const Color &color);
    static ConvexShape Hexagon(int x, int y, const Color &color);
    static ConvexShape Star(int x, int y, const Color &color);

    // Method to get the right color for the shape
    static Color getColor(int color);
};
