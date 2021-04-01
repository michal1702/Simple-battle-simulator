#pragma once

#include "Character.h"
#include <memory>

namespace RTB
{
	class Player
		:public Character
	{
	private:
		Arrow* _arrows;
		SwordHitbox* _sword_hitbox;
		sf::Vector2i _shot_destination;

		///Function responsible for dealing damage to enemies
		///@param list_of_bots list of possible enemies
		void _dealSwordDamage(std::list<std::shared_ptr<Character>>& list_of_bots);

		///Function responsible for dealing damage to enemies
		///@param list_of_bots list of possible enemies
		void _dealBowDamage(std::list<std::shared_ptr<Character>>& list_of_bots);

		///Function checks collisions with objects
		///@param map_objects all collidable objects
		void _isColidingWithTile(std::vector<std::vector<std::unique_ptr<MapElement>>>& map_objects);
	public:
		Player(sf::Texture texture, short health_points, sf::Texture& arrow_texture);
		~Player();

		///Function responsible for all of the player moves and behaviours
		///@param time game time
		///@param map_objects all collidable objects to avoid
		///@param list_of_bots list of bots given as target to attack
		void update(sf::Time time, std::vector<std::vector<std::unique_ptr<MapElement>>>& map_objects,
			std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderWindow& window);

		///Dealing damage to bots of enemy team
		///@param time time needed for combat animations
		///@param list_of_bots list of possible enemies
		///@param window render window
		void dealDamage(sf::Time time, std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderTarget& window);
	};
}