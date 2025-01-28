// Enemy.h

#pragma once

#include "Character.h"

enum class Direction {
    DEAD,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Enemy : public Character {
private:
    Direction             m_state;

public:
    Enemy() = delete;
    bool m_life;
    Enemy(sf::Texture& texture, sf::Vector2f start_pos, float health, bool life);
    ~Enemy();


    void Update(float time) override;

    void setDirection(Direction direct);

    void interactionWithMap();
};
