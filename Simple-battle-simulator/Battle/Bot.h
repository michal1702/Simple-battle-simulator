#pragma once

#include "Character.h"
#include "RTBPathGenerator.h"

namespace RTB
{
	class Bot :
		public Character
	{
	protected:
		AI::RTBPathGenerator* _path_generator = nullptr;
		AI::PathNode* _current_path = nullptr, * _tmp_current_path = nullptr, * _half_way = nullptr;
		sf::Vector2i _current_enemy_position, _end_path_position, _attack_position;
		bool _is_enemy_choosen = false;
		sf::Vector2i _shot_destination;
		std::list<std::shared_ptr<Character>>::iterator _choosen_enemy;

		///Function selects random enemy from the list
		///@param start begin iterator
		///@param end end iterator
		///@return choosen enemy returned as an iterator
		std::list<std::shared_ptr<Character>>::iterator _selectRandomEnemy(std::list<std::shared_ptr<Character>>::iterator start, std::list<std::shared_ptr<Character>>::iterator end);

		///Deletes path
		void _deletePath();

		///Function responsible for movement (up,down,left,right and diagonally)
		///@param time game time
		void _move(sf::Time time);
	};
}