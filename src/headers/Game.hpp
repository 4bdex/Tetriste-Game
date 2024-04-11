#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameBoard.hpp"
#include "ShapeLibrary.hpp"
#include "GameOverScreen.hpp"
#include "PauseScreen.hpp"
#include "Gamebot.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

// class that acts as the main game loop (engine)
class Game
{
private:
    RenderWindow *window;
    GameBoard *board;
    int selectedShapeIndex = 0; // Index of the selected shape
    int selectedColorIndex = 0; // Index of the selected Color
    int selectedOption = 0;     // Index of the selected option
    Font font;
    Event e;
    Text bonusText;
    Clock bonusDisplayTimer;
    Clock bonusFadeOutTimer;
    bool displayBonus = false;
    bool fadingOut = false;
    // Add variables for buttons
    // Add variables for font and text
    // methods
    void drawPlate();
    void handleBonusText();
    void drawQueue();
    void initVariables(RenderWindow *window);
    void drawScore();
    void drawChoicePicker();
    void drawDifficulty();
    void drawPlateSize();
    void drawGameOver();
     void triggerBonusText() ;


    // Add method to handle user input for buttons
    void handleButtons();

    // main game loop
    void update();
    // render game objects
    void render();

public:
    // constructor and destructor
    Game(RenderWindow *window, bool isLoaded = false);
    Game(RenderWindow *window, int Difficulty);
    ~Game();

    void run();
};
