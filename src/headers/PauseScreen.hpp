#pragma once
#include <SFML/Graphics.hpp>
#include "GameBoard.hpp"
#include "MainMenuScreen.hpp"

using namespace sf;

enum class PauseMenuOption
{
    ContinueGame,
    SaveGame,
    Quit,
};

class PauseScreen
{
public:
    // Constructor to initialize font and menu options
    PauseScreen(RenderWindow *window, GameBoard *game);

    // Function to render the pause screen
    void render();

    // Function to navigate through the pause screen options
    void navigate(int delta);

    // Function to get the selected option
    PauseMenuOption getSelectedOption() const;

    // Function to run the pause screen loop
    void run();

private:

    RenderWindow *window;
    GameBoard *game;
    sf::Font font;
    std::vector<std::string> options = {"Continue", "Save Game", "Quit"};
    int selectedOption;
};