#include<iostream>
#include "headers/MainMenuScreen.hpp"


int main()
{
     int windowWidth = VideoMode::getDesktopMode().width, windowHeight = VideoMode::getDesktopMode().height;
     sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow *window;
    if (!VideoMode::getFullscreenModes().empty())
        window = new RenderWindow(VideoMode::getDesktopMode(), "Tetriste" , Style::Fullscreen, settings);
    else
        window = new RenderWindow(VideoMode::getDesktopMode(), "Tetriste",Style::Default ,settings); 

    window->setFramerateLimit(60);
   
    // full screen window
    // RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Tetriste", Style::Fullscreen);
    MainMenu menu(window);
    // Run menu loop
    menu.run();
}

