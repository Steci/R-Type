/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.cpp
*/

#include <sstream>
#include <algorithm>
#include <cmath>
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

S_Collision::S_Collision(SparseArray<IEntity> &sparseEntities)
    : _sparseEntities(sparseEntities)
{
}

S_Collision::~S_Collision()
{
}

bool S_Collision::checkCollision(C_Transform *transform1, C_Transform *transform2, C_Hitbox *hitbox1, C_Hitbox *hitbox2)
{
    if (transform1->_position.x < transform2->_position.x + hitbox2->_size.x &&
        transform1->_position.x + hitbox1->_size.x > transform2->_position.x &&
        transform1->_position.y < transform2->_position.y + hitbox2->_size.y &&
        transform1->_position.y + hitbox1->_size.y > transform2->_position.y && (hitbox1->_status != 0 && hitbox2->_status != 0) ) {
        return true;
    }
    return false;
}

void S_Collision::update()
{
    int index1 = 0;
    int index2 = 0;
    std::vector<int> denseIndex = _sparseEntities.getAllIndices();

    for (auto& entity1 : _sparseEntities.getAll()) {
        for (auto& entity2 : _sparseEntities.getAll()) {
            if (entity1 != entity2) {
                C_Hitbox* hitbox1 = Engine::getComponentRef<C_Hitbox>(*entity1);
                C_Hitbox* hitbox2 = Engine::getComponentRef<C_Hitbox>(*entity2);
                C_Transform* transform1 = Engine::getComponentRef<C_Transform>(*entity1);
                C_Transform* transform2 = Engine::getComponentRef<C_Transform>(*entity2);

                if (checkCollision(transform1, transform2, hitbox1, hitbox2)) {

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

                        // health2->_health -= damage1->_damage;
                        _sparseEntities.remove(denseIndex[index1]);
                        _sparseEntities.remove(denseIndex[index2]);
                    }
                }
            }
            index2++;
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
        if (typeid(*entity1) == typeid(E_Enemy)) {
            // Destroy enemy if it leaves the screen on the left
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity1);

            if (transform->_position.x <= -10.0) {
                printf("Enemy %d destroyed\n", denseIndex[index1]);
                _sparseEntities.remove(denseIndex[index1]);
            }
        }
        if (typeid(*entity1) == typeid(E_Bullet)) {
            // Destroy bullet if it leaves the screen
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity1);

            if (transform->_position.x >= screenWidth + 10 || transform->_position.y >= screenHeight + 10 || transform->_position.y <= -10.0 || transform->_position.x <= -10.0) {
                printf("Bullet %d destroyed\n", denseIndex[index1]);
                _sparseEntities.remove(denseIndex[index1]);
            }
        }
        index1++;
    }
}

S_EnemyAI::S_EnemyAI(SparseArray<IEntity> &sparseEntities )
    : _sparseEntities(sparseEntities)
{
}

S_EnemyAI::~S_EnemyAI()
{
}

void S_EnemyAI::update()
{
    for (auto& entity : _sparseEntities.getAll()) {
        if (typeid(*entity) == typeid(E_Enemy)) {
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity);
            C_EnemyInfo* enemyInfo = Engine::getComponentRef<C_EnemyInfo>(*entity);

            if (enemyInfo->_type == 1) {
                // straight line
                transform->_position.x -= 5;
            }
            if (enemyInfo->_type == 2) {
                // the enemy will move in a sinusoid pattern
                transform->_position.x -= 5;
                transform->_position.y = 50 * sin(transform->_position.x / 50) + transform->_position.y;
            }
            if (enemyInfo->_type == 3) {
                // the enemy will move in a sinusoid pattern but smaller and faster
                transform->_position.x -= 7;
                transform->_position.y = 100 * sin(transform->_position.x / 50) + transform->_position.y;
            }
        }
    }
}