#pragma once
#include "Enemy.h"

class Zombi : public Enemy {
public:
    Zombi(sf::Texture& texture, sf::Vector2f pos);
    virtual ~Zombi() = default;
    void Update(float time) override {}
    void Updatepos(float time, sf::Vector2f player_pos) override;
    void checkColisionWithMap(float Dx, float Dy) override;
};
