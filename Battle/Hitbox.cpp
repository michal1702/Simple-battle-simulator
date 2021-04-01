#include "Hitbox.h"

#pragma once

namespace RTB
{
	sf::Vector2f Hitbox::_isoTo2D(sf::Vector2f position)
	{
		return sf::Vector2f((2 * position.y + position.x) / 2, (2 * position.y - position.x) / 2);
	}

	Hitbox::Hitbox(sf::Sprite*& object, sf::Vector2f size, sf::Vector2f offset):
		_object(object), _offset(offset)
	{
		_hitbox.setPosition(_object->getPosition().x + offset.x, _object->getPosition().y + offset.y);
		_hitbox.setSize(size);
		_hitbox.setFillColor(sf::Color::Transparent);
		_hitbox.setOutlineThickness(1.f);
		_hitbox.setOutlineColor(sf::Color::Green);
		_asset_manager.setFont("arial", "Fonts/arial.ttf");
		_cords_map.setFont(_asset_manager.getFont("arial"));
		_cords_map.setFillColor(sf::Color::Green);
		_cords_map.setCharacterSize(10);
	}

	Hitbox::~Hitbox()
	{
		_object = nullptr;
	}

	bool Hitbox::checkIntersection(const sf::FloatRect& rectangle)
	{
		return _hitbox.getGlobalBounds().intersects(rectangle);
	}

	void Hitbox::update()
	{
		_hitbox.setPosition(_object->getPosition().x + _offset.x, _object->getPosition().y + _offset.y);
		sf::Vector2f position = _object->getPosition();
		position = this->_isoTo2D(position);
		position.x /= 25;
		position.y /= 25;
		std::ostringstream sstream;
		sstream << "x:" << (int)position.x << " y: " << (int)position.y+1;
		std::string text(sstream.str());
		_cords_map.setString(text);
		_cords_map.setPosition(_object->getPosition().x + _offset.x + 28, _object->getPosition().y + _offset.y);
	}

	void Hitbox::render(sf::RenderTarget& window)
	{
		window.draw(_cords_map);
		window.draw(_hitbox);
	}
	sf::RectangleShape& Hitbox::getRectangle()
	{
		return _hitbox;
	}
}