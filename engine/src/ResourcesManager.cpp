/*
** EPITECH PROJECT, 2023
** GAME ENGINE
** File description:
** ResourcesManager
*/

#include <string>
#include <raylib.h>
#include "ResourcesManager.hpp"

namespace Engine
{
	ResourcesManager::~ResourcesManager()
	{
		for (auto &it : this->_textures)
			UnloadTexture(it.second);
		for (auto &it : this->_images)
			UnloadImage(it.second);
		for (auto &it : this->_music)
			UnloadMusicStream(it.second);
	}

	Texture2D &ResourcesManager::LoadTextures(const std::string &path)
	{
		if (this->_textures.find(path) == this->_textures.end())
			this->_textures[path] = LoadTexture(path.c_str());
		return this->_textures[path];
	}

	Image &ResourcesManager::LoadPictures(const std::string &path)
	{
		if (this->_images.find(path) == this->_images.end())
			this->_images[path] = LoadImage(path.c_str());
		return this->_images[path];
	}

	Music &ResourcesManager::LoadMusic(const std::string &path)
	{
		if (this->_music.find(path) == this->_music.end())
			this->_music[path] = LoadMusicStream(path.c_str());
		return this->_music[path];
	}

}