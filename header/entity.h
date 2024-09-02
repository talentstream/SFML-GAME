#pragma once

#include <SFML/Graphics.hpp>

#include "sceneNode.h"

class Entity :
	public SceneNode
{
public:
	void setVelocity(sf::Vector2f velocity);

	void setVelocity(float vx, float vy);

	sf::Vector2f getVelocity() const;

private:
	void updateCurrent(sf::Time dt) override;

	sf::Vector2f _velocity;
};
