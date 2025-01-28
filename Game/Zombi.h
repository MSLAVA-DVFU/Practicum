#pragma once
#include "Enemy.h"

class Zombie : public Enemy {
public:
    Zombie(const sf::Texture& texture, sf::Vector2f position);

    void Update(float deltaTime) override;

private:
    void ChangeDirection();
};
