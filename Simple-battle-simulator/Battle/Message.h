#pragma once

#include "../Engine/AssetManager.h"

namespace RTBGUI
{
	class Message
	{
	private:
		sf::Text _message, _shadow;
		RiD::AssetManager _asset_manager;
	public:
		Message(std::string message, int size);

		void update(sf::Vector2f position);

		void render(sf::RenderWindow*& window);
	};
}