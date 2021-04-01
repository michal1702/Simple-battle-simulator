#pragma once

#include "Arrow.h"

namespace RTB
{
	sf::Vector2i Arrow::_isoTo2D(sf::Vector2f position)
	{
		return sf::Vector2i(static_cast<int>(((2 * position.y + position.x) / 2) / 25), static_cast<int>(((2 * position.y - position.x) / 2) / 25));
	}

	Arrow::Arrow(sf::Sprite*& character, sf::Texture& texture) : _character(character), _is_flying(false), _change_direction(true),
		_fly_time(sf::seconds(static_cast<float>(0.8))), _start_time(sf::Time::Zero)
	{
		_sprite = new sf::Sprite;
		_sprite->setTexture(texture);
		_sprite->setTextureRect(sf::IntRect(0, 0, 32, 32));
		_sprite->setPosition(character->getPosition());
		_hitbox = new ArrowHitbox(_sprite);
		_rotation = 0.f;
	}

	Arrow::~Arrow()
	{
		delete _hitbox;
		delete _sprite;
	}

	void Arrow::update()
	{
		_sprite->setPosition(_character->getPosition().x + 2.f, _character->getPosition().y);
	}

	void Arrow::render(sf::RenderTarget& window)
	{
		window.draw(*_sprite);
		_hitbox->render(window);
	}

	void Arrow::fly(sf::Time time, sf::RenderTarget& window, sf::Vector2i destination)
	{
		if (_change_direction == true)
		{
			_is_flying = true;
			_change_direction = false;
			_start_time = time;
			sf::Vector2f current_position = _character->getPosition();
			if (destination.x - current_position.x > 0 && abs(destination.x - current_position.x) > abs(destination.y - current_position.y))
			{
				_direction = right;
				_rotation = (atan2(destination.y - current_position.y, destination.x - current_position.x) * 180) / (22 / 7);
				_sprite->setRotation(_rotation);
			}
			else if (destination.x - current_position.x < 0 && abs(destination.x - current_position.x)> abs(destination.y - current_position.y))
			{
				_direction = left;
				_rotation = (atan2(current_position.y - destination.y, current_position.x - destination.x) * 180) / (22 / 7);
				_sprite->setRotation(_rotation);
			}
			else if (destination.y - current_position.y > 0 && abs(destination.x - current_position.x) < abs(destination.y - current_position.y))
			{
				_direction = down;
				_rotation = (atan2(destination.x - current_position.x, destination.y - current_position.y) * 180) / (22 / 7);
				_sprite->setRotation(-_rotation);
			}
			else if (destination.y - current_position.y < 0 && abs(destination.x - current_position.x) < abs(destination.y - current_position.y))
			{
				_direction = up;
				_rotation = (atan2(current_position.x - destination.x, current_position.y - destination.y) * 180) / (22 / 7);
				_sprite->setRotation(-_rotation);
			}
			_deltaY = destination.y - current_position.y;
			_deltaX = destination.x - current_position.x;
		}
		if (_direction == up)
		{
			if (time - _start_time < _fly_time)
			{
				_sprite->setTextureRect(sf::IntRect(0, 0, 32, 32));
				_sprite->setOrigin(16.f, 16.f);
				_sprite->move(-(_speed *(_deltaX/ _deltaY)), -_speed);
				_hitbox->update(_direction, _rotation);
				render(window);
			}
			else
			{
				_is_flying = false;
				_change_direction = true;
			}
		}
		else if (_direction == down)
		{
			if (time - _start_time < _fly_time)
			{
				_sprite->setTextureRect(sf::IntRect(32, 0, 32, 32));
				_sprite->setOrigin(16.f, 16.f);
				_sprite->move((_speed * (_deltaX / _deltaY)), _speed);
				_hitbox->update(_direction, _rotation);
				render(window);
			}
			else
			{
				_is_flying = false;
				_change_direction = true;
			}
		}
		else if (_direction == left)
		{
			if (time - _start_time < _fly_time)
			{
				_sprite->setTextureRect(sf::IntRect(96, 0, 32, 32));
				_sprite->setOrigin(16.f, 16.f);
				_sprite->move(-_speed, -_speed * (_deltaY/_deltaX));
				_hitbox->update(_direction, _rotation);
				render(window);
			}
			else
			{
				_is_flying = false;
				_change_direction = true;
			}
		}
		else if (_direction == right)
		{
			if (time - _start_time < _fly_time)
			{
				_sprite->setTextureRect(sf::IntRect(64, 0, 32, 32));
				_sprite->setOrigin(16.f, 16.f);
				_sprite->move(_speed, _speed * (_deltaY / _deltaX));
				_hitbox->update(_direction, _rotation);
				render(window);
			}
			else
			{
				_is_flying = false;
				_change_direction = true;
			}

		}
	}

	bool Arrow::isFlying()
	{
		return _is_flying;
	}

	sf::Vector2f Arrow::getPosition()
	{
		return _sprite->getPosition();
	}

	sf::RectangleShape Arrow::getHitbox()
	{
		return this->_hitbox->getHitbox();
	}
}