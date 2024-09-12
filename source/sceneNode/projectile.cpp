#include "sceneNode/projectile.h"

#include "common/utility.h"
#include "common/dataTable.h"


namespace
{
	const auto Table = initialProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textureHolder) :
Entity{1},
_type{type},
_sprite{textureHolder.get(Table.at(type).textureID)}
{
	centerOrigin(_sprite);
}

void Projectile::guideTowards(sf::Vector2f position)
{
	assert(isGuided());
	_targetDirection = unitVector(position - getWorldPosition());
}

bool Projectile::isGuided() const
{
	return _type == Type::Missile;
}

Category Projectile::getCategory() const
{
	if(_type == Type::EnemyBullet)
	{
		return Category::EnemyProjectile;
	}
	else
	{
		return Category::AlliedProjectile;
	}
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return Entity::getBoundingRect();
}

float Projectile::getMaxSpeed() const
{
	return Table.at(_type).speed;
}

int Projectile::getDamage() const
{
	return Table.at(_type).damage;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commandQueue)
{
	if(isGuided())
	{
		constexpr auto approachRate{ 200.f };

		auto newVelocity = unitVector(approachRate * dt.asSeconds() * _targetDirection + getVelocity());
		newVelocity *= getMaxSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);

		setRotation(toDegree(angle) + 90.f);
		setVelocity(newVelocity);
	}

	Entity::updateCurrent(dt, commandQueue);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
