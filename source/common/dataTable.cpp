#include "common/dataTable.h"

std::unordered_map<Aircraft::Type, AircraftData> initialAircraftData()
{
	std::unordered_map<Aircraft::Type, AircraftData> data;

	using enum Aircraft::Type;
	data[Eagle].hitpoints = 100;
	data[Eagle].speed = 200.f;
	data[Eagle].textureID = TextureID::Eagle;

	data[Raptor].hitpoints = 20;
	data[Raptor].speed = 80.f;
	data[Raptor].textureID = TextureID::Raptor;
	data[Raptor].directions.emplace_back(45.f, 80.f);
	data[Raptor].directions.emplace_back(-45.f, 160.f);
	data[Raptor].directions.emplace_back(45.f, 80.f);

	data[Avenger].hitpoints = 40;
	data[Avenger].speed = 50.f;
	data[Avenger].textureID = TextureID::Avenger;
	data[Avenger].directions.emplace_back(45.f, 50.f);
	data[Avenger].directions.emplace_back(0.f, 50.f);
	data[Avenger].directions.emplace_back(-45.f, 100.f);
	data[Avenger].directions.emplace_back(0.f, 50.f);
	data[Avenger].directions.emplace_back(45.f, 50.f);


	return data;
}

std::unordered_map<Projectile::Type, ProjectileData> initialProjectileData()
{
	std::unordered_map<Projectile::Type, ProjectileData> data;

	using enum Projectile::Type;
	data[AlliedBullet].damage = 10;
	data[AlliedBullet].speed = 300.f;
	data[AlliedBullet].textureID = TextureID::Bullet;

	data[EnemyBullet].damage = 10;
	data[EnemyBullet].speed = 300.f;
	data[EnemyBullet].textureID = TextureID::Bullet;

	data[Missile].damage = 200;
	data[Missile].speed = 150.f;
	data[Missile].textureID = TextureID::Missile;

	return data;
}
