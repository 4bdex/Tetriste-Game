#include "headers/PauseScreen.hpp"

PauseScreen::PauseScreen(RenderWindow *window,GameBoard *game) : window(window), game(game)
{
    if (!font.loadFromFile("assets/fonts/sansation.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
    selectedOption = 0;
}

void PauseScreen::render()
{
    window->clear(sf::Color::White);

    sf::Text title;
    title.setFont(font);
    title.setString("Paused");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::Black);
    title.setStyle(Text::Bold | Text::Italic);
    title.setPosition(window->getSize().x / 2 - title.getLocalBounds().width / 2,
                           window->getSize().y / 4);
           // Add an outline to the text
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(2);

    // Apply a shadow effect to the text
    title.setOutlineColor(Color(0, 0, 0, 150)); // Semi-transparent black
    title.move(2, 2); // Move the shadow text slightly down and to the right

    for (int i = 0; i < options.size(); ++i)
    {
        sf::Text option;
        option.setFont(font);
        option.setString(options[i]);
        option.setCharacterSize(30);
         option.setPosition(window->getSize().x / 2 - option.getLocalBounds().width / 2, title.getPosition().y + title.getLocalBounds().height + 50 + i * 50);
        option.setFillColor((i == selectedOption) ? sf::Color::Red : sf::Color::Black);
        window->draw(option);
    }

    window->draw(title);
    window->display();
}

void PauseScreen::navigate(int delta)
{
    selectedOption = (selectedOption + delta + options.size()) % options.size();
}

PauseMenuOption PauseScreen::getSelectedOption() const
{
    return static_cast<PauseMenuOption>(selectedOption);
}

void PauseScreen::run()
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
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    navigate(-1);
                    break;
                case sf::Keyboard::Down:
                    navigate(1);
                    break;
                case sf::Keyboard::Return:
                    switch (getSelectedOption())
                    {
                    case PauseMenuOption::ContinueGame:
                        return;
                    case PauseMenuOption::SaveGame:
                        // Save game
                        game->saveGame();
                        (new MainMenu(window))->run();
                        return;
                    case PauseMenuOption::Quit:
                        (new MainMenu(window))->run();
                        return;
                    }
                    break;
                }
            }
        }
        render();
    }
}





