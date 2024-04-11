#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameBoard.hpp"
#include "Game.hpp"
#include "MainMenuScreen.hpp"
using namespace sf;


enum class GameOverOption {
  ReplayGame,
  MainMenu,
  SaveScore
};

class GameOver {
public:
  GameOver(RenderWindow* window, bool isWin, int score, int difficulty);
  void render();
  void drawSaveScore();
  void navigate(int delta);
  GameOverOption getSelectedOption() const ;
        // Function to run the main menu loop
    void run() ;

private:
  RenderWindow* window;
  sf::Font font;
  std::vector<std::string> options = {"Try Again", "Save Score","Main Menu"};
  bool isWin;
  int score;
  int difficulty;
  int selectedOption;
};
