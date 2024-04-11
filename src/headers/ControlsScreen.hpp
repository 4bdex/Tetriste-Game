#pragma once
#include <SFML/Graphics.hpp>
#include <MainMenuScreen.hpp>
#include <iostream>
using namespace sf;

class ControlsScreen
{
public:
    ControlsScreen(RenderWindow *window);
    void render();
    void run();

private:
    RenderWindow *window;
    sf::Font font;
};