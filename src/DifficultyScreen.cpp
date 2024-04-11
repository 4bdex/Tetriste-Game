#include "headers/DifficultyScreen.hpp"

DifficultyMenu::DifficultyMenu(RenderWindow* window) : window(window){
         if (!font.loadFromFile("assets/fonts/sansation.ttf"))
    {
        std::cout << "Error loading font" << endl;
    }
    this->selectedOption = 0;
}

// Function to render the menu
void DifficultyMenu::render()
{
    window->clear(sf::Color::White);
    sf::Text title;
    title.setFont(font);
    title.setString("Choose Mode:");
    title.setCharacterSize(45);
    title.setStyle(Text::Bold | Text::Italic);
    title.setFillColor(sf::Color::Black);
    title.setPosition(window->getSize().x / 2 - title.getLocalBounds().width / 2, window->getSize().y / 3 - 150);
           // Add an outline to the text
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(2);

    // Apply a shadow effect to the text
    title.setOutlineColor(Color(0, 0, 0, 150)); // Semi-transparent black
    title.move(2, 2); // Move the shadow text slightly down and to the right
    // display option but with each selected option display a description of the selected option on top right
    for (int i = 0; i < options.size(); i++)
    {
        sf::Text option;
        option.setFont(font);
        option.setString(options[i]);
        option.setCharacterSize(30);
        option.setFillColor(selectedOption == i ? sf::Color::Red : sf::Color::Black);
        option.setPosition(window->getSize().x / 2 - option.getLocalBounds().width / 2, window->getSize().y / 3 + i * 75.f);
        window->draw(option);
    }
    // display description of selected option
    sf::Text description;
    description.setFont(font);
    description.setString(optionsDescription[selectedOption]);
    description.setCharacterSize(25);
    description.setFillColor(sf::Color::Black);
    description.setPosition(window->getSize().x / 2 - description.getLocalBounds().width / 2, window->getSize().y / 3 + options.size() * 75.f + 50.f);
    window->draw(title);
    window->draw(description);
    window->display();
    
}

// Function to handle arrow key navigation
void DifficultyMenu::navigate(int delta)
{
    selectedOption = (selectedOption + delta + options.size()) % options.size();
}

// Function to get the currently selected option
DifficultyOption DifficultyMenu::getSelectedOption() const
{
    return static_cast<DifficultyOption>(selectedOption);
}

// Function to run the main menu loop
void DifficultyMenu::run()
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
                else if(event.key.code == sf::Keyboard::Escape){
                    (new MainMenu(window))->run();
                }
                else if (event.key.code == sf::Keyboard::Return)
                {
                    DifficultyOption selectedOption = getSelectedOption();
                    // Handle selected option

                    if (selectedOption == DifficultyOption::EASY)
                    {
                        (new Game(window, 4))->run();
                       
                    }
                    else if (selectedOption == DifficultyOption::MEDIUM)
                    {
                        (new Game(window, 5))->run();
                    }
                    else if (selectedOption == DifficultyOption::HARD)
                    {
                        (new Game(window, 6))->run();
                    }
                }
            }
        }

        // Render menu
        render();
    }
}
