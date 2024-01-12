/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.cpp
*/

#include <sstream>
#include <algorithm>
#include <cmath>
#include "../include/Game.hpp"

S_Renderer::S_Renderer(int w, int h, int fps, std::string wName, const std::string& imagePath) {
    _screenWidth = w;
    _screenHeight = h;
    _targetFps = fps;
    _windowName = wName;
    InitWindow(_screenWidth, _screenHeight, _windowName.c_str());
    InitAudioDevice();
    SetTargetFPS(_targetFps);
    _parallax = S_Parallax();
    _parallax.setScale(0.7f);
    _parallax.add(imagePath+"1.png", 0.7f);
    _parallax.add(imagePath+"2.png", 2.0f);
    _parallax.add(imagePath+"3.png", 3.5f);
    _parallax.add(imagePath+"4.png", 5.0f);
};

void S_Renderer::render()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);

        // Parallax Draw
        for (int i = 0; i < _parallax.getBackgrounds().size(); i++) {
            DrawTextureEx(_parallax.getBackgrounds()[i], (Vector2){ _parallax.getScrolling()[i], 0 }, 0.0f, _parallax.getScale(), WHITE);
            DrawTextureEx(_parallax.getBackgrounds()[i], (Vector2){ (_parallax.getBackgrounds()[i].width * _parallax.getScale()) + _parallax.getScrolling()[i], 0 }, 0.0f, _parallax.getScale(), WHITE);
        }
        int id = 0;
        for (auto& entity : _entities) {
            entity->render();
            id++;
        }
        _parallax.update();
    EndDrawing();
}

void S_Renderer::update()
{
    if (IsKeyPressed(KEY_ESCAPE))
        closeWindow();
    if (!WindowShouldClose())
        render();
}

void S_Renderer::closeWindow()
{
    CloseWindow();
}

int S_EventManager::EventKeyPressed(std::list<int> keys)
{
    for (auto key: keys) {
        if (IsKeyPressed(key)) {
            return key;
        }
    }
}

int S_EventManager::getMovement()
{
    if (IsKeyDown(KEY_UP))
        return 1;
    if (IsKeyDown(KEY_RIGHT))
        return 2;
    if (IsKeyDown(KEY_DOWN))
        return 3;
    if (IsKeyDown(KEY_LEFT))
        return 4;
    return 0;
}

int S_EventManager::getShoot()
{
    if (IsKeyDown(KEY_SPACE))
        return 1;
    return 0;
}

int S_EventManager::getQuit()
{
    if (IsKeyDown(KEY_ESCAPE))
        return 1;
    return 0;
}

S_Parallax::~S_Parallax()
{
    for (auto& background : _backgrounds) {
        UnloadTexture(background);
    }
    for (auto& image : _images) {
        UnloadImage(image);
    }
}

void S_Parallax::update()
{
    for (int i = 0; i < _backgrounds.size(); i++) {
        _scrolling[i] -= _scrollingForces[i];
        if (_scrolling[i] <= -(_backgrounds[i].width * _scale)) {
            _scrolling[i] = 0;
        }
    }
}

S_AudioManager::S_AudioManager()
{
    _background_music_game["BOSS"] = LoadMusicStream("./music/Boss.mp3");
    _background_music_game["MENU"] = LoadMusicStream("./music/menu.mp3");
    _background_music_game["GAME_OVER"] = LoadMusicStream("./music/Game_over.mp3");
    _background_music_game["THEME"] = LoadMusicStream("./music/Theme_song.mp3");
    _sound_effects["DEAD"] = LoadSound("./music/dead.wav");
    _sound_effects["SHOOT"] = LoadSound("./music/shoot.wav");
}

S_AudioManager::~S_AudioManager()
{
    for (auto& effect : _sound_effects) {
        UnloadSound(effect.second);
    }
    for (auto& backgroundMusic : _background_music_game) {
        UnloadMusicStream(backgroundMusic.second);
    }
    CloseAudioDevice();
}
