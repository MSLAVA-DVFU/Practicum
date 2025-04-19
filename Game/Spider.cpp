#include "Spider.h"
#include "Map.h"
#include <cmath>

Spider::Spider(sf::Texture& texture, sf::Vector2f pos)
    : Enemy(texture, pos, 35, true, "spidy") {
    m_speed = 2.0f;
    m_state = State::LEFT;
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(64, 32, 32, 32));
    m_sprite.setScale(0.8f, 0.8f);
    m_size = sf::Vector2f(m_sprite.getTextureRect().width - 10, m_sprite.getTextureRect().height - 10);
    m_damage = 0.2;
}

void Spider::Updatepos(float time, sf::Vector2f player_pos) {
    if (!m_life || m_health <= 0) {
        m_life = false;
        m_state = State::DEAD;
        return;
    }

    float dx = player_pos.x - m_pos.x;
    float dy = player_pos.y - m_pos.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    dx /= dist; dy /= dist;

    m_pos.x += dx * m_speed;
    checkColisionWithMap(dx * m_speed, 0);

    m_pos.y += dy * m_speed;
    checkColisionWithMap(0, dy * m_speed);

    m_sprite.setPosition(m_pos);
}

void Spider::checkColisionWithMap(float Dx, float Dy) {
    for (int i = m_pos.y / 32; i < (m_pos.y + m_size.y) / 32; i++) {
        for (int j = m_pos.x / 32; j < (m_pos.x + m_size.x) / 32; j++) {
            if (TileMap[i][j] == '0') {
                if (Dy > 0) m_pos.y = i * 32 - m_size.y;
                if (Dy < 0) m_pos.y = i * 32 + 32;
                if (Dx > 0) m_pos.x = j * 32 - m_size.x;
                if (Dx < 0) m_pos.x = j * 32 + 32;
            }
        }
    }
}
