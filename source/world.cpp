#include "world.h"

#include "sceneNode/spriteNode.h"
#include "common/utility.h"

#include <ranges>
#include <variant>

World::World(sf::RenderWindow& window, FontHolder& fontHolder) :
	_window{window},
	_worldView{window.getDefaultView()},
	_textureHolder{},
	_fontHolder{fontHolder},
	_sceneGraph{},
	_sceneLayers{},
	_worldBounds{0.f, 0.f, _worldView.getSize().x, 2000.f},
	_spawnPosition{_worldView.getSize().x / 2.f, _worldBounds.height - _worldView.getSize().y / 2.f},
	_scrollSpeed{-50.f},
	_playerAircraft{nullptr}
{
	loadTextures();
	buildScene();

	_worldView.setCenter(_spawnPosition);
}

void World::update(sf::Time dt)
{
	_worldView.move(0.f, _scrollSpeed * dt.asSeconds());
	_playerAircraft->setVelocity(0.f, 0.f);

	destroyEntitiesOutsideView();
	guideMissiles();

	while (_commandQueue.isEmpty() == false)
	{
		_sceneGraph.onCommand(_commandQueue.pop(), dt);
	}
	adaptPlayerVelocity();

	spawnEnemies();

	_sceneGraph.update(dt, _commandQueue);
	adaptPlayerPosition();
}

void World::draw()
{
	_window.setView(_worldView);
	_window.draw(_sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return _commandQueue;
}

void World::loadTextures()
{
	_textureHolder.load(TextureID::Eagle, "resource/Eagle.png");
	_textureHolder.load(TextureID::Raptor, "resource/Raptor.png");
	_textureHolder.load(TextureID::Desert, "resource/Desert.png");
	_textureHolder.load(TextureID::Avenger, "resource/Avenger.png");

	_textureHolder.load(TextureID::Bullet, "resource/Bullet.png");
	_textureHolder.load(TextureID::Missile, "resource/Missile.png");

	_textureHolder.load(TextureID::HealthRefill, "resource/HealthRefill.png");
	_textureHolder.load(TextureID::MissileRefill, "resource/MissileRefill.png");
	_textureHolder.load(TextureID::FireSpread, "resource/FireSpread.png");
	_textureHolder.load(TextureID::FireRate, "resource/FireRate.png");
}

void World::buildScene()
{
	for (auto i = 0; i < std::to_underlying(Layer::Count); i++)
	{
		auto layer = std::make_unique<SceneNode>();
		_sceneLayers[static_cast<Layer>(i)] = layer.get();
		_sceneGraph.attachChild(std::move(layer));
	}

	auto& texture = _textureHolder.get(TextureID::Desert);
	sf::IntRect textureRect{_worldBounds};
	texture.setRepeated(true);

	auto backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
	backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);
	_sceneLayers[Layer::Background]->attachChild(std::move(backgroundSprite));

	auto leader = std::make_unique<Aircraft>(Aircraft::Type::Eagle, _textureHolder, _fontHolder);
	_playerAircraft = leader.get();
	_playerAircraft->setPosition(_spawnPosition);
	_playerAircraft->setVelocity(40.f, _scrollSpeed);
	_sceneLayers[Layer::Air]->attachChild(std::move(leader));

	auto leftEscort = std::make_unique<Aircraft>(Aircraft::Type::Raptor, _textureHolder, _fontHolder);
	leftEscort->setPosition(-80.f, 50.f);
	_playerAircraft->attachChild(std::move(leftEscort));

	auto rightEscort = std::make_unique<Aircraft>(Aircraft::Type::Raptor, _textureHolder, _fontHolder);
	rightEscort->setPosition(80.f, 50.f);
	_playerAircraft->attachChild(std::move(rightEscort));
}

void World::addEnemies()
{
	addEnemy(Aircraft::Type::Raptor, 0.f, 500.f);
	addEnemy(Aircraft::Type::Raptor, 0.f, 1000.f);
	addEnemy(Aircraft::Type::Raptor, +100.f, 1100.f);
	addEnemy(Aircraft::Type::Raptor, -100.f, 1100.f);
	addEnemy(Aircraft::Type::Avenger, -70.f, 1400.f);
	addEnemy(Aircraft::Type::Avenger, -70.f, 1600.f);
	addEnemy(Aircraft::Type::Avenger, 70.f, 1400.f);
	addEnemy(Aircraft::Type::Avenger, 70.f, 1600.f);

	namespace ranges = std::ranges;
	ranges::sort(_enemySpawnPoints, ranges::less{}, &SpawnPoint::y);
}

void World::addEnemy(Aircraft::Type type, float relX, float relY)
{
}

void World::spawnEnemies()
{
	while (_enemySpawnPoints.empty() == false &&
		_enemySpawnPoints.back().y > getBattlefieldBounds().top)
	{
		auto spawnPoint = _enemySpawnPoints.back();

		auto enemy = std::make_unique<Aircraft>(Aircraft::Type::Raptor, _textureHolder, _fontHolder);
		enemy->setPosition(spawnPoint.x, spawnPoint.y);
		enemy->setRotation(180.f);
		_sceneLayers[Layer::Air]->attachChild(std::move(enemy));

		_enemySpawnPoints.pop_back();
	}
}

void World::destroyEntitiesOutsideView()
{
	Command command;
	command._category = Category::EnemyAircraft | Category::AlliedProjectile;
	command._action = derivedAction<Entity>([this](Entity& entity, sf::Time)
	{
		if (!getBattlefieldBounds().intersects(entity.getBoundingRect()))
		{
			entity.destroy();
		}
	});

	_commandQueue.push(command);
}

void World::guideMissiles()
{
	Command enemyCollectorCommand;
	enemyCollectorCommand._category = Category::EnemyAircraft;
	enemyCollectorCommand._action = derivedAction<Aircraft>([this](Aircraft& enemy, sf::Time)
	{
		if (!enemy.isDestroyed())
		{
			_activeEnemies.push_back(&enemy);
		}
	});

	Command missileGuiderCommand;
	missileGuiderCommand._category = Category::AlliedProjectile;
	missileGuiderCommand._action = derivedAction<Projectile>([this](Projectile& missile, sf::Time)
	{
		if(!missile.isGuided())
		{
			return;
		}
		float minDistance = std::numeric_limits<float>::max();
		Aircraft* closestEnemy = nullptr;
		for(const auto& enemy : _activeEnemies)
		{
			float enemyDistance = SceneNode::distance(missile, *enemy);

			if(enemyDistance < minDistance)
			{
				minDistance = enemyDistance;
				closestEnemy = enemy;
			}
		}

		if(closestEnemy != nullptr)
		{
			missile.guideTowards(closestEnemy->getWorldPosition());
		}
	});

	_commandQueue.push(enemyCollectorCommand);
	_commandQueue.push(missileGuiderCommand);
	_activeEnemies.clear();
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect{
		_worldView.getCenter() - _worldView.getSize() / 2.f,
		_worldView.getSize()
	};
}

sf::FloatRect World::getBattlefieldBounds() const
{
	auto bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}

void World::adaptPlayerPosition() const
{
	sf::FloatRect viewBounds{_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize()};
	constexpr float borderDistance = 40.f;

	sf::Vector2f position = _playerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	_playerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	auto velocity = _playerAircraft->getVelocity();

	if (velocity.x != 0.f && velocity.y != 0.f)
	{
		_playerAircraft->setVelocity(velocity / std::sqrt(2.f));
	}

	_playerAircraft->accelerate(0.f, -_scrollSpeed);
}
