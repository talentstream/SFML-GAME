#include "aircraft.h"

Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Type::Eagle:
		return Textures::ID::Eagle;
	case Aircraft::Type::Raptor:
		return Textures::ID::Raptor;
	default:
		return Textures::ID::Eagle;
	}
}

Aircraft::Aircraft(Type type, const TextureHolder& textureHolder)
	: _type{type},
	  _sprite{textureHolder.get(toTextureID(type))}
{
	sf::FloatRect bounds = _sprite.getLocalBounds();
	_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

