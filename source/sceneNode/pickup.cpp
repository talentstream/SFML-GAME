#include "sceneNode/pickup.h"
#include "common/dataTable.h"
#include "common/utility.h"

namespace 
{
	const auto Table = initialPickupData();
}

Pickup::Pickup(Type type, const TextureHolder& textureHolder) :
	Entity{1},
	_type{type},
	_sprite{textureHolder.get(Table.at(type).textureID)}
{
	centerOrigin(_sprite);
}

Category Pickup::getCategory() const
{
	return Category::Pickup;
}

sf::FloatRect Pickup::getBoundingRect() const
{
	return  getWorldTransform().transformRect(_sprite.getGlobalBounds());
}

void Pickup::apply(Aircraft& player) const
{
	Table.at(_type).action(player);
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
