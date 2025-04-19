#include "Enemy.h"
#include "Zombi.h"
#include "Spider.h"

Enemy::Enemy(sf::Texture& texture,sf::Vector2f start_pos, float health, bool life, std::string name) {
    m_pos = start_pos;
    m_health = health;
    m_life = life;
    m_name = name;
}

Enemy* Enemy::create(const std::string& name, sf::Texture& texture, sf::Vector2f pos) {
    if (name == "spidy") {
        return new Spider(texture, pos);
    }
    else{
        return new Zombi(texture, pos);
    }
    return nullptr; 
}

void Enemy::kill() {
    m_life = false;
    m_state = State::DEAD;
}

sf::FloatRect Enemy::getGlobalBounds() const
{
    return getSprite().getGlobalBounds();
}
