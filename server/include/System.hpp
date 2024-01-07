/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#include "../../engine/include/Engine.hpp"
#include "../../engine/include/System.hpp"

class S_Parallax : public System {
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

class S_Renderer : public System {
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

class S_AudioManager : public System {
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

class S_EnemyAI : public System {
    public:
        S_EnemyAI(SparseArray<IEntity> &sparseEntities);
        ~S_EnemyAI();
        void update() override;
    private:
        SparseArray<IEntity> &_sparseEntities;
};

class S_Collision : public System {
    public:
        S_Collision(SparseArray<IEntity> &sparseEntities);
        ~S_Collision();
        void update() override;
        bool checkCollision(C_Transform *transform1, C_Transform *transform2, C_Hitbox *hitbox1, C_Hitbox *hitbox2);
        int screenWidth = 800;
        int screenHeight = 600;
    private:
        SparseArray<IEntity> &_sparseEntities;
};

class S_EventManager : public System {
    public:
        S_EventManager() = default;
        ~S_EventManager() = default;
        void update() override;
        int EventKeyPressed(std::list<int> keys);
};