#pragma once

#include "SwordHitbox.h"

namespace RTB
{
	SwordHitbox::SwordHitbox(sf::Sprite*& object) :
		_object(object)
	{
		_hitbox.setFillColor(sf::Color::Transparent);
		_hitbox.setOutlineThickness(1.f);
		_hitbox.setOutlineColor(sf::Color::Green);
	}

	SwordHitbox::~SwordHitbox()
	{
		_object = nullptr;
	}

	bool SwordHitbox::checkIntersection(const sf::FloatRect& rectangle)
	{
		return _hitbox.getGlobalBounds().intersects(rectangle);
	}

	void SwordHitbox::update(short direction)
	{
		if (direction == up)
		{
			_hitbox.setSize({ 96.f, 40.f });
			_hitbox.setPosition(_object->getPosition().x - 48.f, _object->getPosition().y - 38.f);
		}
		else if (direction == down)
		{
			_hitbox.setSize({ 96.f, 48.f });
			_hitbox.setPosition(_object->getPosition().x - 48.f, _object->getPosition().y);
		}
		else if (direction == right)
		{
			_hitbox.setSize({ 64.f, 24.f });
			_hitbox.setPosition(_object->getPosition().x , _object->getPosition().y - 10.f);
		}
		else if (direction == left)
		{
			_hitbox.setSize({ 64.f, 24.f });
			_hitbox.setPosition(_object->getPosition().x - 64.f, _object->getPosition().y - 10.f);
		}
		
	}

	void SwordHitbox::render(sf::RenderTarget& window)
	{
		//window.draw(_hitbox);
	}
}