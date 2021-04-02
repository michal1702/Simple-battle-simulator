#pragma once

#include <cmath>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ArrowHitbox.h"

namespace RTB
{
	class Arrow
	{
	private:
		ArrowHitbox *_hitbox = nullptr;
		sf::Sprite *_sprite = nullptr;
		sf::Sprite* _character;
		sf::Time _fly_time, _start_time;
		enum directions { up, left, down, right };
		bool _is_flying, _change_direction;
		short _direction;
		float _speed = 7.f, _rotation, _deltaX, _deltaY, _B;

		sf::Vector2i _isoTo2D(sf::Vector2f position);
	public:
		Arrow(sf::Sprite*& character, sf::Texture& texture);
		~Arrow();

		///Updates arrow starting position
		void update();

		///Renders arrow
		void render(sf::RenderTarget& window);

		///Function responsible for moving arrow
		void fly(sf::Time time, sf::RenderTarget& window, sf::Vector2i destination);

		///Checks if arrow is flying
		bool isFlying();

		///Gets arrow position
		sf::Vector2f getPosition();

		sf::RectangleShape getHitbox();
	};
}