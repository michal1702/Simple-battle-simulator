#pragma once

#include "SFML/Graphics.hpp"

namespace RTB
{
	class ArrowHitbox
	{
	private:
		sf::RectangleShape _hitbox;
		sf::Sprite *_arrow = nullptr;
		enum directions { up, left, down, right };
	public:
		ArrowHitbox(sf::Sprite*& arrow);

		///Changes position of hitbox as arrow is moving
		void update(short direction, float angle);

		///Draws hitbox
		void render(sf::RenderTarget& window);

		///Returns rectangle of hitbox
		sf::RectangleShape& getHitbox();

	};
}