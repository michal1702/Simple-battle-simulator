#pragma once

#include "SFML/Graphics.hpp"

namespace AI
{
	class PathNode
	{
	private:
		int _F, _G, _H;
		PathNode* _next_node, *_parent_node;
		sf::Vector2i _position;
		bool _walkable;

		///Calculates G value which is the movement cost to move from the starting point to a given position
		///@param start starting position
		void _calcG(sf::Vector2i start);

		///Calculates H value which is the estimated movement cost to move from that given position to the final destination.
		///@param end destination
		void _calcH(sf::Vector2i end);
	public:
		PathNode();

		///Gets position of current node
		sf::Vector2i getPosition();

		///@return F cost which is sum of G and H
		int getFCost();

		///@return parent of current node
		PathNode*& getParent();

		///@return next node
		PathNode*& getPNext();

		///Sets next node
		///@param node pointer to the next node
		void setPNext(PathNode *node);

		///Sets parent node
		///@param node pointer to the parent node
		void setParent(PathNode *node);

		///Determines which areas of the map are not walkable
		void setNotWalkable();

		///Sets F cost
		///@param end destination
		void setFCost(sf::Vector2i end);

		///Sets position
		///@param pos position
		void setPosition(sf::Vector2i pos);

		///Checks if area is walkable
		bool isWalkable();

		///@return G cost
		///@param start 
		int getGCost(sf::Vector2i start);
	};
}