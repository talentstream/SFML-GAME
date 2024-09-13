#pragma once

#include <unordered_map>

#include "common/resourceHolder.h"
#include "sceneNode/aircraft.h"
#include "sceneNode/pickup.h"
#include "sceneNode/projectile.h"

struct Direction
{
	Direction(float angle, float distance) :
		angle(angle),
		distance(distance)
	{
	}

	float angle;
	float distance;
};

struct AircraftData
{
	int hitpoints;
	float speed;
	TextureID textureID;
	sf::Time fireInterval;
	std::vector<Direction> directions;
};

struct ProjectileData
{
	int damage;
	float speed;
	TextureID textureID;
};

struct PickupData
{
	std::function<void(Aircraft&)> action;
	TextureID textureID;
};

std::unordered_map<Aircraft::Type, AircraftData> initialAircraftData();

std::unordered_map<Projectile::Type, ProjectileData> initialProjectileData();

std::unordered_map<Pickup::Type, PickupData> initialPickupData();