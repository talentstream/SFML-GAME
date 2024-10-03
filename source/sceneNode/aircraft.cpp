#include "sceneNode/aircraft.h"

#include "common/dataTable.h"
#include "common/utility.h"
#include "common/commandQueue.h"

TextureID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Type::Eagle:
		return TextureID::Eagle;
	case Aircraft::Type::Raptor:
		return TextureID::Raptor;
	default:
		return TextureID::Eagle;
	}
}

namespace
{
	const auto Table = initialAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textureHolder, const FontHolder& fontHolder)
	: Entity{Table.at(type).hitpoints},
	  _type{type},
	  _sprite{textureHolder.get(toTextureID(type))}
{
	centerOrigin(_sprite);

	_fireCommand._category = Category::SceneAirLayer;
	_fireCommand._action = [this, &textureHolder](SceneNode& node, sf::Time)
	{
		createBullets(node, textureHolder);
	};

	_missileCommand._category = Category::SceneAirLayer;
	_missileCommand._action = [this, &textureHolder](SceneNode& node, sf::Time)
	{
		createProjectile(node, Projectile::Type::Missile, 0.f, 0.5f, textureHolder);
	};

	_dropPickupCommand._category = Category::SceneAirLayer;
	_dropPickupCommand._action = [this, &textureHolder](SceneNode& node, sf::Time)
	{
		createPickup(node, textureHolder);
	};

	auto healthDisplay = std::make_unique<TextNode>(fontHolder, "");
	_healthDisplay = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	if (getCategory() == Category::PlayerAircraft)
	{
		auto missileDisplay = std::make_unique<TextNode>(fontHolder, "");
		_missileDisplay = missileDisplay.get();
		_missileDisplay->setPosition(0.f, 70.f);
		attachChild(std::move(missileDisplay));
	}

	updateTexts();
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Aircraft::updateMovementPattern(sf::Time dt)
{

	const auto& directions = Table.at(_type).directions;

	if (directions.empty() == false)
	{
		auto distanceToTravel = directions[_directionIndex].distance;
		if (_travelledDistance > distanceToTravel)
		{
			_directionIndex = (_directionIndex + 1) % directions.size();
			_travelledDistance = 0.f;
		}
	}
}

Category Aircraft::getCategory() const
{
	if (isAllied())
	{
		return Category::PlayerAircraft;
	}
	else
	{
		return Category::EnemyAircraft;
	}
}

sf::FloatRect Aircraft::getBoundingRect() const
{
	return Entity::getBoundingRect();
}

bool Aircraft::isMarkedForRemoval() const
{
	return Entity::isMarkedForRemoval();
}

bool Aircraft::isAllied() const
{
	return _type == Type::Eagle;
}

float Aircraft::getMaxSpeed() const
{
	return Table.at(_type).speed;
}

void Aircraft::increaseFireRate()
{
	if (_fireRateLevel < 10)
	{
		++_fireRateLevel;
	}
}

void Aircraft::increaseSpread()
{
	if (_spreadLevel < 3)
	{
		++_spreadLevel;
	}
}

void Aircraft::collectMissiles(unsigned int count)
{
	_missileAmmo += count;
}

void Aircraft::fire()
{
	if (Table.at(_type).fireInterval != sf::Time::Zero)
	{
		_isFiring = true;
	}
}

void Aircraft::launchMissile()
{
	if (_missileAmmo > 0)
	{
		_isLaunchingMissile = true;
		--_missileAmmo;
	}
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commandQueue)
{
	if (isDestroyed())
	{
		checkPickupDrop(commandQueue);

		_isMarkedForRemoval = true;
		return;
	}

	checkProjectileLaunch(dt, commandQueue);
	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commandQueue);

	updateTexts();
}

void Aircraft::checkPickupDrop(CommandQueue& commandQueue)
{
	if (!isAllied() && randomInt(3) == 0)
	{
		commandQueue.push(_dropPickupCommand);
	}
}

void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue& commandQueue)
{
	if (!isAllied())
	{
		fire();
	}

	if (_isFiring && _fireCountdown <= sf::Time::Zero)
	{
		commandQueue.push(_fireCommand);
		_fireCountdown += Table.at(_type).fireInterval / (_fireRateLevel + 1.f);
		_isFiring = false;
	}
	else if (_fireCountdown > sf::Time::Zero)
	{
		_fireCountdown -= dt;
		_isFiring = false;
	}

	if (_isLaunchingMissile)
	{
		commandQueue.push(_missileCommand);
		_isLaunchingMissile = false;
	}
}

void Aircraft::createBullets(SceneNode& node, const TextureHolder& textureHolder) const
{
	auto type = isAllied() ? Projectile::Type::AlliedBullet : Projectile::Type::EnemyBullet;

	switch (_spreadLevel)
	{
	case 1:
		createProjectile(node, type, 0.f, 0.5f, textureHolder);
		break;

	case 2:
		createProjectile(node, type, -0.33f, 0.33f, textureHolder);
		createProjectile(node, type, +0.33f, 0.33f, textureHolder);
		break;

	case 3:
		createProjectile(node, type, -0.5f, 0.33f, textureHolder);
		createProjectile(node, type, 0.f, 0.5f, textureHolder);
		createProjectile(node, type, +0.5f, 0.33f, textureHolder);
		break;

	default:
		break;
	}
}

void Aircraft::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset,
                                const TextureHolder& textureHolder) const
{
	auto projectile = std::make_unique<Projectile>(type, textureHolder);
	sf::Vector2f offset{xOffset * _sprite.getGlobalBounds().width, yOffset * _sprite.getGlobalBounds().height};
	sf::Vector2f velocity{0, projectile->getMaxSpeed()};

	float sign = isAllied() ? -1.f : 1.f;
	projectile->setPosition(getWorldPosition() + offset * sign);
	projectile->setVelocity(velocity * sign);
	node.attachChild(std::move(projectile));
}

void Aircraft::createPickup(SceneNode& node, const TextureHolder& textureHolder) const
{
	auto type = static_cast<Pickup::Type>(randomInt(std::to_underlying(Pickup::Type::Count)));

	auto pickup = std::make_unique<Pickup>(type, textureHolder);
	pickup->setPosition(getWorldPosition());
	pickup->setVelocity(0.f, 1.f);
	node.attachChild(std::move(pickup));
}

void Aircraft::updateTexts() const
{
	_healthDisplay->setString(std::to_string(getHitpoints()) + " HP");
	_healthDisplay->setPosition(0.f, 50.f);
	_healthDisplay->setRotation(-getRotation());

	if (_missileDisplay)
	{
		if (_missileAmmo == 0)
		{
			_missileDisplay->setString("");
		}
		else
		{
			_missileDisplay->setString("M: " + std::to_string(_missileAmmo));
		}
	}
}
