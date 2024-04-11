#include "headers/MainMenuScreen.hpp"

MainMenu::MainMenu(RenderWindow *window)
{
    this->window = window;
    if (!font.loadFromFile("assets/fonts/sansation.ttf"))
    {
        std::cout << "Error loading font" << endl;
    }
    this->selectedOption = 0;
}

// Function to render the menu
void MainMenu::render()
{
    window->clear(sf::Color::White);
    sf::Text title;
    title.setFont(font);
    title.setString("Tetriste");
    title.setCharacterSize(80);
    title.setStyle(Text::Bold | Text::Italic);
    title.setFillColor(sf::Color::Black);
    title.setPosition(window->getSize().x / 2 - title.getLocalBounds().width / 2, window->getSize().y / 6);
       // Add an outline to the text
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(2);

    // Apply a shadow effect to the text
    title.setOutlineColor(Color(0, 0, 0, 150)); // Semi-transparent black
    title.move(2, 2); // Move the shadow text slightly down and to the right
    bool isGameSaved = checkSavedGame();
    if (!isGameSaved){
        options = {"New Game", "LeaderBoard","Contols", "Quit"};
    }
    for (int i = 0; i < options.size(); ++i)
    {
        sf::Text option;
        option.setFont(font);
        option.setString(options[i]);
        option.setCharacterSize(30);
        option.setPosition(window->getSize().x / 2 - option.getLocalBounds().width / 2, window->getSize().y / 3 + i * 75.f);
        option.setFillColor((i == selectedOption) ? sf::Color::Red : sf::Color::Black);
        window->draw(option);
    }

    window->draw(title);
    window->display();
}

// Function to handle arrow key navigation
void MainMenu::navigate(int delta)
{
    selectedOption = (selectedOption + delta + options.size()) % options.size();
}

// Function to get the currently selected option
MainMenuOption MainMenu::getSelectedOption() const
{
    if(!checkSavedGame() && selectedOption >= 1){
        return static_cast<MainMenuOption>(selectedOption + 1);
    }
    return static_cast<MainMenuOption>(selectedOption);
}

// Function to run the main menu loop
void MainMenu::run()
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
                    MainMenuOption selectedOption = getSelectedOption();
                    // Handle selected option

                    if (selectedOption == MainMenuOption::NewGame)
                    {
                        (new DifficultyMenu(window))->run();
                    }
                    else if (selectedOption == MainMenuOption::ResumeGame)
                    {
                        (new Game(window, true))->run();
                        
                    }
                    else if (selectedOption == MainMenuOption::ViewScores)
                    {
                        (new LeaderBoard(window))->run();
                    }
                    else if (selectedOption == MainMenuOption::Controls)
                    {
                        (new ControlsScreen(window))->run();
                    }
                    else if (selectedOption == MainMenuOption::Quit)
                    {
                        window->close();
                    }
                }
            }
        }

        // Render menu
        render();
    }
}
