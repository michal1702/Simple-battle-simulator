#pragma once

#include "Message.h"

namespace RTBGUI
{
	Message::Message(std::string message, int size)
	{
		_asset_manager.setFont("CloisterBlack", "Fonts/CloisterBlack.ttf");
		_message.setFont(_asset_manager.getFont("CloisterBlack"));
		_message.setFillColor(sf::Color::White);
		_message.setCharacterSize(size);
		_message.setString(message);

		_shadow.setFont(_asset_manager.getFont("CloisterBlack"));
		_shadow.setFillColor(sf::Color::Black);
		_shadow.setCharacterSize(size+1);
		_shadow.setString(message);
	}

	void Message::update(sf::Vector2f position)
	{
		_message.setPosition(position);
		_shadow.setPosition(position.x - 4.f, position.y - 2.f);
	}

	void Message::render(sf::RenderWindow*& window)
	{
		window->draw(_shadow);
		window->draw(_message);
	}
}