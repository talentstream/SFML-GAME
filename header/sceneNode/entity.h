#pragma once

#include <SFML/Graphics.hpp>

#include "common/sceneNode.h"

class Entity : public SceneNode
{
public:
	explicit Entity(int hitpoints);

	void setVelocity(sf::Vector2f velocity);

	void setVelocity(float vx, float vy);

	void accelerate(sf::Vector2f velocity);

	void accelerate(float vx, float vy);

	sf::Vector2f getVelocity() const;

	void repair(int points);

	void damage(int points);

	void destroy();

	int getHitpoints() const;

	bool isDestroyed() const override;

protected:
	void updateCurrent(sf::Time dt, CommandQueue& commandQueue) override;

private:
	sf::Vector2f _velocity;

	int _hitpoints;
};
