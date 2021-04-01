#pragma once

#include <memory>

#include "Movement.h"
#include "../Battle/RealTimeBattle.h"

namespace RiD
{
	struct gameDat 
	{
		sf::RenderWindow window;
	};

	typedef std::shared_ptr<gameDat> gameDatReference;

	class RiDGame
	{
	private:
		sf::Clock _clock;
		gameDatReference _data = std::make_shared<gameDat>();

		//Executes creation of window
		void Exec();
	public:
		/*
		Constructor that creates main window
		@param width width of the window
		@param height height of the window
		@param title title on the top bar
		*/
		RiDGame(int width, int height, std::string title);
		~RiDGame();
	};
}