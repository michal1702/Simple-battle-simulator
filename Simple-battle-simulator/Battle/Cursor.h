#pragma once

#include "../Engine/AssetManager.h"

namespace RTBGUI
{
	class Cursor
	{
	private:
		sf::Sprite _cursor;
		RiD::AssetManager _asset_manager;
	public:

		Cursor();

		void update(sf::Vector2f position);

		void render(sf::RenderWindow*& window);
	};
}