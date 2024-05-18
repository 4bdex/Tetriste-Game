#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "LeaderBoardScreen.hpp"
#include "DifficultyScreen.hpp"
#include "ControlsScreen.hpp"

enum class MainMenuOption {
    NewGame,
    ResumeGame,
    ViewScores,
    Controls,
    Quit
};

class MainMenu {
public:
    // Constructor to initialize font and menu options
    MainMenu(RenderWindow* window) ;

    // Function to render the menu
    void render() ;
    
    // Function to handle arrow key navigation
    void navigate(int delta);
    // Function to get the currently selected option
    MainMenuOption getSelectedOption() const ;

    // Function to run the main menu loop
    void run();

private:
    RenderWindow *window;
    sf::Font font;
    std::vector<std::string> options = {"New Game", "Resume Game", "Leaderboard","Controls", "Quit"};
    int selectedOption;
};