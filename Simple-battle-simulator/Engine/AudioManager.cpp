#pragma once

#include "AudioManager.h"

namespace RiD
{
	AudioManager::AudioManager()
	{
		setSoundBuffer("swordSwing", "audio/swordSwing.wav");
		setSoundBuffer("spearPoke", "audio/spearPoke.wav");
		setSoundBuffer("arrow", "audio/arrow.wav");
		setSoundBuffer("death", "audio/death.wav");
		setSoundBuffer("steps", "audio/steps.wav");
	}

	void AudioManager::setSoundBuffer(std::string sound_name, std::string file_name)
	{
		sf::SoundBuffer buff;
		if (buff.loadFromFile(file_name))
			this->_audio_buffer[sound_name] = buff;
	}

	sf::SoundBuffer& AudioManager::getSoundBuffer(std::string sound_name)
	{
		return this->_audio_buffer.at(sound_name);
	}

	void AudioManager::playSound(const std::string& sound_name, const float& volume, const float& pitch, const bool& loop)
	{
		_sound.setBuffer(getSoundBuffer(sound_name));
		_sound.setVolume(volume);
		_sound.setLoop(loop);
		_sound.setPitch(pitch);
		_sound.setMinDistance(6.f);
		_sound.play();
	}

	void AudioManager::playMusic(const std::string& file_name, const float& volume)
	{
		try
		{
			if (!_music.openFromFile(file_name))
				throw;
			_music.setVolume(volume);
			_music.setLoop(true);
			_music.play();
		}
		catch(std::exception& ex)
		{
			ex.what();
		}
	}
}