#include "Spider.h"

Spider::Spider(const sf::Texture& texture, sf::Vector2f position)
    : Enemy(texture, position, 50.0f, 80.0f, 15.0f) {
    direction = { 0.0f, -1.0f }; // Начальное движение вверх
}

void Spider::Update(float deltaTime) {
    sf::Vector2f newPosition = sprite.getPosition() + direction * speed * deltaTime;

    for (int i = newPosition.y / 32; i < (newPosition.y + m_size.y) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
        for (int j = newPosition.x / 32; j < (m_pos.x + m_size.x) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
        {
            if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
            {
        ChangeDirection();
    }
    else {
        sprite.setPosition(newPosition);
    }
}

void Spider::ChangeDirection() {
    direction = (direction.y != 0) ? sf::Vector2f(1.0f, 0) : sf::Vector2f(0, -1.0f);
}
