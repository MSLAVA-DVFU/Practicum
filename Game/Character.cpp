// Character.cpp

#include "Character.h"

Character::~Character() {}

void Character::takeDamage(float damage) {
    m_health -= damage;
}

void Character::setPosition(const sf::Vector2f& pos) {
    m_pos = pos;
}


void Character::setDirection(Direction direction) {
    m_direction = direction;
}

void Character::setHP(float health) {
    m_health = health;
}


float Character::getHP() const {
    return m_health;
}

float Character::getDamage() const {
    return m_damage;
}

sf::Vector2f Character::getSize() const {
    return m_size;
}

sf::Vector2f Character::getPosition() const {
    return m_pos;
}

sf::Sprite Character::getSprite() const {
    return m_sprite;
}

Direction Character::getDirection() const {
    return m_direction;
}

