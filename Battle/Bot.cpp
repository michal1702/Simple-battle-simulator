#pragma once

#include "Bot.h"

namespace RTB
{
	std::list<std::shared_ptr<Character>>::iterator Bot::_selectRandomEnemy(std::list<std::shared_ptr<Character>>::iterator start, std::list<std::shared_ptr<Character>>::iterator end)
	{
		unsigned seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::mt19937 gen(seed);
		std::uniform_int_distribution<int> dis(0, std::distance(start, end) - 1);
		std::advance(start, dis(gen));
		return start;
	}

	void Bot::_deletePath()
	{
		AI::PathNode* iterator = _current_path;

		while (iterator != 0)
		{
			_current_path = iterator->getPNext();
			delete iterator;
			iterator = _current_path;
		}

		delete _current_path;
	}

	void Bot::_move(sf::Time time)
	{
		if (_current_path == nullptr)
		{
			_path_generator->findPath(_isoTo2D(_position), _isoTo2D((*_choosen_enemy)->getPosition()));
			_current_path = _path_generator->getPath();
			_half_way = _path_generator->getMiddle();
			_tmp_current_path = _current_path;
			_end_path_position = _current_enemy_position;
		}
		else if (_current_enemy_position != _end_path_position && _tmp_current_path == _half_way)
		{
			_deletePath();
			_path_generator->findPath(_isoTo2D(_position), _isoTo2D((*_choosen_enemy)->getPosition()));
			_current_path = _path_generator->getPath();
			_half_way = _path_generator->getMiddle();
			_tmp_current_path = _current_path;
			_end_path_position = _current_enemy_position;
		}
		else if (_tmp_current_path->getPNext())
		{
			if (_tmp_current_path->getPNext()->getPosition().x > _isoTo2D(_position).x &&
				_tmp_current_path->getPNext()->getPosition().y < _isoTo2D(_position).y)
			{
				_movement->walkingRight(time, _speed, -_speed);
			}
			else if (_tmp_current_path->getPNext()->getPosition().x < _isoTo2D(_position).x &&
				_tmp_current_path->getPNext()->getPosition().y < _isoTo2D(_position).y)
			{
				_movement->walkingLeft(time, -_speed, -_speed);
			}
			else if (_tmp_current_path->getPNext()->getPosition().x < _isoTo2D(_position).x &&
				_tmp_current_path->getPNext()->getPosition().y > _isoTo2D(_position).y)
			{
				_movement->walkingLeft(time, -_speed, _speed);
			}
			else if (_tmp_current_path->getPNext()->getPosition().x > _isoTo2D(_position).x &&
				_tmp_current_path->getPNext()->getPosition().y > _isoTo2D(_position).y)
			{
				_movement->walkingRight(time, _speed, _speed);
			}
			else if (_tmp_current_path->getPNext()->getPosition().x > _isoTo2D(_position).x)
			{
				_movement->walkingRight(time, _speed, 0.0f);
			}

			else if (_tmp_current_path->getPNext()->getPosition().x < _isoTo2D(_position).x)
			{
				_movement->walkingLeft(time, -_speed, 0.0f);
			}

			else if (_tmp_current_path->getPNext()->getPosition().y < _isoTo2D(_position).y)
			{
				_movement->walkingUp(time, 0.0f, -_speed);
			}

			else if (_tmp_current_path->getPNext()->getPosition().y > _isoTo2D(_position).y)
			{
				_movement->walkingDown(time, 0.0f, _speed);
			}
			else
				_movement->idle(time);

			if (_tmp_current_path->getPNext()->getPosition() == _isoTo2D(_position))
				_tmp_current_path = _tmp_current_path->getPNext();
		}
	}
}