/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#include "Engine.hpp"
#include "EngineSystem.hpp"

/**
 * @brief The S_Parallax class is the parallax system.
 * 
 */
class S_Parallax : public System {
    public:
        /**
         * @brief Construct a new S_Parallax object
         * 
         */
        S_Parallax() = default;

        /**
         * @brief Destroy the s parallax object
         * 
         */
        ~S_Parallax();

        /**
         * @brief Get the Backgrounds object
         * 
         * @return std::vector<Texture2D> is the vector of the background textures.
         */
        std::vector<Texture2D> getBackgrounds() const { return _backgrounds; }

        /**
         * @brief Get the Images object
         * 
         * @return std::vector<Image> is the vector of the images.
         */
        std::vector<Image> getImages() const { return _images; }

        /**
         * @brief Set the Scale object
         * 
         * @param newScale is the new scale.
         */
        void setScale(float newScale) { _scale = newScale; }

        /**
         * @brief Get the Scale object
         * 
         * @return float is the scale.
         */
        float getScale() const { return _scale; }

        /**
         * @brief Get the Scrolling object
         * 
         * @return std::vector<float> is the vector of the scrolling.
         */
        std::vector<float> getScrolling() const { return _scrolling; }

        /**
         * @brief Set the Background object
         * 
         * @param newImage is the new image.
         */
        void setBackground(Image newImage)
        {
            Texture2D background = LoadTextureFromImage(newImage);
            _backgrounds.push_back(background);
        }

        /**
         * @brief Add a new image.
         * 
         * @param path is the path of the image.
         * @param force is the force of the scrolling.
         */
        void add(std::string path, float force)
        {
            Image image = LoadImage(path.c_str());
            _images.push_back(image);
            _scrolling.push_back(0.0f);
            _scrollingForces.push_back(force);
            setBackground(image);
        }

        /**
         * @brief Update the parallax.
         * 
         */
        void update();

    private:
        std::vector<Image> _images;
        std::vector<Texture2D> _backgrounds;
        float _scale;
        std::vector<float> _scrolling;
        std::vector<float> _scrollingForces;
};

/**
 * @brief The S_Renderer class is the renderer system.
 * 
 */
class S_Renderer : public System {
    public:
        /**
         * @brief Construct a new s renderer object
         * 
         */
        S_Renderer() = default;

        /**
         * @brief Construct a new s renderer object
         * 
         * @param w is the width.
         * @param h is the height.
         * @param fps is the fps.
         * @param wName is the window name.
         * @param imagePath is the path of the image.
         */
        S_Renderer(int w, int h, int fps, std::string wName, const std::string& imagePath);

        /**
         * @brief Destroy the s renderer object
         * 
         */
        ~S_Renderer() = default;

        /**
         * @brief Render the renderer.
         * 
         */
        void render();

        /**
         * @brief Update the renderer.
         * 
         */
        void update() override;

        /**
         * @brief Set the IDServer object
         * 
         * @param new_idServer is the new id server.
         */
        void setIDServer(int new_idServer) {_idServer = new_idServer;};

        /**
         * @brief Set the Status Game object
         * 
         * @param newStatusGame is the new status game.
         */
        void setStatusGame(bool newStatusGame) {_statusGame = newStatusGame;};

        /**
         * @brief Get the Status Game object
         * 
         * @return bool is the status game.
         */
        bool getStatusGame() {return _statusGame;};

    private:
        int _screenWidth;
        int _screenHeight;
        int _targetFps;
        int _idServer;
        bool _statusGame = false;
        std::string _windowName;
        S_Parallax _parallax;

        Camera2D _camera;
};

/**
 * @brief The S_AudioManager class is the Audio system.
 * 
 */
class S_AudioManager : public System {
    public:
        /**
         * @brief Construct a new s audiomanager object
         * 
         */
        S_AudioManager();

        /**
         * @brief Destroy the s audiomanager object
         * 
         */
        ~S_AudioManager();

        /**
         * @brief Update the audio manager.
         * 
         */
        void update() override {};

        /**
         * @brief Get the Sound Effect object
         * 
         * @return std::map<std::string, Sound> const is the map of the sound effects.
         */
        std::map<std::string, Sound> const getSoundEffect() { return _sound_effects; }

        /**
         * @brief Get the Background Music object
         * 
         * @return std::map<std::string, Music> const is the map of the background music.
         */
        std::map<std::string, Music> const getBackgroundMusic() { return _background_music_game; }
    private:
        std::map<std::string, Sound> _sound_effects;
        std::map<std::string, Music> _background_music_game;
};

/**
 * @brief The S_EventManager class is the event manager system.
 * 
 */
class S_EventManager : public System {
    public:
        /**
         * @brief Construct a new s eventmanager object
         * 
         */
        S_EventManager() = default;

        /**
         * @brief Destroy the s eventmanager object
         * 
         */
        ~S_EventManager() = default;

        /**
         * @brief Update the event manager.
         * 
         */
        void update() override {};

        /**
         * @brief EventKeyPressed is the event when a key is pressed.
         * 
         * @param keys is the list of the keys.
         * @return int is the movement.
         */
        int EventKeyPressed(std::list<int> keys);

        /**
         * @brief Get the Movement object
         * 
         * @return int is the movement.
         */
        int getMovement();

        /**
         * @brief Get the Shoot object
         * 
         * @return int is the shoot.
         */
        int getShoot();

        /**
         * @brief Get the Quit object
         * 
         * @return int is the quit.
         */
        int getQuit();
};
