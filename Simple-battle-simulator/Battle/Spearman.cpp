#pragma once

#include "Spearman.h"

namespace RTB
{
	void Spearman::_dealSpearDamage(std::list<std::shared_ptr<Character>>& list_of_bots)
	{
		for (std::list<std::shared_ptr<Character>>::iterator iterator = list_of_bots.begin();//Iterates through list of bots...
			iterator != list_of_bots.end(); iterator++)
		{
			if ((*iterator)->isAlive() && _spear_hitbox->checkIntersection((*iterator)->getHitbox().getGlobalBounds()) == true)//checks if spear intersected one of them...
			{
				(*iterator)->subtractHP(_spear_damage);//and subtracts hp
			}
		}
		_movement->notReadyToDealSpearDamage();
	}


	Spearman::Spearman(sf::Texture texture, short health_points, std::vector<std::vector<AI::PathNode>>& walkable_area):
		_spear_hitbox(nullptr)
	{
		_path_generator = new AI::RTBPathGenerator(walkable_area);
		_health_points = health_points;
		_character_sprite = new sf::Sprite;
		_movement = new RiD::Movement(texture, _character_sprite);
		_hitbox = new Hitbox(_character_sprite, { 24.f, 46.f }, { -12.f,-16.f });
		_spear_hitbox = new SpearHitbox(_character_sprite);
		_hp_bar = new HPBar(_character_sprite, _health_points);
		_is_alive = true;
		_is_enemy_choosen = false;
		_speed = 0.3f;
		_spear_damage = 10;
	}

	Spearman::~Spearman()
	{
		delete _movement;
		delete _hitbox;
		delete _character_sprite;
		delete _hp_bar;
		delete _spear_hitbox;
		delete _path_generator;
		_deletePath();
	}

	void Spearman::update(sf::Time time, std::vector<std::vector<std::unique_ptr<MapElement>>>& map_objects, std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderWindow& window)
	{
		_position = _movement->getSprite().getPosition();
		if (!_movement->isSpearTriggered())
		{
			if (_is_enemy_choosen)
			{
				_current_enemy_position = _isoTo2D((*_choosen_enemy)->getPosition());
				_move(time);
			}
			else
			{
				_deletePath();
				_choosen_enemy = _selectRandomEnemy(list_of_bots.begin(), list_of_bots.end());
				_current_enemy_position = _isoTo2D((*_choosen_enemy)->getPosition());
				_is_enemy_choosen = true;

			}
		}
		if (!(*_choosen_enemy)->isAlive())
			_is_enemy_choosen = false;
		else
		{
			float distance;
			distance = static_cast<float>(sqrt(pow((_isoTo2D((*_choosen_enemy)->getPosition()).x - _isoTo2D(_position).x), 2) + pow((_isoTo2D((*_choosen_enemy)->getPosition()).y - _isoTo2D(_position).y), 2)));
			if (distance < 2.7)
				_movement->triggerSpear();
		}
		_hitbox->update();
		_hp_bar->update();

		if (_movement->isDeathTriggered())
		{
			_deletePath();
			_movement->death(time);
			if (_movement->isDeathTriggered() == false)
			{
				_is_alive = false;
				_deletePath();
			}
		}
	}

	void Spearman::dealDamage(sf::Time time, std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderTarget& window)
	{
		if (_movement->isSpearTriggered())
		{
			_movement->spearPoke(time);
			_spear_hitbox->update(_movement->getDirection());
			_spear_hitbox->render(window);
		}
		if (_movement->isReadyToDealSpearDamage())
			this->_dealSpearDamage(list_of_bots);
	}
}