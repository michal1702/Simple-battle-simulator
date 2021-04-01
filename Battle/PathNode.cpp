#pragma once

#include "PathNode.h"

namespace AI
{
	PathNode::PathNode():
		_F(0), _G(0), _H(0), _next_node(nullptr), _parent_node(nullptr)
	{
		_walkable = 1;
	}

	sf::Vector2i PathNode::getPosition()
	{
		return _position;
	}

	int PathNode::getFCost()
	{
		return _F;
	}

	PathNode*& PathNode::getParent()
	{
		return this->_parent_node;
	}

	PathNode*& PathNode::getPNext()
	{
		return this->_next_node;
	}

	void PathNode::setPNext(PathNode* node)
	{
		this->_next_node = node;
	}

	void PathNode::setParent(PathNode* node)
	{
		this->_parent_node = node;
	}

	void PathNode::setNotWalkable()
	{
		_walkable = 0;
	}

	void PathNode::setFCost(sf::Vector2i end)
	{
		_calcG(_position);
		_calcH(end);
		_F = _G + _H;
	}

	void PathNode::setPosition(sf::Vector2i pos)
	{
		_position = pos;
	}

	bool PathNode::isWalkable()
	{
		if (_walkable)
			return true;
		else
			return false;
	}

	int PathNode::getGCost(sf::Vector2i start)
	{
		_G = abs(_position.x - start.x);
		_G += abs(_position.y - start.y);
		return _G;

	}

	void PathNode::_calcG(sf::Vector2i start)
	{
		_G = abs(start.x - _position.x);
		_G += abs(start.y - _position.y);
	}

	void PathNode::_calcH(sf::Vector2i end)
	{
		_H = abs(end.x - _position.x);
		_H += abs(end.y - _position.y);
	}
}