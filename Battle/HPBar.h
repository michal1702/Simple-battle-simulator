#pragma once

#include "SFML/Graphics.hpp"

namespace RTB
{
	class HPBar
	{
	private:
		sf::RectangleShape _hp_bar, _hp_background;
		sf::Sprite* _object;
		sf::Vector2f _offset;
		short _health_points;
		float _bar_width;
	public:
		HPBar(sf::Sprite*& object, short hp);

		///Updates bar position
		void update();

		///Renders bar
		void render(sf::RenderTarget& window);

		///Shortens bar after something hit the object
		void shortenBar(short value);
	};
}