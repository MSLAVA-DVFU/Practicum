#include "Info.h"
#include "Constants.h"

void drawGameOverWindow(sf::RenderWindow& window, int keys, int score, int gameTime) {
    // Прямоугольник для фона
    sf::RectangleShape gameOverBox(sf::Vector2f(400, 200));
    gameOverBox.setFillColor(sf::Color(50, 50, 50, 200)); // Полупрозрачный фон
    gameOverBox.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 100);

    // Настройка текста
    sf::Font font;
    font.loadFromFile("C:/Users/Kille/OneDrive/Рабочий стол/Дисциплины 2 курс/C++/Infinity Gate/Text/CyrilicOld.TTF");

    sf::Text title;
    if (keys==3) title=sf::Text ("You Win!", font, 36);
    else title=sf::Text ("Game Over", font, 36);
    title.setFillColor(sf::Color::Red);
    title.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 80);

    sf::Text scoreText("Score: " + std::to_string(score), font, 24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2 - 20);

    sf::Text timeText("Time: " + std::to_string(gameTime) + "s", font, 24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2 + 20);

    sf::Text restartText("Press R to Restart", font, 20);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 80);

    sf::Text exitText("Press Q to Quit", font, 20);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 110);

    // Отрисовка элементов
    window.draw(gameOverBox);
    window.draw(title);
    window.draw(scoreText);
    window.draw(timeText);
    window.draw(restartText);
    window.draw(exitText);
}