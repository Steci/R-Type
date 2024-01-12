/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#include "Engine.hpp"
#include "EngineSystem.hpp"

class S_Parallax : public System {
    public:
        S_Parallax() = default;
        ~S_Parallax();

        std::vector<Texture2D> getBackgrounds() const { return _backgrounds; }
        std::vector<Image> getImages() const { return _images; }

        void setScale(float newScale) { _scale = newScale; }
        float getScale() const { return _scale; }

        std::vector<float> getScrolling() const { return _scrolling; }

        void setBackground(Image newImage)
        {
            Texture2D background = LoadTextureFromImage(newImage);
            _backgrounds.push_back(background);
        }

        void add(std::string path, float force)
        {
            Image image = LoadImage(path.c_str());
            _images.push_back(image);
            _scrolling.push_back(0.0f);
            _scrollingForces.push_back(force);
            setBackground(image);
        }

        void update();

    private:
        std::vector<Image> _images;
        std::vector<Texture2D> _backgrounds;
        float _scale;
        std::vector<float> _scrolling;
        std::vector<float> _scrollingForces;
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

class S_EventManager : public System {
    public:
        S_EventManager() = default;
        ~S_EventManager() = default;
        void update() override {};
        int EventKeyPressed(std::list<int> keys);
        int getMovement();
        int getShoot();
        int getQuit();
};
