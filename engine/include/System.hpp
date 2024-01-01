/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#pragma once

#include "Entity.hpp"
#include "Engine.hpp"
#include <map>

/**
 * @brief The base interface for all systems in the engine.
 */
class ISystem {
    public:
        /**
         * @brief Virtual destructor for ISystem.
         */
        virtual ~ISystem() = default;

        /**
         * @brief Update function for the system.
         */
        virtual void update() = 0;

    protected:
        std::vector<IEntity*> _entities; /**< The list of entities managed by the system. */
};

class ASystem : public ISystem {
    public:
        ASystem() = default;
        ~ASystem() = default;
        void update() override = 0;
        void addEntity(IEntity* entity);
        void removeEntity(IEntity* entity);
};

/**
 * @brief The SystemManager class manages a collection of systems.
 */
class SystemManager {
    public:
        /**
        * @brief Destructor for the SystemManager class.
        */
        SystemManager() = default;
        ~SystemManager() = default;
        /**
         * @brief Adds a new system to the collection.
         *
         * @tparam T The type of the system to add.
         * @tparam Args The types of the arguments to pass to the system's constructor.
         * @param args The arguments to pass to the system's constructor.
         */
        template<typename T, typename... Args>
        void addSystem(Args&&... args)
        {
            _systems.push_back(new T(std::forward<Args>(args)...));
        }

        /**
         * @brief Retrieves a system of the specified type.
         *
         * @tparam T The type of the system to retrieve.
         * @return A pointer to the system if found, nullptr otherwise.
         */
        template<typename T>
        T* getSystem()
        {
            for (auto& system : _systems) {
                if (typeid(*system) == typeid(T)) {
                    return dynamic_cast<T*>(system);
                }
            }
            return nullptr;
        }

        /**
         * @brief Updates all systems in the collection.
         */
        void update();
    private:
        std::vector<ISystem*> _systems; /**< The collection of systems managed by the SystemManager. */
};

class S_Parallax : public ASystem {
    public:
        S_Parallax() = default;
        ~S_Parallax();

        void initialize(const std::string &imagePath, int screenWidth, int screenHeight);
        Texture2D getBackground() const { return _background; }
        Vec2 getScaleFactor() const { return _scaleFactor; }
        Image getImage() const { return _image; }
        void setBackground(Image newTexture) { _background = LoadTextureFromImage(newTexture); }
        void setScaleFactor(Vec2 newVec2) { _scaleFactor = newVec2; }
        void setImage(std::string newImage)
        { 
            _image = LoadImage(newImage.c_str());
            setBackground(_image);
        }
        void update() override {};

    private:
        Image _image;
        Texture2D _background;
        Vec2 _scaleFactor;
};

class S_Renderer : public ASystem {
    public:
        S_Renderer() = default;
        S_Renderer(int w, int h, int fps, std::string wName, const std::string& imagePath);
        ~S_Renderer() = default;

        void render();
        void update() override;
        void closeWindow();

    private:
        int _screenWidth;
        int _screenHeight;
        int _targetFps;
        std::string _windowName;
        S_Parallax _parallax;

        Camera2D _camera;
};

class S_Network : public ASystem {
    public:
        S_Network() = default;
        ~S_Network() = default;
};

class S_AudioManager : public ASystem {
    public:
        S_AudioManager();
        ~S_AudioManager();
        
        void update() override {};
        std::map<std::string, Sound> const getSoundEffect() { return _sound_effects; }
        std::map<std::string, Music> const getBackgroundMusic() { return _background_music_game; }
    private:
        std::map<std::string, Sound> _sound_effects;
        std::map<std::string, Music> _background_music_game;
};

class S_EnemyAI : public ASystem {
    public:
        S_EnemyAI() = default;
        ~S_EnemyAI() = default;
};

class S_Collision : public ASystem {
    public:
        S_Collision() = default;
        ~S_Collision() = default;
        void update() override;
        bool checkCollision(IEntity* entity1, IEntity* entity2);
};

class S_Animation : public ASystem {
    public:
        S_Animation() = default;
        ~S_Animation() = default;
};

class S_EventManager : public ASystem {
    public:
        S_EventManager() = default;
        ~S_EventManager() = default;
        int EventKeyPressed(std::list<int> keys);
        void update() override;
};