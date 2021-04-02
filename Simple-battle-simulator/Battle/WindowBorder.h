#pragma once

#include "../Engine/AssetManager.h"

namespace RTBGUI
{
	class WindowBorder
	{
	private:
		sf::Sprite _window_border;
		RiD::AssetManager _asset_manager;
	public:
		WindowBorder();

		void update(sf::Vector2f position);

		void render(sf::RenderWindow*& window);
	};
}