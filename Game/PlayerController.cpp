// PlayerController.cpp

#include "PlayerController.h"

#include "Player.h"
#include "Constants.h"

PlayerController* PlayerController::controller = nullptr;

PlayerController::~PlayerController() {
    delete controller;
}

PlayerController* PlayerController::getPlayerController() {
    if (!controller) {
        controller = new PlayerController();
    }

    return controller;
}

void PlayerController::controllPlayer(Player* player, float time) {
    sf::Vector2f updated_pos = player->getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->setState(State::LEFT);
        player->setDirection(Direction::LEFT);
        updated_pos.x -= 0.15 * time;
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        updated_pos.x += 0.15 * time;
        player->setState(State::RIGHT);
        player->setDirection(Direction::RIGHT);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        updated_pos.y -= 0.15 * time;
        player->setState(State::UP);
        player->setDirection(Direction::UP);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        updated_pos.y += 0.15 * time;
        player->setState(State::DOWN);
        player->setDirection(Direction::DOWN);
    }

    player->setPosition(updated_pos);
    
}