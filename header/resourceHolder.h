#pragma once

#include <string_view>
#include <stdexcept>
#include <cassert>
#include <memory>
#include <map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

template <typename Resource, typename Identifier>
class ResourceHolder
{
	using ResourcePtr = std::unique_ptr<Resource>;

public:
	ResourceHolder() = default;

	~ResourceHolder() = default;

	void load(Identifier id, std::string_view filename);

	template <typename Parameter>
	void load(Identifier id, std::string_view filename, const Parameter& parameter);

	Resource& get(Identifier id);

	const Resource& get(Identifier id) const;

private:
	void insertResource(Identifier id, ResourcePtr resource);

	std::map<Identifier, ResourcePtr> _resourceMap;
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, std::string_view filename)
{
	auto resource = std::make_unique<Resource>();

	if (!resource->loadFromFile(filename.data()))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + std::string(filename));
	}

	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, std::string_view filename, const Parameter& parameter)
{
	auto resource = std::make_unique<Resource>();

	if (!resource->loadFromFile(filename, parameter))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + std::string(filename));
	}

	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = _resourceMap.find(id);
	assert(found != _resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = _resourceMap.find(id);
	assert(found != _resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, ResourcePtr resource)
{
	auto inserted = _resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}


namespace Textures
{
	enum class ID
	{
		Landscape,
		Airplane,
		Missile,
		Eagle,
		Raptor,
		Desert
	};
}

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

namespace Fonts
{
	enum class ID
	{
		Main
	};
}

using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;
