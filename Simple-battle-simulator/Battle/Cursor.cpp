#pragma once

#include "Cursor.h"

namespace RTBGUI
{
	Cursor::Cursor()
	{
		_asset_manager.setTexture("cursor", "img/Hand.png");
		_asset_manager.setFont("CloisterBlack", "Fonts/CloisterBlack.ttf");
		_cursor.setTexture(_asset_manager.getTexture("cursor"));
		_cursor.setOrigin(18.f, 14.f);
	}

	void Cursor::update(sf::Vector2f position)
	{
		_cursor.setPosition(position);
	}

	void Cursor::render(sf::RenderWindow*& window)
	{
		window->draw(_cursor);
	}
}