#pragma once

#include "ArrowHitbox.h"

namespace RTB
{
	ArrowHitbox::ArrowHitbox(sf::Sprite*& arrow) : _arrow(arrow)
	{
		_hitbox.setFillColor(sf::Color::Transparent);
		_hitbox.setOutlineThickness(1.f);
		_hitbox.setOutlineColor(sf::Color::Green);
	}

	void ArrowHitbox::update(short direction, float angle)
	{
		if (direction == up)
		{
			_hitbox.setRotation(-angle);
			_hitbox.setSize({ 6.f, 32.f });
			_hitbox.setPosition(_arrow->getPosition().x - 4.f - (0.3f * angle), _arrow->getPosition().y - 14.f + (0.1f * angle));
		}
		else if (direction == down)
		{
			_hitbox.setRotation(-angle);
			_hitbox.setSize({ 6.f, 32.f });
			_hitbox.setPosition(_arrow->getPosition().x - 2.f - (0.3f * angle), _arrow->getPosition().y - 14.f + (0.1f * angle));
		}
		else if (direction == right)
		{
			_hitbox.setRotation(angle);
			_hitbox.setSize({ 32.f, 6.f });
			_hitbox.setPosition(_arrow->getPosition().x - 14.f + (0.1f * angle), _arrow->getPosition().y - 4.f - (0.3f * angle));
		}
		else if (direction == left)
		{
			_hitbox.setRotation(angle);
			_hitbox.setSize({ 32.f, 6.f });
			_hitbox.setPosition(_arrow->getPosition().x - 14.f - (0.1f * angle), _arrow->getPosition().y - 4.f - (0.3f * angle));
		}
	}

	void ArrowHitbox::render(sf::RenderTarget& window)
	{
		//window.draw(_hitbox);
	}

	sf::RectangleShape& ArrowHitbox::getHitbox()
	{
		return _hitbox;
	}
}