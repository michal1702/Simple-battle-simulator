#pragma once

#include "RTBPathGenerator.h"

namespace AI
{
	void RTBPathGenerator::_addToOpenedList(PathNode*& node)
	{
		if (_opened_list_head)
		{
			node->setPNext(_opened_list_head);
			_opened_list_head = node;

		}
		else
		{
			_opened_list_head = node;
			node->setPNext(nullptr);
		}
	}

	void RTBPathGenerator::_addToPathList(PathNode*& node)
	{
		if (_path)
		{
			node->setPNext(_path);
			_path = node;

		}
		else
		{
			_path = node;
			node->setPNext(nullptr);
		}
	}

	void RTBPathGenerator::_moveToClosedList(PathNode*& node)
	{
		PathNode* tmp = nullptr;
		tmp = this->_cutOffNodeFromOpen(node);
		if (_closed_list_head)
		{
			tmp->setPNext(_closed_list_head);
			_closed_list_head = tmp;

		}
		else
		{
			_closed_list_head = tmp;
			tmp->setPNext(nullptr);
		}
	}

	void RTBPathGenerator::_deleteOpenedList()
	{
		PathNode* iterator = _opened_list_head;

		while (iterator != 0)
		{
			_opened_list_head = iterator->getPNext();
			delete iterator;
			iterator = _opened_list_head;
		}

		delete _opened_list_head;
	}

	void RTBPathGenerator::_deleteClosedList()
	{
		PathNode* iterator = _closed_list_head;

		while (iterator != 0)
		{
			_closed_list_head = iterator->getPNext();
			delete iterator;
			iterator = _closed_list_head;
		}

		delete _closed_list_head;
	}

	bool RTBPathGenerator::_ifExists(PathNode neighbour, PathNode* pHead)
	{
		PathNode* tmp;
		if (pHead == nullptr)
			return false;
		else
		{
			tmp = pHead;
			while (tmp->getPosition() != neighbour.getPosition())
			{
				if (tmp->getPNext() == nullptr)
					return false;
				else
					tmp = tmp->getPNext();
			}
		}
		return true;
	}

	void RTBPathGenerator::_NeighbourPosition(unsigned short i, unsigned short j, unsigned short points[])
	{
		if (i > 0 && j > 0 && j < _width - 1 && i < _height - 1)
		{
			points[0] = i - 1;
			points[1] = i + 1;
			points[2] = j - 1;
			points[3] = j + 1;
		}
		else if (i == 0 && j > 0 && j < _width - 1)
		{
			points[0] = i;
			points[1] = i + 1;
			points[2] = j - 1;
			points[3] = j + 1;
		}
		else if (i == _height - 1 && j > 0 && j < _width - 1)
		{
			points[0] = i - 1;
			points[1] = i;
			points[2] = j - 1;
			points[3] = j + 1;
		}
		else if (j == 0 && i > 0 && i < _height - 1)
		{
			points[0] = i - 1;
			points[1] = i + 1;
			points[2] = j;
			points[3] = j + 1;
		}
		else if (j == _width - 1 && i > 0 && i < _height - 1)
		{
			points[0] = i - 1;
			points[1] = i + 1;
			points[2] = j - 1;
			points[3] = j;
		}
	}

	void RTBPathGenerator::_generatePath()
	{
		PathNode* end_node = _findByPosition(_end);
		_path = _cutOffNodeFromClosed(end_node);
		PathNode* tmp = _path;
		while (tmp->getParent())
		{
			PathNode* new_node = _cutOffNodeFromClosed(tmp->getParent());
			_addToPathList(new_node);
			tmp = tmp->getParent();
		}
	}

	PathNode* RTBPathGenerator::_cutOffNodeFromOpen(PathNode*& node)
	{
		if (_opened_list_head == node)
		{
			PathNode* ptr = _opened_list_head;
			_opened_list_head = ptr->getPNext();
			ptr->setPNext(nullptr);
			return ptr;
		}
		else
		{
			PathNode* ptr = _opened_list_head;
			while (ptr->getPNext())
			{
				if (ptr->getPNext() == node)
				{
					node = ptr->getPNext();
					ptr->setPNext(node->getPNext());
					node->setPNext(nullptr);
					return node;
				}
				ptr = ptr->getPNext();
			}
		}
	}

