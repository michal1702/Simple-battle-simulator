#pragma once

#include "Message.h"

namespace RTBGUI
{
	class Panel
	{
	private:
		sf::Sprite _panel;
		std::unique_ptr<Message> _message;
		RiD::AssetManager _asset_manager;
	public:
		Panel();

		void update(sf::Vector2f position);

		void render(sf::RenderWindow*& window);
	};
}