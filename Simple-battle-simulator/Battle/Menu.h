#pragma once

#include "../Engine/AssetManager.h"

namespace RTBGUI
{
	class Menu
	{
	private:
		sf::Sprite _menu;
		RiD::AssetManager _asset_manager;
	public:

		Menu();

		void update(sf::Vector2f position);

		void render(sf::RenderWindow*& window);
	};
}