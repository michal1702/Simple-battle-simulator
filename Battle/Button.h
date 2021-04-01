#pragma once

#include <memory>
#include "../Engine/AssetManager.h"
#include "Message.h"

namespace RTBGUI
{
	class Button
	{
	private:
		std::unique_ptr<Message> _text;
		sf::Sprite _rectangular_button, _rectangular_button_pressed;
		RiD::AssetManager _asset_manager;
		bool _is_hovered;
	public:
		Button(std::string text);

		void update(sf::Vector2f position);

		void render(sf::RenderWindow*&window);

		void setHovered(bool hover);

		sf::Sprite getSprite();
	};
}