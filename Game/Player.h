// Player.h

#pragma once

#include "Character.h"

class PlayerController;

enum class State {
    IDLE,
    DEAD,
    RED,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Player : public Character {
private:
    State             m_state;
    PlayerController* m_controller;

public:
    Player() = delete;
    int m_score;
    bool m_life;
    int m_keys;
    int m_class;
    Player(sf::Texture& texture, sf::Vector2f start_pos, float health,int PlayerScore,bool life,int choice);
    ~Player();
    
    void reset();
    void setClass(int newClass);

    void Update(float time) override;

    void setState(State state);

    void interactionWithMap();
};
