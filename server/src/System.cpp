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

bool S_Collision::checkCollision(C_Transform* transform1, C_Transform* transform2, C_Hitbox* hitbox1, C_Hitbox* hitbox2)
{
    float left1 = transform1->_position.x;
    float right1 = transform1->_position.x + hitbox1->_size.x;
    float top1 = transform1->_position.y;
    float bottom1 = transform1->_position.y + hitbox1->_size.y;

    float left2 = transform2->_position.x;
    float right2 = transform2->_position.x + hitbox2->_size.x;
    float top2 = transform2->_position.y;
    float bottom2 = transform2->_position.y + hitbox2->_size.y;

    if (right1 >= left2 && left1 <= right2 && bottom1 >= top2 && top1 <= bottom2) {
        return true;
    }
    return false;
}

void S_Collision::update()
{
    int index1 = 0;
    int index2 = 0;
    std::vector<int> denseIndex = _sparseEntities.getAllIndices();
    std::vector<std::shared_ptr<IEntity>> &entities = _sparseEntities.getAll();

    for (auto& entity1 : entities) {
        for (auto& entity2 : entities) {
            if (entity1 != entity2) {
                C_Hitbox* hitbox1 = Engine::getComponentRef<C_Hitbox>(*entity1);
                C_Hitbox* hitbox2 = Engine::getComponentRef<C_Hitbox>(*entity2);
                C_Transform* transform1 = Engine::getComponentRef<C_Transform>(*entity1);
                C_Transform* transform2 = Engine::getComponentRef<C_Transform>(*entity2);

                if (typeid(*entity1) == typeid(E_Player) && typeid(*entity2) == typeid(E_Enemy)) {
                    if (checkCollision(transform1, transform2, hitbox1, hitbox2)) {
                        C_Health* health1 = Engine::getComponentRef<C_Health>(*entity1);
                        C_Health* health2 = Engine::getComponentRef<C_Health>(*entity2);

                        transform1->_position.x -= 50;
                    }
                }

                if (typeid(*entity1) == typeid(E_Bullet) && typeid(*entity2) == typeid(E_Enemy)) {
                    if (checkCollision(transform1, transform2, hitbox1, hitbox2)) {
                        C_Health* health2 = Engine::getComponentRef<C_Health>(*entity2);
                        C_Damage* damage1 = Engine::getComponentRef<C_Damage>(*entity1);

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
            C_Hitbox* hitbox1 = Engine::getComponentRef<C_Hitbox>(*entity1);

            if (transform1->_position.x < 0)
                transform1->_position.x = 0;
            if (transform1->_position.x + hitbox1->_size.x > screenWidth)
                transform1->_position.x = screenWidth - hitbox1->_size.x;
            if (transform1->_position.y < 0)
                transform1->_position.y = 0;
            if (transform1->_position.y + hitbox1->_size.y > screenHeight)
                transform1->_position.y = screenHeight - hitbox1->_size.y;
        }
        if (typeid(*entity1) == typeid(E_Enemy)) {
            // Destroy enemy if it leaves the screen on the left
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity1);

            if (transform->_position.x <= -100.0) {
                printf("Enemy %d destroyed (POS X:%f Y:%f)\n", denseIndex[index1], transform->_position.x, transform->_position.y);
                printf("Old size: %d\n", _sparseEntities.getAll().size());
                // print sparse
                for (auto& element : _sparseEntities.getSparse()) {
                    printf("%d ", element);
                }
                printf("\n");
                _sparseEntities.remove(denseIndex[index1]);
                printf("New size: %d\n", _sparseEntities.getAll().size());
                // print sparse
                for (auto& element : _sparseEntities.getSparse()) {
                    printf("%d ", element);
                }
                printf("\n");
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
                transform->_position.y = 20 * sin(transform->_position.x / 30) + transform->_position.y;
            }
            if (enemyInfo->_type == 3) {
                // the enemy will move in a sinusoid pattern but smaller and faster
                transform->_position.x -= 8;
                transform->_position.y = 10 * sin(transform->_position.x / 20) + transform->_position.y;
            }
        }
    }
}

S_Spawner::S_Spawner(SparseArray<IEntity> &sparseEntities)
    : _sparseEntities(sparseEntities)
{
}

S_Spawner::~S_Spawner()
{
}

void S_Spawner::update()
{
    int random = rand() % 50;

    if (random == 1 || random == 50) {
        int random2 = rand() % 3;
        int random4 = rand() % 600;
        int random5 = rand() % 3 + 1;
        int random3 = rand() % (random5 == 1 ? 400 : 600);
        int id = _sparseEntities.add(std::make_shared<E_Enemy>(800, random3, 65.2, 66, random5));
        printf("Creating Enemy ID: %d with type %d\n", id, random2);
    }
}

S_Weapon::S_Weapon(SparseArray<IEntity> &sparseEntities)
   : _sparseEntities(sparseEntities)
{
}

void S_Weapon::shoot(int idCreator)
{
    int i = 0;
    std::vector<int> denseIndex = _sparseEntities.getAllIndices();

    for (auto& entity : _sparseEntities.getAll()) {
        if (typeid(*entity) == typeid(E_Player)) {
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity);

            if (idCreator == denseIndex[i]) {
                // create bullet with player position info
                float xpos = transform->_position.x;
                float ypos = transform->_position.y;
                float size_x = transform->_size.x;
                float size_y = transform->_size.y;
                float velocity_x = 10;
                float velocity_y = 0;
                _sparseEntities.add(std::make_shared<E_Bullet>(10, xpos, ypos, size_x, size_y, velocity_x, velocity_y, idCreator));
            }
        }
        i++;
    }
}

void S_Weapon::update()
{
    // Update all bullets
    int i = 0;
    std::vector<int> denseIndex = _sparseEntities.getAllIndices();

    for (auto& entity : _sparseEntities.getAll()) {
        if (typeid(*entity) == typeid(E_Bullet)) {
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity);
            C_Sprite* sprite = Engine::getComponentRef<C_Sprite>(*entity);

            transform->_position.x += transform->_velocity.x;
            transform->_position.y += transform->_velocity.y;
        }
        i++;
    }
}
