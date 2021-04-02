#pragma once

#include "SpearHitbox.h"

namespace RTB
{
	SpearHitbox::SpearHitbox(sf::Sprite*& object):
		_object(object)
	{
		_hitbox.setFillColor(sf::Color::Transparent);
		_hitbox.setOutlineThickness(1.f);
		_hitbox.setOutlineColor(sf::Color::Green);
	}

	SpearHitbox::~SpearHitbox()
	{
		_object = nullptr;
	}

	bool SpearHitbox::checkIntersection(const sf::FloatRect& rectangle)
	{
		return _hitbox.getGlobalBounds().intersects(rectangle);
	}

	void SpearHitbox::update(short direction)
	{
		if (direction == up)
		{
			_hitbox.setSize({ 8.f, 64.f });
			_hitbox.setPosition(_object->getPosition().x, _object->getPosition().y - 64.f);
		}
		else if (direction == down)
		{
			_hitbox.setSize({ 8.f, 64.f });
			_hitbox.setPosition(_object->getPosition().x - 8.f, _object->getPosition().y);
		}
		else if (direction == right)
		{
			_hitbox.setSize({ 64.f, 8.f });
			_hitbox.setPosition(_object->getPosition().x, _object->getPosition().y + 8.f);
		}
		else if (direction == left)
		{
			_hitbox.setSize({ 64.f, 8.f });
			_hitbox.setPosition(_object->getPosition().x - 64.f, _object->getPosition().y + 8.f);
		}
	}

	void SpearHitbox::render(sf::RenderTarget& window)
	{
		//window.draw(_hitbox);
	}
}