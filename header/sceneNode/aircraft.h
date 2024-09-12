#pragma once

#include "entity.h"
#include "projectile.h"
#include "textNode.h"

#include "common/resourceHolder.h"

class Aircraft final : public Entity
{
public:
	enum class Type : std::size_t
	{
		Eagle,
		Raptor,
		Avenger,
		Count
	};

	explicit Aircraft(Type type, const TextureHolder& textureHolder,const FontHolder& fontHolder);

	Category getCategory() const override;

	sf::FloatRect getBoundingRect() const override;

	bool isMarkedForRemoval() const override;

	bool isAllied() const;

	float getMaxSpeed() const;

	void increaseFireRate();

	void increaseSpread();

	void collectMissiles(unsigned int count);

	void fire();

	void launchMissile();

private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateCurrent(sf::Time dt, CommandQueue& commandQueue) override;

	void updateMovementPattern(sf::Time dt);

	void checkPickupDrop(CommandQueue& commandQueue);

	void checkProjectileLaunch(sf::Time dt, CommandQueue& commandQueue);

	void createBullets(SceneNode& node, const TextureHolder& textureHolder) const;

	void createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset,
	                      const TextureHolder& textureHolder) const;


	void createPickup(SceneNode& node, const TextureHolder& textureHolder) const;

	void updateTexts() const;

	Type _type;
	sf::Sprite _sprite;
	Command _fireCommand{};
	Command _missileCommand{};
	Command _dropPickupCommand{};

	sf::Time _fireCountdown{sf::Time::Zero};

	bool _isFiring{false};
	bool _isLaunchingMissile{false};
	bool _isMarkedForRemoval{false};

	int _fireRateLevel{1};
	int _spreadLevel{1};
	int _missileAmmo{2};


	float _travelledDistance{0.f};
	std::size_t _directionIndex{0};

	TextNode* _healthDisplay{nullptr};
	TextNode* _missileDisplay{nullptr};
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
