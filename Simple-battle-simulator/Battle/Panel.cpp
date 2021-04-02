#pragma once

#include "Panel.h"

namespace RTBGUI
{
	Panel::Panel()
	{
		std::string message = "          Controls\n\n\n    Walking:\n    W,S,A,D\n    Sword:\n    Space\n    Bow:\n    LMB\n    Open/Cloce this window:\n    RMB on the book\n    Pause:\n    Escape\n    Spectator(while dead):\n    LMB";
		_asset_manager.setTexture("panel", "img/Panel.png");
		_panel.setTexture(_asset_manager.getTexture("panel"));

		_message = std::make_unique<Message>(message, 28);
	}

	void Panel::update(sf::Vector2f position)
	{
		_panel.setPosition(position);
		_message->update(sf::Vector2f(position.x, position.y + 10.f));
	}

	void Panel::render(sf::RenderWindow*& window)
	{
		window->draw(_panel);
		_message->render(window);
	}
}