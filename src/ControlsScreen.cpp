#include "headers/ControlsScreen.hpp"

ControlsScreen::ControlsScreen(RenderWindow *window) : window(window)
{
  if (!font.loadFromFile("assets/fonts/sansation.ttf"))
  {
    std::cout << "Error loading font" << std::endl;
  }
}

void ControlsScreen::render(){
    window->clear(Color::White);
    // Title text
    Text titleText;
    titleText.setFont(font);
    titleText.setString("Controls");
       titleText.setCharacterSize(60);
    titleText.setStyle(Text::Bold | Text::Italic);
    titleText.setFillColor(Color::Black);
    titleText.setPosition(window->getSize().x / 2 - titleText.getLocalBounds().width / 2, window->getSize().y / 8);
           // Add an outline to the text
    titleText.setOutlineColor(Color::Yellow);
    titleText.setOutlineThickness(2);

    // Apply a shadow effect to the text
    titleText.setOutlineColor(Color(0, 0, 0, 150)); // Semi-transparent black
    titleText.move(2, 2); // Move the shadow text slightly down and to the right
    window->draw(titleText);

    // Control text
    // left arrow
    Text leftArrowText;
    leftArrowText.setFont(font);
    leftArrowText.setString("Left Arrow: Insert Piece on the Left");
    leftArrowText.setCharacterSize(30);
    leftArrowText.setFillColor(Color::Black);
    leftArrowText.setPosition(window->getSize().x / 3, window->getSize().y / 8 + 100);

    // right arrow
    Text rightArrowText;
    rightArrowText.setFont(font);
    rightArrowText.setString("Right Arrow: Insert Piece on the Right");
    rightArrowText.setCharacterSize(30);
    rightArrowText.setFillColor(Color::Black);
    rightArrowText.setPosition(window->getSize().x / 3, window->getSize().y / 8 + 150);

    // up arrow
    Text upArrowText;
    upArrowText.setFont(font);
    upArrowText.setString("Up Arrow: Choose Piece Shape");
    upArrowText.setCharacterSize(30);
    upArrowText.setFillColor(Color::Black);
    upArrowText.setPosition(window->getSize().x / 3, window->getSize().y / 8 + 200);

    // down arrow
    Text downArrowText;
    downArrowText.setFont(font);
    downArrowText.setString("Down Arrow: Choose Piece Color");
    downArrowText.setCharacterSize(30);
    downArrowText.setFillColor(Color::Black);
    downArrowText.setPosition(window->getSize().x / 3, window->getSize().y / 8 + 250);

    // Q key
    Text qKeyText;
    qKeyText.setFont(font);
    qKeyText.setString("Q: Shift Pieces by Chosen Shape to left");
    qKeyText.setCharacterSize(30);
    qKeyText.setFillColor(Color::Black);
    qKeyText.setPosition(window->getSize().x / 3, window->getSize().y / 8 + 300);
    
    // s key
    Text sKeyText;
    sKeyText.setFont(font);
    sKeyText.setString("S: Shift Pieces by Chosen Shape to right");
    sKeyText.setCharacterSize(30);
    sKeyText.setFillColor(Color::Black);
    sKeyText.setPosition(window->getSize().x / 3, window->getSize().y / 8 + 350);

    // D key
    Text dKeyText;
    dKeyText.setFont(font);
    dKeyText.setString("D: Shift Pieces by Chosen Color to left");
    dKeyText.setCharacterSize(30);
    dKeyText.setFillColor(Color::Black);
    dKeyText.setPosition(window->getSize().x / 3, window->getSize().y / 8 + 400);

    // C key
    Text cKeyText;
    cKeyText.setFont(font);
    cKeyText.setString("C: Shift Pieces by Chosen Color to right");
    cKeyText.setCharacterSize(30);
    cKeyText.setFillColor(Color::Black);
    cKeyText.setPosition(window->getSize().x / 3, window->getSize().y / 8 + 450);

    // Esc key
    Text escKeyText;
    escKeyText.setFont(font);
    escKeyText.setString("Esc: Pause Game");
    escKeyText.setCharacterSize(30);
    escKeyText.setFillColor(Color::Black);
    escKeyText.setPosition(window->getSize().x / 3, window->getSize().y / 8 + 500);

// Press any key to continue
    Text continueText;
    continueText.setFont(font);
    continueText.setCharacterSize(20);
    continueText.setFillColor(Color::Black);
    continueText.setString("Press any key to continue");
    continueText.setPosition(window->getSize().x / 2 - continueText.getLocalBounds().width / 2,
                              window->getSize().y - 100);

    window->draw(continueText);

    window->draw(leftArrowText);
    window->draw(rightArrowText);
    window->draw(upArrowText);
    window->draw(downArrowText);
    window->draw(qKeyText);
    window->draw(sKeyText);
    window->draw(dKeyText);
    window->draw(cKeyText);
    window->draw(escKeyText);

    window->display();
}

void ControlsScreen::run(){
    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window->close();
            }
            if (event.type == Event::KeyPressed)
            {
                (new MainMenu(window))->run();
            }
        }
        render();
    }
}