#pragma once

#include "SFML/Graphics.hpp"
#include "../Engine/AssetManager.h"
#include "MapElement.h"
#include "../Battle/PathNode.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

namespace RTB
{
	class TileMap
	{
	private:
		RiD::AssetManager _asset_manager;
		enum _tiles {dirt, grass, water, road};
		enum _flora {no_flora, tinyFlower, redFlower, fence1Fallen};
		enum _Collidable_objects {no_object, fence1, sign, tree, chest};

		std::vector<std::vector<unsigned int>> _level;
		std::vector<std::vector<unsigned int>> _flora;
		std::vector<std::vector<unsigned int>> _objects;
		std::vector<std::vector<std::unique_ptr<MapElement>>> _map_elements;

		std::vector<std::vector<AI::PathNode>> _walkable_area;

		unsigned int _width , _height , _tile_type;
		sf::Vector2f _point;

		sf::Vector2f _twoDToIso();

		///Loads from files info about 3 layers: tiles, flora and objects
		void _loadFromFile(std::string map_file_name, std::string flora_file_name, std::string objects_file_name);

		///Assigns tile sprite on certain position
		void _placeTile(unsigned short _position_x, unsigned short _position_y);

		///Assigns flora sprite on certain position
		void _placeFlora(unsigned short _position_x, unsigned short _position_y);

		///Assigns object sprite on certain position
		void _placeObjects(unsigned short _position_x, unsigned short _position_y);

		///Generates walkable area
		void _generateWalkableArea();
	public:
		TileMap(sf::Vector2i tile_size);

		///Draws tiles: grass, dirt, etc. and flowers
		void drawTiles(sf::RenderTarget& window);

		///Draws collidable objects: trees, fences, etc.
		void drawObjects(sf::RenderTarget& window);

		///@return 2d vector of objects that player may collide with
		std::vector<std::vector<std::unique_ptr<MapElement>>>& getCollidableObjects();

		///@return 2d vector of walkable area for bots
		std::vector<std::vector<AI::PathNode>>& getWalkableArea();

		///@return width of the map
		unsigned int& getWidth();

		///@return height of the map
		unsigned int& getHeight();

		sf::Vector2f _twoDToIso(sf::Vector2f position);
	};
}