	PathNode* RTBPathGenerator::_cutOffNodeFromClosed(PathNode*& node)
	{
		if (_closed_list_head == node)
		{
			PathNode* ptr = _closed_list_head;
			_closed_list_head = ptr->getPNext();
			ptr->setPNext(nullptr);
			return ptr;
		}
		else
		{
			PathNode* ptr = _closed_list_head;
			while (ptr->getPNext())
			{
				if (ptr->getPNext() == node)
				{
					node = ptr->getPNext();
					ptr->setPNext(node->getPNext());
					node->setPNext(nullptr);
					return node;
				}
				ptr = ptr->getPNext();
			}
		}
	}

	PathNode* RTBPathGenerator::_findSmallestF()
	{
		PathNode* smallestFElement;
		PathNode* tmp = _opened_list_head;
		smallestFElement = tmp;

		while (tmp)
		{
			if (tmp->getFCost() < smallestFElement->getFCost())
				smallestFElement = tmp;
			tmp = tmp->getPNext();
		}
		return smallestFElement;
	}

	PathNode* RTBPathGenerator::_findByPosition(sf::Vector2i position)
	{
		PathNode* tmp = _closed_list_head;
		while (tmp)
		{
			if (tmp->getPosition() == position)
				return tmp;
			tmp = tmp->getPNext();
		}
		return nullptr;
	}

	RTBPathGenerator::RTBPathGenerator(std::vector<std::vector<PathNode>>& walkable_area) :
		_path(nullptr), _opened_list_head(nullptr), _closed_list_head(nullptr)
	{
		_walkable_area = walkable_area;
		_width = _walkable_area[0].size();
		_height = _walkable_area.size();
	}

	void RTBPathGenerator::findPath(sf::Vector2i start, sf::Vector2i end)
	{
		if (_walkable_area[end.x][end.y].isWalkable() && start.y < _walkable_area[0].size()
			&& start.x < _walkable_area.size() && start != end)
		{
			_start = start;
			_end = end;
			unsigned short neighbors_bounds[4];

			PathNode* first = new PathNode();
			first->setPosition(_start);
			first->setFCost(_end);
			this->_addToOpenedList(first);
			while (_opened_list_head)
			{
				PathNode* current = _findSmallestF();
				_moveToClosedList(current);

				if (current->getPosition() == _end)
					break;
				_NeighbourPosition(current->getPosition().x, current->getPosition().y, neighbors_bounds);
				for (unsigned short i = neighbors_bounds[0]; i <= neighbors_bounds[1]; ++i)
				{
					for (unsigned short j = neighbors_bounds[2]; j <= neighbors_bounds[3]; ++j)
					{
						if (i != current->getPosition().x || j != current->getPosition().y)
						{
							_walkable_area[i][j].setFCost(_end);
							if (!_walkable_area[i][j].isWalkable() || _ifExists(_walkable_area[i][j], _closed_list_head))
								continue;
							else if (current->getGCost(_start) + distance(current->getPosition(), _walkable_area[i][j].getPosition()) < _walkable_area[i][j].getGCost(_start) || !_ifExists(_walkable_area[i][j], _opened_list_head))
							{
								PathNode* neighbour = new PathNode();
								neighbour->setPosition(sf::Vector2i(i, j));
								neighbour->setFCost(_end);
								neighbour->setParent(current);
								if (!_ifExists(_walkable_area[i][j], _opened_list_head))
								{
									this->_addToOpenedList(neighbour);
								}
								else
									delete neighbour;
							}
						}
					}
				}
			}
			if (_findByPosition(_end))
			{
				this->_generatePath();
				_deleteOpenedList();
				_deleteClosedList();
			}
			else
				_path = nullptr;
		}
		else
		{
			_path = nullptr;
		}
	}

	PathNode*& RTBPathGenerator::getPath()
	{
		return _path;
	}

	PathNode* RTBPathGenerator::getMiddle()
	{
		PathNode* slow_ptr = _path;
		PathNode* fast_ptr = _path;

		if (_path)
		{
			while (fast_ptr != NULL && fast_ptr->getPNext() != nullptr)
			{
				fast_ptr = fast_ptr->getPNext()->getPNext();
				slow_ptr = slow_ptr->getPNext();
			}
			return slow_ptr;
		}
		else
			return nullptr;
	}

	int RTBPathGenerator::distance(sf::Vector2i start, sf::Vector2i end)
	{
		return static_cast<int>(sqrt(pow(start.x - end.x, 2) + pow((start.y - end.y), 2)));
	}
}