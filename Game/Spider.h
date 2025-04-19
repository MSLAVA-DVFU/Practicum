#pragma once
#include "Enemy.h"

class Spider : public Enemy {
public:
    Spider(sf::Texture& texture, sf::Vector2f pos);
    virtual ~Spider() = default;
    void Update(float time) override {}
    void Updatepos(float time, sf::Vector2f player_pos) override;
    void checkColisionWithMap(float Dx, float Dy) override;
};
