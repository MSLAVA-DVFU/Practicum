// Character.h

#pragma once

#include <SFML/Graphics.hpp>

enum class Direction : bool {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
};

class Character {
protected:
	float		 m_health;
	float		 m_speed;
	sf::Vector2f m_size;
	sf::Vector2f m_pos;
	sf::Sprite   m_sprite;
	Direction    m_direction = Direction::RIGHT;

public:
	virtual ~Character();

	virtual void Update(float time) = 0;
	void takeDamage(float damage);

	void setPosition(const sf::Vector2f& pos);
	void setDirection(Direction direction);
	void setHP(float health);

	float getHP() const;
	float MoveTimer;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	Direction getDirection() const;
};
