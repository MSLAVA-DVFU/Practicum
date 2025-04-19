#pragma once

#include "Character.h"

class Enemy : public Character {
protected:
    bool   m_life;
    float  m_speed;
    State  m_state;
    std::string m_name;

public:
    Enemy(sf::Texture& texture, sf::Vector2f start_pos, float health, bool life, std::string name);
    virtual ~Enemy()=default;

    virtual void Update(float time) = 0;
    virtual void Updatepos(float time, sf::Vector2f player_pos) = 0;
    virtual void checkColisionWithMap(float Dx, float Dy) = 0;
    bool isAlive() const { return m_life; }
    void kill();
    sf::FloatRect getGlobalBounds() const;

    static Enemy* create(const std::string& name, sf::Texture& texture, sf::Vector2f pos);
};
