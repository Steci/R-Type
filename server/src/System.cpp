/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.cpp
*/

#include <sstream>
#include <algorithm>
#include "Game.hpp"


S_Renderer::S_Renderer(int w, int h, int fps, std::string wName, const std::string& imagePath) {
    _screenWidth = w;
    _screenHeight = h;
    _targetFps = fps;
    _windowName = wName;
    InitWindow(_screenWidth, _screenHeight, _windowName.c_str());
    InitAudioDevice();
    SetTargetFPS(_targetFps);
    _parallax = S_Parallax();
    _parallax.initialize(imagePath, w, h);
};

void S_Renderer::render()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        float maxScale = std::max(_parallax.getScaleFactor().x, _parallax.getScaleFactor().y);
        DrawTextureEx(_parallax.getBackground(), (Vector2){ 0, 0 }, 0.0f, maxScale, WHITE);
        for (auto& entity : _entities) {
            entity->render();
        }
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
    return -1;
}

void S_Parallax::initialize(const std::string& imagePath, int screenWidth, int screenHeight)
{
    _image = LoadImage(imagePath.c_str());
    if (_image.data == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << imagePath << std::endl;
        return;
    } else {
        _background = LoadTextureFromImage(_image);
    }
    if (_background.id == 0) {
        std::cerr << "Erreur de chargement de la texture de l'image." << std::endl;
        return;
    }
    float scaleX = (float)screenWidth / ((float)_background.width);
    float scaleY = (float)screenHeight / ((float)_background.height);
    _scaleFactor = {scaleX, scaleY};
}

S_Parallax::~S_Parallax()
{
    UnloadTexture(_background);
    UnloadImage(_image);
}

S_AudioManager::S_AudioManager()
{
    _background_music_game["BOSS"] = LoadMusicStream("./music/Boss.mp3");
    _background_music_game["MENU"] = LoadMusicStream("./music/menu.mp3");
    _background_music_game["GAME_OVER"] = LoadMusicStream("./music/Game_over.mp3");
    _background_music_game["THEME"] = LoadMusicStream("./music/Theme_song.mp3");
    _sound_effects["DEAD"] = LoadSound("./music/dead.wav");
    _sound_effects["SHOOT"] = LoadSound("./music/shoot.wav");;;
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

S_Collision::S_Collision()
{
}

S_Collision::~S_Collision()
{
}

bool S_Collision::checkCollision(IEntity* entity1, IEntity* entity2)
{
    C_Hitbox* hitbox1 = Engine::getComponentRef<C_Hitbox>(*entity1);
    C_Hitbox* hitbox2 = Engine::getComponentRef<C_Hitbox>(*entity2);

    if (hitbox1->_status == 0 || hitbox2->_status == 0)
        return false;

    C_Transform* transform1 = Engine::getComponentRef<C_Transform>(*entity1);
    C_Transform* transform2 = Engine::getComponentRef<C_Transform>(*entity2);

    if (transform1->_position.x < transform2->_position.x + hitbox2->_size.x &&
        transform1->_position.x + hitbox1->_size.x > transform2->_position.x &&
        transform1->_position.y < transform2->_position.y + hitbox2->_size.y &&
        transform1->_position.y + hitbox1->_size.y > transform2->_position.y)
        return true;
    return false;
}

void S_Collision::update()
{
    for (auto& entity1 : _entities) {
        for (auto& entity2 : _entities) {
            if (entity1 != entity2) {
                if (checkCollision(entity1, entity2)) {
                    C_Transform* transform1 = Engine::getComponentRef<C_Transform>(*entity1);
                    C_Transform* transform2 = Engine::getComponentRef<C_Transform>(*entity2);

                    if (typeid(*entity1) == typeid(E_Player) && typeid(*entity2) == typeid(E_Enemy)) {
                        C_Health* health1 = Engine::getComponentRef<C_Health>(*entity1);
                        C_Health* health2 = Engine::getComponentRef<C_Health>(*entity2);
                        C_Damage* damage2 = Engine::getComponentRef<C_Damage>(*entity2);

                        health1->_health -= damage2->_damage;
                        health2->_health -= 1;
                        transform1->_position.x -= 20;
                    }

                    if (typeid(*entity1) == typeid(E_Bullet) && typeid(*entity2) == typeid(E_Enemy)) {
                        C_Health* health2 = Engine::getComponentRef<C_Health>(*entity2);
                        C_Damage* damage1 = Engine::getComponentRef<C_Damage>(*entity1);

                        health2->_health -= damage1->_damage;
                        transform1->_position.x += 1000;
                    }

                }
            }
            if (typeid(*entity1) == typeid(E_Player)) {
                // check if player is leaving screenWidth or screenHeight
                C_Transform* transform1 = Engine::getComponentRef<C_Transform>(*entity1);

                if (transform1->_position.x < 0)
                    transform1->_position.x = 0;
                if (transform1->_position.x > screenWidth)
                    transform1->_position.x = screenWidth;
                if (transform1->_position.y < 0)
                    transform1->_position.y = 0;
                if (transform1->_position.y > screenHeight)
                    transform1->_position.y = screenHeight;
            }
        }
    }
}