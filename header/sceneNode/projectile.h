#pragma once

#include "sceneNode/entity.h"

#include "common/resourceHolder.h"

class Projectile final : public Entity
{
public:
	enum class Type
	{
		AlliedBullet,
		EnemyBullet,
		Missile,
		Count
	};

	Projectile(Type type, const TextureHolder& textureHolder);

	void guideTowards(sf::Vector2f position);

	bool isGuided() const;

	Category getCategory() const override;

	sf::FloatRect getBoundingRect() const override;

	float getMaxSpeed() const;

	int getDamage() const;

private:
	void updateCurrent(sf::Time dt, CommandQueue& commandQueue) override;

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	Type _type;
	sf::Sprite _sprite;
	sf::Vector2f _targetDirection;
};
