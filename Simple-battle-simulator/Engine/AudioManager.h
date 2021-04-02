#pragma once

#include <map>
#include <exception>
#include "SFML/Audio.hpp"

namespace RiD
{
	class AudioManager
	{
	private:
		std::map<std::string, sf::SoundBuffer> _audio_buffer;
		std::map<std::string, sf::Sound> _sounds;

		sf::Sound _sound;
		sf::Music _music;

	public:
		AudioManager();

		///Adds sound buffer
		///@param sound_name name
		///@param file_name sound file
		void setSoundBuffer(std::string sound_name, std::string file_name);

		///@return sound buffer
		sf::SoundBuffer& getSoundBuffer(std::string sound_name);

		///Plays sound with specified parameters
		void playSound(const std::string &sound_name, const float& volume, const float& pitch = 1.f, const bool& loop = false);

		///Plays music with specified parameters
		void playMusic(const std::string& file_name, const float& volume);
	};
}