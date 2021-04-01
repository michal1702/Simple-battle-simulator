#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <list>
#include "../Engine/Movement.h"
#include "Hitbox.h"
#include "HPBar.h"
#include "SwordHitbox.h"
#include "SpearHitbox.h"
#include "Arrow.h"
#include "../Map/TileMap.h"
#include "OrientedHitbox.h"

namespace RTB
{
	class Character
	{
	protected:
		sf::Sprite* _character_sprite = nullptr;
		HPBar* _hp_bar = nullptr;
		RiD::Movement* _movement = nullptr;
		Hitbox* _hitbox = nullptr;
		short _health_points = 0;
		short _sword_damage = 0, _spear_damage = 0, _bow_damage = 0;
		sf::Vector2f _position;
		bool _is_alive = false;
		short _direction = 1;
		float _speed = 0.0;
		enum class directions { up, left, down, right };
		bool _moving_up = true, _moving_down = true, _moving_right = true, _moving_left = true;


		///Changes isometric coordinates to 2D coordinates
		///@param position position in 2D system
		sf::Vector2i _isoTo2D(sf::Vector2f position);
	public:

		///Sets character's position
		///@param position position
		virtual void setPosition(sf::Vector2f position);

		///Function responsible for all of the moves
		///@param time game time
		///@param map_objects all collidable objects to avoid
		///@param list_of_bots list of bots given as target to attack
		virtual void update(sf::Time time, std::vector<std::vector<std::unique_ptr<MapElement>>>& map_objects,
			std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderWindow& window) = 0;

		///Draws character's sprite
		///@param window render target
		virtual void render(sf::RenderWindow& window);

		///Checks if character is alive
		virtual bool isAlive();

		///Gets character position
		///@return characters position
		virtual sf::Vector2f getPosition();

		///Checks if two objects collide witch each other
		///@param Object1
		///@param Object2
		bool checkOrientedCollision(const sf::RectangleShape& Object1, const sf::RectangleShape& Object2);

		///Subtracts character's hp
		///@param value health points to subtract
		virtual void subtractHP(short value);

		///Returns character's hitbox as rectangle
		///@return rectangle hitbox
		virtual sf::RectangleShape getHitbox();

		///Dealing damage to bots of enemy team
		///@param time time needed for combat animations
		///@param list_of_bots list of possible enemies
		///@param window render window
		virtual void dealDamage(sf::Time time, std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderTarget& window) = 0;

		///Function drows dead body of a character
		///@param window render target
		virtual void deadBody(sf::RenderWindow& window);
	};
}