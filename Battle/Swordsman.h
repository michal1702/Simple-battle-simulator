#pragma once

#include "Bot.h"
#include "RTBPathGenerator.h"

namespace RTB
{
	class Swordsman
		:public Bot
	{
	private:
		SwordHitbox* _sword_hitbox;

		///Function responsible for dealing damage to enemies
		///@param list_of_bots list of possible enemies
		void _dealSwordDamage(std::list<std::shared_ptr<Character>>& list_of_bots);

	public:
		Swordsman(sf::Texture texture, short health_points, std::vector<std::vector<AI::PathNode>>& walkable_area);
		~Swordsman();

		///Function responsible for all of the behaviours
		///@param time game time
		///@param map_objects all collidable objects to avoid
		///@param list_of_bots list of bots given as target to attack
		void update(sf::Time time, std::vector<std::vector<std::unique_ptr<MapElement>>>& map_objects,
			std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderWindow& window);

		///Dealing damage to Swordsmans of enemy team
		///@param time time needed for combat animations
		///@param list_of_Swordsmans list of possible enemies
		///@param window render window
		void dealDamage(sf::Time time, std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderTarget& window);
	};
}