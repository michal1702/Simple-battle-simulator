#pragma once

#include "Archer.h"

namespace RTB
{
	

	void Archer::_dealBowDamage(std::list<std::shared_ptr<Character>>& list_of_bots)
	{
		for (std::list<std::shared_ptr<Character>>::iterator iterator = list_of_bots.begin();
			iterator != list_of_bots.end(); iterator++)
		{
			if ((*iterator)->isAlive() && _arrows->isFlying() && checkOrientedCollision((*iterator)->getHitbox(), _arrows->getHitbox()))
			{
				(*iterator)->subtractHP(_bow_damage);
			}
		}
	}

	Archer::Archer(sf::Texture texture, short health_points, sf::Texture& arrow_texture, std::vector<std::vector<AI::PathNode>>& walkable_area):
		_arrows(nullptr)
	{
		_path_generator = new AI::RTBPathGenerator(walkable_area);
		_health_points = health_points;
		_character_sprite = new sf::Sprite;
		_movement = new RiD::Movement(texture, _character_sprite);
		_hitbox = new Hitbox(_character_sprite, { 24.f, 46.f }, { -12.f,-16.f });
		_hp_bar = new HPBar(_character_sprite, _health_points);
		_arrows = new Arrow(_character_sprite, arrow_texture);
		_is_alive = true;
		_is_enemy_choosen = false;
		_speed = 0.6f;
		_bow_damage = 1;
	}

	Archer::~Archer()
	{
		delete _movement;
		delete _hitbox;
		delete _character_sprite;
		delete _hp_bar;
		delete _arrows;
		delete _path_generator;
		_deletePath();
	}

	void Archer::update(sf::Time time, std::vector<std::vector<std::unique_ptr<MapElement>>>& map_objects,
		std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderWindow& window)
	{
		_position = _movement->getSprite().getPosition();
		if (!_movement->isShotTriggered())
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
			if (distance < 8 && !_arrows->isFlying())
			{
				_shot_destination = { (int)(*_choosen_enemy)->getPosition().x, (int)(*_choosen_enemy)->getPosition().y };
				_movement->triggerShot();
			}
		}
		_hitbox->update();
		_hp_bar->update();
		if (_movement->isDeathTriggered())
		{
			_movement->death(time);
			if (_movement->isDeathTriggered() == false)
			{
				_is_alive = false;
				_deletePath();
			}
		}
	}

	void Archer::dealDamage(sf::Time time, std::list<std::shared_ptr<Character>>& list_of_bots, sf::RenderTarget& window)
	{
		if (_movement->isShotTriggered())
		{
			_position = _character_sprite->getPosition();
			if (_shot_destination.x - _position.x > 0 && abs(_shot_destination.x - _position.x) > abs(_shot_destination.y - _position.y))
				_direction = static_cast<short>(directions::right);
			else if (_shot_destination.x - _position.x < 0 && abs(_shot_destination.x - _position.x)> abs(_shot_destination.y - _position.y))
				_direction = static_cast<short>(directions::left);
			else if (_shot_destination.y - _position.y > 0 && abs(_shot_destination.x - _position.x) < abs(_shot_destination.y - _position.y))
				_direction = static_cast<short>(directions::down);
			else if (_shot_destination.y - _position.y < 0 && abs(_shot_destination.x - _position.x) < abs(_shot_destination.y - _position.y))
				_direction = static_cast<short>(directions::up);
			_movement->bowShot(time,_direction);
			_arrows->update();
		}
		if (_movement->isReadyToShotArrow())
		{
			_arrows->fly(time, window, _shot_destination);
			this->_dealBowDamage(list_of_bots);
		}

		if (_arrows->isFlying() == false)
			_movement->notReadyToShotArrow();
	}
}