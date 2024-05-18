#include "headers/ShapeLibrary.hpp"

RectangleShape ShapeLibrary::Square(int x, int y, const Color &color)
{
    RectangleShape square(Vector2f(size, size));
    square.setPosition(x, y);
    square.setFillColor(color);
    return square;
}

CircleShape ShapeLibrary::Circle(int x, int y, const Color &color)
{
    CircleShape circle(radius);
    circle.setPosition(x, y);
    circle.setFillColor(color);
    return circle;
}

ConvexShape ShapeLibrary::Triangle(int x, int y, const Color &color)
{
    ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, Vector2f(size / 2, 0)); 
    triangle.setPoint(1, Vector2f(0, size));     
    triangle.setPoint(2, Vector2f(size, size));
    triangle.setPosition(x, y);
    triangle.setFillColor(color);
    return triangle;
}

ConvexShape ShapeLibrary::Diamond(int x, int y, const Color &color)
{
    ConvexShape diamond;
    diamond.setPointCount(4);
    diamond.setPoint(0, Vector2f(size / 2, 0));
    diamond.setPoint(1, Vector2f(size, size / 2));
    diamond.setPoint(2, Vector2f(size / 2, size));
    diamond.setPoint(3, Vector2f(0, size / 2));
    diamond.setPosition(x, y);
    diamond.setFillColor(color);
    return diamond;
}
ConvexShape ShapeLibrary::Hexagon(int x, int y, const Color &color)
{
    ConvexShape hexagon;
    hexagon.setPointCount(6);
    hexagon.setPoint(0, Vector2f(size / 4, 0));
    hexagon.setPoint(1, Vector2f(3 * size / 4, 0));
    hexagon.setPoint(2, Vector2f(size, size / 2));
    hexagon.setPoint(3, Vector2f(3 * size / 4, size));
    hexagon.setPoint(4, Vector2f(size / 4, size));
    hexagon.setPoint(5, Vector2f(0, size / 2));
    hexagon.setPosition(x, y);
    hexagon.setFillColor(color);
    return hexagon;
}
ConvexShape ShapeLibrary::Star(int x, int y, const Color &color)
{
    ConvexShape star;
    star.setPointCount(10);
    star.setPoint(0, Vector2f(size / 2, 0));
    star.setPoint(1, Vector2f(3 * size / 5, 2 * size / 5));
    star.setPoint(2, Vector2f(size, size / 2));
    star.setPoint(3, Vector2f(3 * size / 5, 3 * size / 5));
    star.setPoint(4, Vector2f(size / 2, size));
    star.setPoint(5, Vector2f(2 * size / 5, 3 * size / 5));
    star.setPoint(6, Vector2f(0, size / 2));
    star.setPoint(7, Vector2f(2 * size / 5, 2 * size / 5));
    star.setPoint(8, Vector2f(size / 2, 0));
    star.setPoint(9, Vector2f(3 * size / 5, 2 * size / 5));
    star.setPosition(x, y);
    star.setFillColor(color);
    return star;
}

Color ShapeLibrary::getColor(int color)
{
    switch (color)
    {
    case 0:
        return Color::Blue;
    case 1:
        return Color::Yellow;
    case 2:
        return Color::Red;

    case 3:
        return Color::Green;
    case 4:
        return Color(128, 0, 128); // Purple
    case 5:
        return Color::Black;
    default:
        return Color::White;
    }
}
