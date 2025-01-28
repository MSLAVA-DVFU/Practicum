#pragma once
#include "Enemy.h"

class Spider : public Enemy {
public:
    Spider(const sf::Texture& texture, sf::Vector2f position);

    void Update(float deltaTime) override;

private:
    void ChangeDirection();
};
