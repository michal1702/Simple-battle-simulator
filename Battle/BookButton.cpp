#pragma once

#include "BookButton.h"

namespace RTBGUI
{
	RTBGUI::BookButton::BookButton():
		_is_hovered(false)
	{
		_asset_manager.setTexture("book", "img/controls.png");
		_asset_manager.setTexture("book_hovered", "img/controlsPreLight.png");
		_book.setTexture(_asset_manager.getTexture("book"));
		_book_hovered.setTexture(_asset_manager.getTexture("book_hovered"));
	}

	void RTBGUI::BookButton::update(sf::Vector2f position)
	{
		_book.setPosition(position);
		_book_hovered.setPosition(position);
	}

	void RTBGUI::BookButton::render(sf::RenderWindow*& window)
	{
		if (_is_hovered)
			window->draw(_book_hovered);
		else
			window->draw(_book);

		_is_hovered = false;
	}

	void BookButton::setHovered(bool hover)
	{
		_is_hovered = hover;
	}

	sf::Sprite BookButton::getSprite()
	{
		return _book;
	}
}
