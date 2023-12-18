/*
** EPITECH PROJECT, 2023
** GAME ENGINE
** File description:
** RessourcesManager
*/

#include <string>
#include <raylib>
#include "ResourcesManager.hpp"

namespace Engine
{
	ResourcesManager::~ResourcesManager()
	{
		for (auto &it : this->_textures)
			UnloadTexture(it.second);
		for (auto &it : this->_pictures)
			UnloadImage(it.second);
		for (auto &it : this->_music)
			UnloadMusicStream(it.second);
		for (auto &it : this->_audio)
			UnloadAudioStream(it.second);
	}

	Texture2D &ResourcesManager::LoadTextures(const std::string &path)
	{
		if (this->_textures.find(path) == this->_textures.end())
			this->_textures[path] = LoadTexture(path.c_str());
		return this->_textures[path]
	}

	Image &ResourcesManager::LoadPictures(const std::string &path)
	{
		if (this->_pictures.find(path) == this->_pictures.end())
			this->_pictures[path] = LoadImage(path.c_str());
		return this->_pictures[path]
	}

	Music &ResourcesManager::LoadMusic(const std::string &path)
	{
		if (this->_music.find(path) == this->_music.end())
			this->_music[path] = LoadMusicStream(path.c_str());
		return this->_music[path]
	}

	AudioStream &ResourcesManager::LoadAudio(const std::string &path)
	{
		if (this->_audio.find(path) == this->_audio.end())
			this->_audio[path] = LoadAudioStream(path.c_str());
		return this->_audio[path]
	}
}