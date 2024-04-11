#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameBoard.hpp"
#include "MainMenuScreen.hpp"
using namespace sf;
// Class to display top 10 scores (leaderboard)

class LeaderBoard
{
public:
    // Constructor to initialize font and menu options
    LeaderBoard(RenderWindow *window);

    // Function to render the leaderboard
    void render();

    // Function to run the leaderboard loop
    void run();

private:
    RenderWindow *window;
    sf::Font font;
};