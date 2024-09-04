#pragma once

#include "entity.h"
#include "resourceHolder.h"


class Aircraft :
	public Entity
{
public:
	enum class Type
	{
		Eagle,
		Raptor
	};

	explicit Aircraft(Type type, const TextureHolder& textureHolder);

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	Category getCategory() const override;

private:
	Type _type;
	sf::Sprite _sprite;
};

class AircraftMover
{
public:
	AircraftMover(float vx, float vy)
		: _velocity{vx, vy}
	{
	}

	void operator()(Aircraft& aircraft, sf::Time dt) const
	{
		aircraft.accelerate(_velocity);
	}

	sf::Vector2f _velocity;
};
