#include "headers/Game.hpp"

void Game::initVariables(RenderWindow *window)
{
    this->window = window;

    if (!font.loadFromFile("assets/fonts/sansation.ttf"))
    {
        std::cout << "Error loading font" << endl;
    }
}
Game::Game(RenderWindow *window, int Difficulty)
{
    initVariables(window);
    board = new GameBoard(Difficulty);
}
Game::Game(RenderWindow *window, bool isLoaded)
{
    initVariables(window);
    if (isLoaded)
    {
        board = new GameBoard(true);
    }
}
Game::~Game()
{
    delete window;
}
void Game::run()
{
    while (window->isOpen())
    {

        int gameState = board->checkMatches();
        render();

        update();
        if (gameState != 0)
        {
            render(); // this renders the last inserted Piece
            // the window should wait for 2 seconds before showing the game over screen
            drawGameOver();
            if (gameState == 1)
            {
                (new GameOver(window, true, board->getScore(), board->getPiecePool()))->run();
            }
            else if (gameState == -1)
            {
                (new GameOver(window, false, board->getScore(), board->getPiecePool()))->run();
            }
            board->~GameBoard();
        }
    }
}

void Game::drawScore()
{
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + to_string(board->getScore()));
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(50, 50); // Adjust position as needed
    window->draw(scoreText);
}
void Game::drawDifficulty()
{
    Text difficultyText;
    difficultyText.setFont(font);
    string difficulty;
    if (board->getPiecePool() == 4)
    {
        difficulty = "Easy";
    }
    else if (board->getPiecePool() == 5)
    {
        difficulty = "Medium";
    }
    else
    {
        difficulty = "Hard";
    }
    difficultyText.setString("Difficulty: " + difficulty);
    difficultyText.setCharacterSize(25);
    difficultyText.setFillColor(Color::Black);
    difficultyText.setPosition(50, 100);
    window->draw(difficultyText);
}
void Game::drawPlateSize()
{
    Text plateSizeText;
    plateSizeText.setFont(font);
    plateSizeText.setString("Pieces: " + to_string(board->getSize()));
    plateSizeText.setCharacterSize(25);
    plateSizeText.setFillColor(Color::Black);
    // center size text in the window on top
    plateSizeText.setPosition(window->getSize().x / 2 - plateSizeText.getLocalBounds().width / 2, 50);
    window->draw(plateSizeText);
}
void Game::drawQueue()
{
    // top right corner, it should leave 50 pixels from the right side, it has 4 Pieces each piece is 100 pixels width
    int startX = window->getSize().x - 50 - 100 * 4;
    int startY = 100;
    const int spacing = 100;

    // print Incoming pieces in the windows above queue
    Text text;
    text.setFont(font);
    text.setString("<- Incoming Pieces");
    text.setCharacterSize(25);
    text.setFillColor(Color::Black);
    text.setPosition(startX + 20, 50);
    window->draw(text);

    Piece *piece = board->incomingPieces->getFront();
    while (piece != nullptr)
    {

        // Draw the shape with its color
        switch (piece->shape)
        {
        case PShape::SQUARE:
        {
            window->draw(ShapeLibrary::Square(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::CIRCLE:
        {
            window->draw(ShapeLibrary::Circle(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::TRIANGLE:
        {
            window->draw(ShapeLibrary::Triangle(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::DIAMOND:
        {
            window->draw(ShapeLibrary::Diamond(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::HEXAGON:
        {
            window->draw(ShapeLibrary::Hexagon(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::STAR:
        {
            window->draw(ShapeLibrary::Star(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        }
        piece = piece->next;
        startX += spacing;
    }
}
void Game::drawPlate()
{
    // center the plate of 15 Pieces each piece is 75 pixels width
    int startX = window->getSize().x / 11;
    int startY = window->getSize().y - 200;
    const int spacing = 100;

    // Define the spacing between shapes

    Piece *piece = board->getHead();
    for (int i = 0; i < board->getSize(); i++)
    {
        // Draw the shape with its color
        switch (piece->shape)
        {
        case PShape::SQUARE:
        {
            window->draw(ShapeLibrary::Square(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::CIRCLE:
        {
            window->draw(ShapeLibrary::Circle(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::TRIANGLE:
        {
            window->draw(ShapeLibrary::Triangle(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::DIAMOND:
        {
            window->draw(ShapeLibrary::Diamond(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::HEXAGON:
        {
            window->draw(ShapeLibrary::Hexagon(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        case PShape::STAR:
        {
            window->draw(ShapeLibrary::Star(startX, startY, ShapeLibrary::getColor(static_cast<int>(piece->color))));
            break;
        }
        }
        piece = piece->next;
        startX += spacing;
    }
}
void Game::drawChoicePicker()
{
    Text text;
    text.setFont(font);
    text.setString("Choose:");
    text.setCharacterSize(25);
    text.setFillColor(Color::Black);
    // center the text in the window
    text.setPosition(50, 150);
    window->draw(text);
    // center Shape picker in the window under choose text
    int startX = 50;
    int startY = 200;

    switch (selectedShapeIndex)
    {
    case 0:
    {
        window->draw(ShapeLibrary::Square(startX, startY, ShapeLibrary::getColor(selectedColorIndex)));
        break;
    }
    case 1:
    {
        window->draw(ShapeLibrary::Diamond(startX, startY, ShapeLibrary::getColor(selectedColorIndex)));
        break;
    }
    case 2:
    {
        window->draw(ShapeLibrary::Circle(startX, startY, ShapeLibrary::getColor(selectedColorIndex)));
        break;
    }
    case 3:
    {
        window->draw(ShapeLibrary::Triangle(startX, startY, ShapeLibrary::getColor(selectedColorIndex)));
        break;
    }
    case 4:
    {
        window->draw(ShapeLibrary::Hexagon(startX, startY, ShapeLibrary::getColor(selectedColorIndex)));
        break;
    }
    case 5:
    {
        window->draw(ShapeLibrary::Star(startX, startY, ShapeLibrary::getColor(selectedColorIndex)));
        break;
    }
    }
}
// Splash game Over text in center of the window for 2 seconds
void Game::drawGameOver()
{
    // black background with 50% opacity
    RectangleShape background(Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(Color(0, 0, 0, 128));
    window->draw(background);

    Text text;
    text.setFont(font); // Assuming 'font' is a loaded font
    text.setString("Game Over");
    text.setCharacterSize(80);                // Increased font size
    text.setFillColor(Color(255, 165, 0));    // Changed text color to orange
    text.setStyle(Text::Bold | Text::Italic); // Applied bold and italic styles
    // Center the text in the window
    text.setPosition(window->getSize().x / 2 - text.getLocalBounds().width / 2, window->getSize().y / 2 - text.getLocalBounds().height / 2);

    // Add an outline to the text
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(2);

    // Apply a shadow effect to the text
    text.setOutlineColor(Color(0, 0, 0, 150)); // Semi-transparent black
    text.move(2, 2);                           // Move the shadow text slightly down and to the right

    window->draw(text);
    window->display();
    sleep(seconds(2));
}
void Game::handleButtons()
{
    static Clock clock;
    const Time delayDuration = milliseconds(300);
    // pull events
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            (new PauseScreen(window, board))->run();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if (clock.getElapsedTime() >= delayDuration)
            {
                clock.restart();
                board->insert(true, board->incomingPieces->dequeue());
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            if (clock.getElapsedTime() >= delayDuration)
            {
                clock.restart();
                board->insert(false, board->incomingPieces->dequeue());
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            if (clock.getElapsedTime() >= delayDuration)
            {
                clock.restart();
                // Change selected shape
                selectedShapeIndex++;
                if (selectedShapeIndex >= board->getPiecePool())
                    selectedShapeIndex = 0;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            if (clock.getElapsedTime() >= delayDuration)
            {
                // Change selected color
                clock.restart();
                selectedColorIndex++;
                if (selectedColorIndex >= board->getPiecePool())
                    selectedColorIndex = 0;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            if (clock.getElapsedTime() >= delayDuration)
            {
                clock.restart();
                int size = board->getSize();
                board->shiftByShape(false, static_cast<PShape>(selectedShapeIndex)); // Shift by shape right
                board->checkMatches();
                if (size != board->getSize())
                {
                    board->setScore(board->getScore() + 20); // Add 20 points as bonus
                    triggerBonusText();
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Q))
        {
            if (clock.getElapsedTime() >= delayDuration)
            {
                clock.restart();
                int size = board->getSize();
                board->shiftByShape(true, static_cast<PShape>(selectedShapeIndex)); // Shift by shape left
                board->checkMatches();
                if (size != board->getSize())
                {
                    board->setScore(board->getScore() + 20); // Add 20 points as bonus
                    triggerBonusText();
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::C))
        {
            if (clock.getElapsedTime() >= delayDuration)
            {
                clock.restart();
                int size = board->getSize();
                board->shiftByColor(false, static_cast<PColor>(selectedColorIndex)); // Shift by Color right
                board->checkMatches();
                if (size != board->getSize())
                {
                    board->setScore(board->getScore() + 20); // Add 20 points as bonus
                    triggerBonusText();
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            if (clock.getElapsedTime() >= delayDuration)
            {
                clock.restart();
                int size = board->getSize();
                board->shiftByColor(true, static_cast<PColor>(selectedColorIndex)); // Shift by Color left
                board->checkMatches();
                if (size != board->getSize())
                {
                    board->setScore(board->getScore() + 20); // Add 20 points as bonus
                    triggerBonusText();
                }
            }
        }
    }
}
void Game::handleBonusText()
{
    if (displayBonus)
    {
        window->draw(bonusText);
        window->display();
        if (bonusDisplayTimer.getElapsedTime().asSeconds() >= 2.0f)
        {
            displayBonus = false;        // Stop displaying bonus text
            fadingOut = true;            // Start fading out
            bonusFadeOutTimer.restart(); // Restart the fade-out timer
        }
    }

    if (fadingOut)
    {
        float alpha = 255 - (bonusFadeOutTimer.getElapsedTime().asSeconds() / 1.0f * 255);
        if (alpha < 0)
            alpha = 0;
        bonusText.setFillColor(Color(0, 255, 0, static_cast<Uint8>(alpha)));

        if (bonusFadeOutTimer.getElapsedTime().asSeconds() >= 1.0f)
        {
            fadingOut = false; // Stop fading out
        }
    }
}
void Game::triggerBonusText()
{
    displayBonus = true;
    fadingOut = false;
    bonusDisplayTimer.restart();
    bonusFadeOutTimer.restart();
    bonusText.setFont(font);
    bonusText.setStyle(Text::Bold | Text::Italic);
    bonusText.setString("+20 bonus");
    bonusText.setCharacterSize(30);
    bonusText.setFillColor(Color::Green);
    // in front of score text
    bonusText.setPosition(250, 50);
}

void Game::update()
{
    handleButtons();
    handleBonusText();
}
void Game::render()
{
    // Draw game objects
    window->clear(Color::White);
    drawScore();
    drawPlate();
    drawQueue();
    drawChoicePicker();
    drawDifficulty();
    drawPlateSize();
    window->display();
}