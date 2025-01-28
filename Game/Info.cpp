#include "Info.h"
#include "Constants.h"

void showMenu(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("C:/Users/Kille/OneDrive/Рабочий стол/Дисциплины 2 курс/C++/Infinity Gate/Text/CyrilicOld.TTF");

    sf::Text title("Infinity Gate", font, 50);
    title.setFillColor(sf::Color::White);
    title.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 4);

    sf::Text startOption("1. Start Game", font, 30);
    startOption.setFillColor(sf::Color::White);
    startOption.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);

    sf::Text exitOption("2. Exit", font, 30);
    exitOption.setFillColor(sf::Color::White);
    exitOption.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 50);

    window.clear();
    window.draw(title);
    window.draw(startOption);
    window.draw(exitOption);
    window.display();
}

void drawInfoWindow(sf::RenderWindow& window, int score, int gameTime) {
    // Прямоугольник для фона
    sf::RectangleShape infoBox(sf::Vector2f(300, 150));
    infoBox.setFillColor(sf::Color(50, 50, 50, 200)); // Полупрозрачный фон
    infoBox.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 75);

    // Настройка текста
    sf::Font font;
    font.loadFromFile("C:/Users/Kille/OneDrive/Рабочий стол/Дисциплины 2 курс/C++/Infinity Gate/Text/CyrilicOld.TTF");

    sf::Text scoreText("Score: " + std::to_string(score), font, 24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(WINDOW_WIDTH / 2 - 130, WINDOW_HEIGHT / 2 - 50);

    sf::Text timeText("Time: " + std::to_string(gameTime) + "s", font, 24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(WINDOW_WIDTH / 2 - 130, WINDOW_HEIGHT / 2);

    // Отрисовка элементов
    window.draw(infoBox);
    window.draw(scoreText);
    window.draw(timeText);
}

void showClassSelectionWindow(sf::RenderWindow& window) {
    sf::RectangleShape classBox(sf::Vector2f(400, 400));
    classBox.setFillColor(sf::Color(50, 50, 50, 200)); // Полупрозрачный фон
    classBox.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 125);

    sf::Font font;
    font.loadFromFile("C:/Users/Kille/OneDrive/Рабочий стол/Дисциплины 2 курс/C++/Infinity Gate/Text/CyrilicOld.TTF");

    sf::Text title("Choose Your Class", font, 36);
    title.setFillColor(sf::Color::White);
    title.setPosition(WINDOW_WIDTH / 2 - 160, WINDOW_HEIGHT / 2 - 110);

    sf::Text knight("A. Knight", font, 24);
    knight.setFillColor(sf::Color::White);
    knight.setPosition(WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2 - 50);

    sf::Text archer("B. Archer", font, 24);
    archer.setFillColor(sf::Color::White);
    archer.setPosition(WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2 - 20);

    sf::Text wizard("C. Wizard", font, 24);
    wizard.setFillColor(sf::Color::White);
    wizard.setPosition(WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2 + 10);

    sf::Text thief("D. Thief", font, 24);
    thief.setFillColor(sf::Color::White);
    thief.setPosition(WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2 + 40);

    sf::Text mission("To win you have to collect any 3 keys.\nCollect treasures for bonus score.\nBeware of traps and monsters.", font, 22);
    mission.setFillColor(sf::Color::White);
    mission.setPosition(WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2 + 120);

    window.draw(classBox);
    window.draw(title);
    window.draw(knight);
    window.draw(archer);
    window.draw(wizard);
    window.draw(thief);
    window.draw(mission);
}