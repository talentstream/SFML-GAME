#pragma once

#include "common/resourceHolder.h"
#include "sceneNode/entity.h"

class Aircraft;

class Pickup : public Entity
{
public:
	enum class Type
	{
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		Count
	};

	Pickup(Type type, const TextureHolder& textureHolder);

	Category getCategory() const override;

	sf::FloatRect getBoundingRect() const override;

	void apply(Aircraft& player) const;

protected:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Type _type;
	sf::Sprite _sprite;

};
