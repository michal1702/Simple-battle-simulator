#pragma once

#include <memory>
#include "SFML/Graphics.hpp"

namespace RTB
{
	class MapElement
	{
	private:
		std::unique_ptr<sf::Sprite> _object_sprite = nullptr, _ground_sprite = nullptr, _flora_sprite = nullptr;
		sf::Vector2u _object_sprite_size, _ground_sprite_size, _flora_sprite_size;
		sf::RectangleShape _hitbox;
		bool _walkable;
	public:
		MapElement(sf::Texture* ground, sf::Vector2f position);

		///Places flora elements like flowers
		void setFlora(sf::Texture* flora, sf::Vector2f position);

		///Places collidable elements trees etc.
		void setObject(sf::Texture* object, sf::Vector2f position, sf::Vector2f origin, sf::Vector2f hitbox_size, sf::Vector2f hitbox_position_offset, float hitbox_rotation_angle);

		sf::Sprite getGround();
		sf::Sprite getFlora();
		sf::Sprite getObjects();
		sf::RectangleShape getObjectsHitbox();

		bool isFloraNull();
		bool isObjectNull();
		bool isWalkable();
	};
}