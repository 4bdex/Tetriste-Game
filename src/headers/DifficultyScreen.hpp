#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.hpp"


enum class DifficultyOption {
    EASY,
    MEDIUM,
    HARD
};

class DifficultyMenu {
public:
    // Constructor to initialize font and menu options
    DifficultyMenu(RenderWindow* window) ;

    // Function to render the menu
    void render() ;
    
    // Function to handle arrow key navigation
    void navigate(int delta);
    // Function to get the currently selected option
    DifficultyOption getSelectedOption() const ;

    // Function to run the main menu loop
    void run();

private:
    RenderWindow *window;
    sf::Font font;
    std::vector<std::string> options = {"Easy", "Medium","Hard"};
    std::vector<std::string> optionsDescription = {"Play with 4 Colors and 4 Shapes", "Play with 5 Colors and 5 Shapes","Play with 6 Colors and 6 Shapes"};
    int selectedOption;
};