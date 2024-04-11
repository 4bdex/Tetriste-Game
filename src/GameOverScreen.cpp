#include "headers/GameOverScreen.hpp"

GameOver::GameOver(RenderWindow *window, bool isWin, int score,int difficulty) : window(window)
{
  if (!font.loadFromFile("assets/fonts/sansation.ttf"))
  {
    std::cout << "Error loading font" << std::endl;
  }
  selectedOption = 0;
  this->isWin = isWin;
  this->score = score;
  this->difficulty = difficulty;
}

void GameOver::render()
{

  window->clear(Color::White);
  
  
  // Game Over Text
  Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setCharacterSize(60);
  gameOverText.setStyle(Text::Bold | Text::Italic);
  if (isWin)
  {
    gameOverText.setString("You Win!");
    gameOverText.setFillColor(Color::Green);
  }
  else
  {
    gameOverText.setString("You Lose!");
    gameOverText.setFillColor(Color::Red);
  }
  gameOverText.setPosition(window->getSize().x / 2 - gameOverText.getLocalBounds().width / 2,
                           window->getSize().y / 4);

         // Add an outline to the text
    gameOverText.setOutlineColor(Color::Black);
    gameOverText.setOutlineThickness(2);

    // Apply a shadow effect to the text
    gameOverText.setOutlineColor(Color(0, 0, 0, 150)); // Semi-transparent black
    gameOverText.move(2, 2); // Move the shadow text slightly down and to the right


  // Score Text
  Text scoreText;
  scoreText.setFont(font);
  scoreText.setCharacterSize(30);
  scoreText.setFillColor(Color::Black);
  bool isHighScore = checkScore(score);
  if (!isHighScore)
  {
    options = {"Try Again", "Main Menu"};
    scoreText.setString("Your Score: " + std::to_string(score));
  }else{
     scoreText.setString("New Score: " + std::to_string(score));
  }
  scoreText.setPosition(window->getSize().x / 2 - scoreText.getLocalBounds().width / 2,
                        gameOverText.getPosition().y + gameOverText.getLocalBounds().height + 50);

  
  // Draw options
  for (int i = 0; i < options.size(); ++i)
  {
    Text option;
    option.setFont(font);
    option.setString(options[i]);
    option.setCharacterSize(30);
    option.setPosition(window->getSize().x / 2 - option.getLocalBounds().width / 2, scoreText.getPosition().y + scoreText.getLocalBounds().height + 50 + i * 50);
    option.setFillColor((i == selectedOption) ? Color::Red : Color::Black);
    window->draw(option);
  }

  // window->draw(background);
  window->draw(gameOverText);
  window->draw(scoreText);
  window->display();
}

void GameOver::navigate(int delta)
{
  selectedOption = (selectedOption + delta + options.size()) % options.size();
}

GameOverOption GameOver::getSelectedOption() const
{
  if (options.size() == 3 && selectedOption == 1)
  {
    return GameOverOption::SaveScore;
  }
  if (options.size() == 3 && selectedOption == 2)
  {
    return GameOverOption::MainMenu;
  }
  return static_cast<GameOverOption>(selectedOption);
}
// Function to run the main menu loop
void GameOver::run()
{
  while (window->isOpen())
  {
    sf::Event event;
    while (window->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window->close();
      }
      else if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Up)
        {
          navigate(-1);
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
          navigate(1);
        }
        else if (event.key.code == sf::Keyboard::Return)
        {
          GameOverOption selectedOption = getSelectedOption();
          // Handle selected option

          if (selectedOption == GameOverOption::ReplayGame)
          {
            (new Game(window, difficulty))->run();

          }
          else if (selectedOption == GameOverOption::MainMenu)
          {
            (new MainMenu(window))->run();
            
          }
          else if (selectedOption == GameOverOption::SaveScore)
          {
            drawSaveScore();
          }
        }
      }
    }

    // Render menu
    render();
  }
}
void GameOver::drawSaveScore()
{

  // Enter Name Text
  sf::Text enterNameText;
  enterNameText.setFont(font);
  enterNameText.setString("Enter Player Name:");
  enterNameText.setCharacterSize(30);
  enterNameText.setFillColor(sf::Color::Black);
  enterNameText.setPosition(window->getSize().x / 2 - enterNameText.getLocalBounds().width / 2, window->getSize().y / 2 - 60);

  // Input box rectangle 
  sf::RectangleShape inputBox(sf::Vector2f(200, 30));
  inputBox.setFillColor(sf::Color::White);
  inputBox.setOutlineColor(sf::Color::Black);
  inputBox.setOutlineThickness(2);
  inputBox.setPosition(window->getSize().x / 2 - inputBox.getLocalBounds().width / 2, window->getSize().y / 2);

  // Text for the input box
  sf::Text inputText;
  inputText.setFont(font);
  inputText.setCharacterSize(20);
  inputText.setFillColor(sf::Color::Black);
  inputText.setPosition(inputBox.getPosition().x + 5, inputBox.getPosition().y + 5);

  



  // display press enter to save score
  sf::Text promptText;
  promptText.setFont(font);
  promptText.setString("Press Enter to save score");
  promptText.setCharacterSize(20);
  promptText.setFillColor(sf::Color::Black);
  promptText.setPosition(window->getSize().x / 2 - promptText.getLocalBounds().width / 2, window->getSize().y / 2 + 40);

    Text errorText;
            errorText.setFont(font);
            errorText.setString("Please enter a name");
            errorText.setCharacterSize(20);
            errorText.setFillColor(Color::White);
            errorText.setPosition(window->getSize().x / 2 - errorText.getLocalBounds().width / 2, window->getSize().y / 2 + 80);

  sf::String playerName;
  while (window->isOpen())
  {
    sf::Event event;
    while (window->pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::Closed:
        window->close();
        break;
      case sf::Event::TextEntered:
        if (event.text.unicode < 128 && (isalpha(event.text.unicode) || isdigit(event.text.unicode)) && playerName.getSize() < 15)
        {
          playerName += static_cast<char>(event.text.unicode);
          inputText.setString(playerName);
        }
        else if (event.text.unicode == 8 && !playerName.isEmpty())
        { // Backspace
          playerName.erase(playerName.getSize() - 1, 1);
          inputText.setString(playerName);
        }
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Return)
        {
          if (!playerName.isEmpty())
          {
            // Save Score
            saveScore(score, playerName);
            (new LeaderBoard(window))->run();
          }
          else{
            errorText.setFillColor(Color::Red);
          }
        }
        break;
      default:
        break;
      }
    }

    window->clear(sf::Color::White);
    window->draw(enterNameText);
    window->draw(inputBox);  // Draw input box after prompt
    window->draw(inputText); // Draw input text after prompt
    window->draw(promptText);
    window->draw(errorText);
    window->display();
  }
}
