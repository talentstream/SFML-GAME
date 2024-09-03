#include "world.h"

#include "spriteNode.h"

World::World(sf::RenderWindow& window) :
	_window{window},
	_worldView{window.getDefaultView()},
	_textureHolder{},
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

	auto position = _playerAircraft->getPosition();
	auto velocity = _playerAircraft->getVelocity();

	if (position.x <= _worldBounds.left + 150.f ||
		position.x >= _worldBounds.left + _worldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		_playerAircraft->setVelocity(velocity);
	}

	_sceneGraph.update(dt);
}

void World::draw()
{

	_window.setView(_worldView);
	_window.draw(_sceneGraph);
}

void World::loadTextures()
{
	_textureHolder.load(Textures::ID::Eagle, "resource/Eagle.png");
	_textureHolder.load(Textures::ID::Raptor, "resource/Raptor.png");
	_textureHolder.load(Textures::ID::Desert, "resource/Desert.png");
}

void World::buildScene()
{
	for (auto i = 0; i < static_cast<size_t>(Layer::Count); i++)
	{
		auto layer = std::make_unique<SceneNode>();
		_sceneLayers[static_cast<Layer>(i)] = layer.get();
		_sceneGraph.attachChild(std::move(layer));
	}

	auto& texture = _textureHolder.get(Textures::ID::Desert);
	sf::IntRect textureRect{ _worldBounds };
	texture.setRepeated(true);
	
	auto backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
	backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);
	_sceneLayers[Layer::Background]->attachChild(std::move(backgroundSprite));

	auto leader = std::make_unique<Aircraft>(Aircraft::Type::Eagle, _textureHolder);
	_playerAircraft = leader.get();
	_playerAircraft->setPosition(_spawnPosition);
	_playerAircraft->setVelocity(40.f, _scrollSpeed);
	_sceneLayers[Layer::Air]->attachChild(std::move(leader));

	auto leftEscort = std::make_unique<Aircraft>(Aircraft::Type::Raptor, _textureHolder);
	leftEscort->setPosition(-80.f, 50.f);
	_playerAircraft->attachChild(std::move(leftEscort));

	auto rightEscort = std::make_unique<Aircraft>(Aircraft::Type::Raptor, _textureHolder);
	rightEscort->setPosition(80.f, 50.f);
	_playerAircraft->attachChild(std::move(rightEscort));
}
