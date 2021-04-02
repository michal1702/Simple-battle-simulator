#pragma once

#include "Menu.h"

namespace RTBGUI
{
	Menu::Menu()
	{
		_asset_manager.setTexture("menu", "img/MenuWindow.png");
		_menu.setTexture(_asset_manager.getTexture("menu"));
	}

	void Menu::update(sf::Vector2f position)
	{
		_menu.setPosition(position);
	}

	void Menu::render(sf::RenderWindow*& window)
	{
		window->draw(_menu);
	}
}