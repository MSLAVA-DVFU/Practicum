#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <memory>

#include "Constants.h"
#include "Textures.h"
#include "Map.h"
#include "Player.h"
#include "Info.h"
#include "GameRes.h"

#include "Enemy.h"

class HealthBar {
private:
    sf::RectangleShape background;
    sf::RectangleShape bar;
    float maxHealth;

public:
    HealthBar(float x, float y, float width, float height, float maxHealth) {
        this->maxHealth = maxHealth;

        background.setSize(sf::Vector2f(width, height));
        background.setFillColor(sf::Color(50, 50, 50));
        background.setPosition(x, y);

        bar.setSize(sf::Vector2f(width, height));
        bar.setFillColor(sf::Color(200, 0, 0));
        bar.setPosition(x, y);
    }

    void update(float currentHealth) {
        float healthRatio;
        if (currentHealth>=0) healthRatio = currentHealth / maxHealth;
        else healthRatio = 0;
        bar.setSize(sf::Vector2f(background.getSize().x * healthRatio, background.getSize().y));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(bar);
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Infinity Gate");

    

    Font font;
    font.loadFromFile("C:/Users/Kille/OneDrive/Рабочий стол/Дисциплины 2 курс/C++/Infinity Gate/Text/CyrilicOld.TTF");
    Text text("", font, 20);
    text.setFillColor(Color::Black);
    text.setOutlineColor(Color::Black);

    bool isMenuActive = true;
    bool isInfoVisible = false; // Переменная для отображения окна с информацией
    bool isGameOver = false; // Переменная для отображения окна результатов
    bool isChoosingClass = false;
    int selectedClass = 0; // Переменная для хранения выбранного класса


    textures::setTextures();

    Sprite s_map;
    s_map.setTexture(textures::map_texture);

    std::vector<std::pair<int, int>> freePositions=generateLevel();
    int randomIndex = rand() % (freePositions.size());

    Player* player = new Player(textures::player_texture, sf::Vector2f(freePositions[randomIndex].first*32, freePositions[randomIndex].second*32), 100, 0, true,1);
    HealthBar healthBar(20, 20, 400, 40, player->getHP());
    healthBar.update(player->getHP());
    freePositions.erase(freePositions.begin() + randomIndex);

    int N = freePositions.size();

    std::vector<Enemy*> enemies;
    for (int i = 0; i < 2*N; ++i) {
        randomIndex = rand() % freePositions.size();
        sf::Vector2f enemyPos(freePositions[randomIndex].first * 32, freePositions[randomIndex].second * 32);
        std::string name = (rand() % 2 == 0) ? "spidy" : "zombi";
        
        enemies.push_back(Enemy::create(name, (name == "spidy" ? textures::spider_texture : textures::zombi_texture), enemyPos));
    }


    sf::Clock clock;
    Clock gameTimeClock;
    int gameTime = 0;

    

    while (window.isOpen()) {
        if (isMenuActive) {
            showMenu(window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                isMenuActive = false;
                isChoosingClass = true; // Переход к выбору класса
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                window.close();
            }
            continue;
        }

        if (isChoosingClass) {
            window.clear();
            showClassSelectionWindow(window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player->setClass(1); // Knight
                isChoosingClass = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                player->setClass(2); // Archer
                isChoosingClass = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                player->setClass(3); // Wizard
                isChoosingClass = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player->setClass(4); // Thief
                isChoosingClass = false;
            }
			player->m_class = isChoosingClass;
            window.display();
            continue;
        }

        float time = clock.getElapsedTime().asMicroseconds();

        if (player->m_life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
        clock.restart();
        time /= 800;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Проверка нажатия клавиши Tab
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            isInfoVisible = true; // Показать окно
        }
        else {
            isInfoVisible = false; // Скрыть окно
        }

        player->Update(time);
        healthBar.update(player->getHP());



        window.clear(sf::Color::Black);

        //отрисовка карты
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++) {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
                if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
                if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
                if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
                if ((TileMap[i][j] == 'b')) s_map.setTextureRect(IntRect(160, 0, 32, 32));
                if ((TileMap[i][j] == '1')) s_map.setTextureRect(IntRect(193, 0, 32, 32));
                if ((TileMap[i][j] == '2')) s_map.setTextureRect(IntRect(226, 0, 32, 32));
                if ((TileMap[i][j] == '3')) s_map.setTextureRect(IntRect(257, 0, 32, 32));
                if ((TileMap[i][j] == '4')) s_map.setTextureRect(IntRect(289, 0, 31, 32));
                if ((TileMap[i][j] == '+')) s_map.setTextureRect(IntRect(321, 0, 31, 32));
                if ((TileMap[i][j] == '-')) s_map.setTextureRect(IntRect(353, 0, 31, 32));
                if ((TileMap[i][j] == '*')) s_map.setTextureRect(IntRect(385, 0, 31, 32));
                if ((TileMap[i][j] == '/')) s_map.setTextureRect(IntRect(417, 0, 32, 32));
                if ((TileMap[i][j] == 'w')) s_map.setTextureRect(IntRect(481, 0, 32, 32));

                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }

        window.draw(player->getSprite());
        healthBar.draw(window);
        for (auto& enemy : enemies) {
            if (enemy->isAlive() && player->getGlobalBounds().intersects(enemy->getGlobalBounds())) {
                player->takeDamage(enemy->getDamage());
            }
            if (enemy->isAlive()) {
                enemy->Updatepos(time, player->getPosition());
                window.draw(enemy->getSprite());
            }
       
        }

        // Отрисовка окна информации
        if (isInfoVisible) {
            drawInfoWindow(window, player->m_score, gameTime);
        }

        if (!player->m_life || player->m_keys==3) {
            isGameOver = true; // Игра окончена, окно результатов
            player->m_life = false;
        }

        if (isGameOver) {
            // Отображение окна результатов

            drawGameOverWindow(window,player->m_keys, player->m_score, gameTime);
           

            // Обработка действий игрока
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                // Перезапуск игры
                isGameOver = false;
                player->reset(); // метод для сброса состояния игрока
                generateLevel(); // Генерация нового уровня
                gameTime = 0;          // Сброс времени
                gameTimeClock.restart(); // Перезапуск таймера
                isChoosingClass = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                // Выход из игры
                window.close();
            }

            window.display(); // Обновление экрана
            continue;
        }

        window.display();
    }
    return 0;
}
