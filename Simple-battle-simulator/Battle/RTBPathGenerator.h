#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "PathNode.h"

namespace AI
{
	class RTBPathGenerator
	{
	private:
		std::vector<std::vector<PathNode>> _walkable_area;
		PathNode* _path;
		PathNode* _opened_list_head, * _closed_list_head;
		sf::Vector2i _start, _end;
		unsigned int _width, _height;

		///Adds node to opened list which keeps track of those nodes that need to be examined
		///@param node new node
		void _addToOpenedList(PathNode*& node);

		///Adds node to path which is ready to be implemented
		///@param node new node
		void _addToPathList(PathNode*& node);

		///Adds node to closed list which keeps track of nodes that have already been examined
		///@param node new node
		void _moveToClosedList(PathNode*& node);

		///Deletes opened list
		void _deleteOpenedList();

		///Deletes closed list
		void _deleteClosedList();

		///Gets information about 8 closest nodes near the examined node
		void _NeighbourPosition(unsigned short i, unsigned short j, unsigned short points[]);

		///Generates path
		void _generatePath();

		///Checks if neighbour exists in the list
		///@param neighbour
		///@param pHead pointer to current list
		bool _ifExists(PathNode neighbour, PathNode* pHead);

		///Cuts off node
		///@return pointer to path node
		///@param node node to cut off
		PathNode* _cutOffNodeFromOpen(PathNode*& node);

		///Cuts off node
	    ///@return pointer to path node
	    ///@param node node to cut off
		PathNode* _cutOffNodeFromClosed(PathNode*& node);

		///Finds node with smallest F value in opened list
		///@return pointer to node
		PathNode* _findSmallestF();

		///Finds node with by position in closed list
		///@return pointer to node
		///@param position
		PathNode* _findByPosition(sf::Vector2i position);
	public:
		RTBPathGenerator(std::vector<std::vector<PathNode>>& walkable_area);

		///Performs process of finding path from start to end
		///@param start
		///@param end
		void findPath(sf::Vector2i start, sf::Vector2i end);

		///@return path ready to be implemented
		PathNode*& getPath();

		///@return middle element of path list
		PathNode* getMiddle();

		///@rateurn distance between start and end
		///@param start starting point
		///@param end destination
		int distance(sf::Vector2i start, sf::Vector2i end);
	};
}