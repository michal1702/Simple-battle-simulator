#pragma once

#include "RiDGame.h"

namespace RiD
{
	void RiDGame::Exec()
	{
		sf::Event event;
		sf::Clock clock;
		RTB::RealTimeBattle realTimeBattle(this->_data->window);

		while (this->_data->window.isOpen()) //program main loop
		{
			while (this->_data->window.pollEvent(event)) //handling events
			{
				if (event.type == sf::Event::EventType::Closed)
					this->_data->window.close();
			}

				realTimeBattle.mainLoop();
				return;

			_data->window.clear();
			_data->window.display();
		}
	}
	RiDGame::RiDGame(int width, int height, std::string title)
	{
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		_data->window.setFramerateLimit(60);
		this->Exec();
	}

	RiDGame::~RiDGame() {}
}