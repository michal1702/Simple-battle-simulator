#pragma once
#include "AssetManager.h"

namespace RiD
{
	AssetManager::AssetManager(){}
	AssetManager::~AssetManager(){}
	void AssetManager::setTexture(std::string tex_name, std::string file_name)
	{
		sf::Texture texture;
		if (texture.loadFromFile(file_name))
			this->_textures[tex_name] = texture;
	}

	sf::Texture& AssetManager::getTexture(std::string tex_name)
	{
		return this->_textures.at(tex_name);
	}

	void AssetManager::setFont(std::string font_name, std::string file_name)
	{
		sf::Font font;
		if (font.loadFromFile(file_name))
			this->_fonts[font_name] = font;
	}

	sf::Font& AssetManager::getFont(std::string font_name)
	{
		return this->_fonts.at(font_name);
	}
}