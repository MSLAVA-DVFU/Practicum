#include "Zombi.h"
#include "Map.h"
#include <cmath>
#include <cstdlib>

Zombi::Zombi(sf::Texture& texture, sf::Vector2f pos)
    : Enemy(texture,pos, 50.f, true, "zombi") {
    m_speed = 1.0f;
    m_state = State::RIGHT;
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    m_sprite.setScale(0.8f, 0.8f);
    m_size = sf::Vector2f(m_sprite.getTextureRect().width - 10, m_sprite.getTextureRect().height - 10);
    m_state = State::LEFT;
    m_damage = 0.15;
}

void Zombi::Updatepos(float time, sf::Vector2f player_pos) {
    if (!m_life || m_health <= 0) {
        m_life = false;
        m_state = State::DEAD;
        return;
    }

    float dx = player_pos.x - m_pos.x;
    float dy = player_pos.y - m_pos.y;
    float distance = sqrt(dx * dx + dy * dy);

    float moveX = 0;
    float moveY = 0;


    if (distance < 150) {
        // Преследуем игрока
        if (fabs(dx) > fabs(dy)) {
            moveX = (dx) ? m_speed : -m_speed;
            m_state = (moveX > 0) ? State::RIGHT : State::LEFT;
        }
        else {
            moveY = (dy > 0) ? m_speed : -m_speed;
            m_state = (moveY > 0) ? State::DOWN : State::UP;
        }
    }
    else {
        if (m_state == State::LEFT) {
            moveX = -m_speed;
        }
        else if (m_state == State::RIGHT) {
            moveX = m_speed;
        }

        switch (m_state) {
        case State::UP:    moveY = -m_speed; break;
        case State::DOWN:  moveY = m_speed;  break;
        case State::LEFT:  moveX = -m_speed; break;
        case State::RIGHT: moveX = m_speed;  break;
        default: break;
        }
    }

    // Обновление позиции с учётом столкновений
    m_pos.x += moveX;
    checkColisionWithMap(moveX, 0);

    m_pos.y += moveY;
    checkColisionWithMap(0, moveY);

    m_sprite.setPosition(m_pos);
}

void Zombi::checkColisionWithMap(float Dx, float Dy) {
    for (int i = m_pos.y / 32; i < (m_pos.y + m_size.y) / 32; i++) {
        for (int j = m_pos.x / 32; j < (m_pos.x + m_size.x) / 32; j++) {

            if (TileMap[i][j] == '0') { // стена
                if (Dy > 0) {
                    m_pos.y = i * 32 - m_size.y;
                    m_state = State::UP;
                }
                if (Dy < 0) {
                    m_pos.y = i * 32 + 32;
                    m_state = State::DOWN;
                }
                if (Dx > 0) {
                    m_pos.x = j * 32 - m_size.x;
                    if (m_state == State::RIGHT) m_state = State::LEFT;
                }
                if (Dx < 0) {
                    m_pos.x = j * 32 + 32;
                    if (m_state == State::LEFT) m_state = State::RIGHT;
                }
            }
        }
    }
}
