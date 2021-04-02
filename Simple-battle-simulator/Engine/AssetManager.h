#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace RiD
{
	class AssetManager
	{
	private:
		std::map<std::string, sf::Texture> _textures;
		std::map<std::string, sf::Font> _fonts;
	public:
		AssetManager();
		~AssetManager();

		/*
		Sets textures
		@param tex_name name of the texture
		@param file_name name of the file from which it will be taken
		*/
		void setTexture(std::string tex_name, std::string file_name);

		/*
		Returns texture
		@param tex_name name of the texture
		@return texture
		*/
		sf::Texture& getTexture(std::string tex_name);

		/*
		Sets fonts
		@param font_name name of the font
		@param file_name name of the file from which it will be taken
		*/
		void setFont(std::string font_name, std::string file_name);

		/*
		Returns font
		@param font_name name of the font
		@return font
		*/
		sf::Font& getFont(std::string font_name);
	};
}