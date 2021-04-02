#pragma once

#include "../Engine/AssetManager.h"

namespace RTBGUI
{
	class BookButton
	{
	private:
		sf::Sprite _book, _book_hovered;
		RiD::AssetManager _asset_manager;
		bool _is_hovered;
	public:
		BookButton();

		void update(sf::Vector2f position);

		void render(sf::RenderWindow*& window);

		void setHovered(bool hover);

		sf::Sprite getSprite();
	};
}