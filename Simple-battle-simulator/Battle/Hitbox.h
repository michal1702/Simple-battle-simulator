#pragma once

#include <sstream>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Engine/AssetManager.h"

namespace RTB
{
	class Hitbox
	{
	private:
		RiD::AssetManager _asset_manager;
		sf::Text _cords_map;
		sf::RectangleShape _hitbox;
		sf::Sprite *_object;
		sf::Vector2f _offset;

		sf::Vector2f _isoTo2D(sf::Vector2f position);
	public:
		Hitbox(sf::Sprite *&object, sf::Vector2f size, sf::Vector2f offset);
		~Hitbox();

		///Checks if hitbox collides with another object's hitbox given as rectangle
		bool checkIntersection(const sf::FloatRect& rectangle);

		///Updates hitbox position
		void update();

		///Renders hitbox on the window
		void render(sf::RenderTarget& window);

		///Returns rectangle of hitbox
		sf::RectangleShape& getRectangle();
	};
}