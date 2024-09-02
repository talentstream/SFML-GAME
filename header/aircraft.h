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

private:
	Type _type;
	sf::Sprite _sprite;
};
