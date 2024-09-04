#pragma once

#include "command.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class SceneNode
	:public sf::Transformable,
	 public sf::Drawable,
	 private sf::NonCopyable
{
public:
	using NodePtr = std::unique_ptr<SceneNode>;

public:
	SceneNode();

	void attachChild(NodePtr child);

	NodePtr detachChild(const SceneNode& node);

	void update(sf::Time dt);

	sf::Vector2f getWorldPosition() const;

	sf::Transform getWorldTransform() const;

	void onCommand(const Command& command, sf::Time dt);

	virtual Category getCategory() const;

private:
	virtual void updateCurrent(sf::Time dt);

	void updateChildren(sf::Time dt) const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<NodePtr> _children;
	SceneNode* _parent;
};
