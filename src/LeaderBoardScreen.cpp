#include "headers/LeaderBoardScreen.hpp"

LeaderBoard::LeaderBoard(RenderWindow *window) : window(window)
{
    if (!font.loadFromFile("assets/fonts/sansation.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
}
// Function to render the leaderboard
void LeaderBoard::render()
{
    window->clear(sf::Color::White);

    Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(60);
    titleText.setStyle(Text::Bold | Text::Italic);
    titleText.setString("Leaderboard");
    titleText.setFillColor(Color::Black);
    titleText.setPosition(window->getSize().x / 2 - titleText.getLocalBounds().width / 2, window->getSize().y / 8);
           // Add an outline to the text
    titleText.setOutlineColor(Color::Black);
    titleText.setOutlineThickness(2);

    // Apply a shadow effect to the text
    titleText.setOutlineColor(Color(0, 0, 0, 150)); // Semi-transparent black
    titleText.move(2, 2); // Move the shadow text slightly down and to the right
    window->draw(titleText);

    vector scores = getScores();

    if(scores.empty()){
        Text noScoresText;
        noScoresText.setFont(font);
        noScoresText.setCharacterSize(30);
        noScoresText.setFillColor(Color::Black);
        noScoresText.setString("No scores yet!");
        noScoresText.setPosition(window->getSize().x / 2 - noScoresText.getLocalBounds().width / 2, window->getSize().y / 8 + 200);
        window->draw(noScoresText);
    }else{
        // print top 10 scores

    for (int i = 0; i < scores.size(); ++i)
    {
        Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(Color::Black);
        scoreText.setString(std::to_string(i + 1) + ". " + scores[i].first);

        scoreText.setPosition(titleText.getPosition().x ,
                              titleText.getPosition().y + titleText.getLocalBounds().height + window->getSize().y / 15 * (i + 1));
        window->draw(scoreText);
        scoreText.setString(std::to_string(scores[i].second));
        scoreText.setPosition(titleText.getPosition().x + titleText.getLocalBounds().width - scoreText.getLocalBounds().width,
                              titleText.getPosition().y + titleText.getLocalBounds().height + window->getSize().y / 15 * (i + 1));
        window->draw(scoreText);
    }
    }
    
    // draw press any key to continue
    Text continueText;
    continueText.setFont(font);
    continueText.setCharacterSize(20);
    continueText.setFillColor(Color::Black);
    continueText.setString("Press any key to continue");
    continueText.setPosition(window->getSize().x / 2 - continueText.getLocalBounds().width / 2,
                             window->getSize().y - 100);
    window->draw(continueText);

}

// Function to run the leaderboard loop
void LeaderBoard::run()
{
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
        window->clear();
        render();
        window->display();
    }
}
