#include "Zombi.h"

Zombie::Zombie(const sf::Texture& texture, sf::Vector2f position)
    : Enemy(texture, position, 50.0f, 100.0f, 10.0f) {
    direction = { -1.0f, 0.0f }; // Начальное движение влево
}

void Zombie::Update(float deltaTime) {
    sf::Vector2f newPosition = sprite.getPosition() + direction * speed * deltaTime;

    // Проверка столкновений с границами карты
    int gridX = static_cast<int>(newPosition.x / 32);
    int gridY = static_cast<int>(newPosition.y / 32);
    if (TileMap[gridY][gridX] == '0') {
        ChangeDirection();
    }
    else {
        sprite.setPosition(newPosition);
    }
}

void Zombie::ChangeDirection() {
    direction = (direction.x != 0) ? sf::Vector2f(0, 1.0f) : sf::Vector2f(-1.0f, 0);
}
