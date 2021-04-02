#pragma once

#include "MapElement.h"

namespace RTB
{
	MapElement::MapElement(sf::Texture* ground, sf::Vector2f position)
	{
		_ground_sprite = std::make_unique<sf::Sprite>();
		_ground_sprite->setTexture(*ground);
		_ground_sprite->setPosition(position);
		_walkable = true;
	}

	void MapElement::setFlora(sf::Texture* flora, sf::Vector2f position)
	{
		_flora_sprite = std::make_unique<sf::Sprite>();
		_flora_sprite->setTexture(*flora);
		_flora_sprite->setPosition(position);
	}

	void MapElement::setObject(sf::Texture* object, sf::Vector2f position, sf::Vector2f origin, sf::Vector2f hitbox_size, sf::Vector2f hitbox_position_offset, float hitbox_rotation_angle)
	{
		_object_sprite = std::make_unique<sf::Sprite>();
		_object_sprite->setTexture(*object);
		_object_sprite->setOrigin(origin);
		_object_sprite->setPosition(position);
		_hitbox.setOutlineColor(sf::Color::Green);
		_hitbox.setOutlineThickness(1.f);
		_hitbox.setFillColor(sf::Color::Transparent);
		_hitbox.setPosition(_object_sprite->getPosition().x + hitbox_position_offset.x, _object_sprite->getPosition().y + hitbox_position_offset.y);
		_hitbox.rotate(hitbox_rotation_angle);
		_hitbox.setSize(sf::Vector2f(hitbox_size.x, hitbox_size.y));
		_walkable = false;
	}
	sf::Sprite MapElement::getGround()
	{
		return *_ground_sprite;
	}
	sf::Sprite MapElement::getFlora()
	{
		return *_flora_sprite;
	}
	sf::Sprite MapElement::getObjects()
	{
		return *_object_sprite;
	}
	sf::RectangleShape MapElement::getObjectsHitbox()
	{
		return _hitbox;
	}
	bool MapElement::isFloraNull()
	{
		if (_flora_sprite == nullptr)
			return true;
		else
			return false;
	}

	bool MapElement::isObjectNull()
	{
		if (_object_sprite == nullptr)
			return true;
		else
			return false;
	}

	bool MapElement::isWalkable()
	{
		return _walkable;
	}
}