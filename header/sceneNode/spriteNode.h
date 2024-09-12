#pragma once
#include "common/sceneNode.h"

class SpriteNode : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture& texture);

	SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite _sprite;
};

