#pragma once

#include "WindowBorder.h"

namespace RTBGUI
{
	WindowBorder::WindowBorder()
	{
		_asset_manager.setTexture("window_border", "img/WindowBorder.png");
		_window_border.setTexture(_asset_manager.getTexture("window_border"));
	}


	void WindowBorder::update(sf::Vector2f position)
	{
		_window_border.setPosition(position);
	}

	void WindowBorder::render(sf::RenderWindow*& window)
	{
		window->draw(_window_border);
	}
}