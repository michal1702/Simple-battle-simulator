#pragma once

#include "Button.h"

namespace RTBGUI
{
	Button::Button(std::string text) :
		_is_hovered(false)
	{
		_text = std::make_unique<Message>(text, 30);
		_asset_manager.setTexture("rectButton", "img/MenuButtonPressed.png");
		_asset_manager.setTexture("rectButtonPressed", "img/MenuButtonPreLight.png");

		_rectangular_button.setTexture(_asset_manager.getTexture("rectButton"));
		_rectangular_button_pressed.setTexture(_asset_manager.getTexture("rectButtonPressed"));
	}

	void Button::update(sf::Vector2f position)
	{
		_rectangular_button.setPosition(position);
		_rectangular_button_pressed.setPosition(position);
		_text->update(sf::Vector2f(position.x + 108.f, position.y + 6.f));
	}

	void Button::render(sf::RenderWindow*& window)
	{
		if (_is_hovered)
		{
			window->draw(_rectangular_button_pressed);
			_text->render(window);
		}
		else
		{
			window->draw(_rectangular_button);
			_text->render(window);
		}	
		_is_hovered = false;
	}

	void Button::setHovered(bool hover)
	{
		_is_hovered = hover;
	}

	sf::Sprite Button::getSprite()
	{
		return _rectangular_button;
	}
}