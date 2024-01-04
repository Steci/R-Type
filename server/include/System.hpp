/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#include "../../engine/include/Engine.hpp"
#include "../../engine/include/System.hpp"

/**
 * @brief The S_Parallax class is the background which will be animated during the game.
 */
class S_Parallax : public System {
    public:
        /**
         * @brief the constructor of the class S_Parallax by default.
         */
        S_Parallax() = default;

        /**
         * @brief the destructor of the class S_Parallax.
         */
        ~S_Parallax();

        /**
         * @brief this function is to initialize the variables of the class.
         *
         * @param imagePath The imagePath is the background path.
         * @param screenWidth The screenWidth is the width screen.
         * @param screenHeight The screenHeight is the height screen.
         */
        void initialize(const std::string &imagePath, int screenWidth, int screenHeight);

        /**
         * @brief returns the current texture in the class.
         *
         * @return the current Texture2D in the class.
         */
        Texture2D getBackground() const { return _background; }

        /**
         * @brief returns the scale factor of background.
         *
         * @return returns the Vec2 of scale factor of background.
         */
        Vec2 getScaleFactor() const { return _scaleFactor; }

        /**
         * @brief returns the Image of background.
         *
         * @return returns the Image of background.
         */
        Image getImage() const { return _image; }

        /**
         * @brief setup the new texture for the background.
         *
         * @param newTexture the newTexture is the new Image to setup the new Texture of background for the game.
         */
        void setBackground(Image newTexture) { _background = LoadTextureFromImage(newTexture); }

        /**
         * @brief setup the new scale factor for the background.
         *
         * @param newVec2 the newVec2 is the scale factor of background.
         */
        void setScaleFactor(Vec2 newVec2) { _scaleFactor = newVec2; }

        /**
         * @brief setup the new image for the background.
         *
         * @param newImage the newImage is the new paht to setup the new Image of background for the game.
         */
        void setImage(std::string newImage)
        {
            _image = LoadImage(newImage.c_str());
            setBackground(_image);
        }
        void update() override {};

    private:
        Image _image; /**< The parallax Image. */
        Texture2D _background; /**< The parallax Texture2D. */
        Vec2 _scaleFactor; /**< The parallax scale factor. */
};

/**
 * @brief The S_Renderer class aims to ensure the display of all elements of the game
 */
class S_Renderer : public System {
    public:
        /**
         * @brief the constructor of the class S_Renderer by default.
         */
        S_Renderer() = default;

        /**
         * @brief the constructor of the class S_Renderer with params
         *
         * @param w The w is the width screen
         * @param h The h is the height screen
         * @param wName The wName is the name screen
         * @param imagePath The imagePath is the background path
         */
        S_Renderer(int w, int h, int fps, std::string wName, const std::string& imagePath);

        /**
         * @brief the destructor of the class S_Renderer by default.
         */
        ~S_Renderer() = default;

        void render();
        void update() override;
        void closeWindow();

    private:
        int _screenWidth; /**< The screen width. */
        int _screenHeight; /**< The screen height. */
        int _targetFps; /**< The fps for the display game. */
        std::string _windowName; /**< The screen name. */
        S_Parallax _parallax; /**< The S_Parallax system for the game background. */

        Camera2D _camera; /**< The Raylib Camera2D to help to display elements during the game. */
};

/**
 * @brief The S_AudioManager class manages all the sound effects and music present in the game
 */
class S_AudioManager : public System {
    public:
        /**
         * @brief the constructor of the class S_Renderer.
         */
        S_AudioManager();

        /**
         * @brief the destructor of the class S_Renderer.
         */
        ~S_AudioManager();

        void update() override {};

        /**
         * @brief Return all music in the game.
         *
         * @return all music in the game in std::map.
         */
        std::map<std::string, Sound> const getSoundEffect() { return _sound_effects; }

        /**
         * @brief Return all sound effects in the game.
         *
         * @return all music in the sound effects in std::map.
         */
        std::map<std::string, Music> const getBackgroundMusic() { return _background_music_game; }
    private:
        std::map<std::string, Sound> _sound_effects; /**< The sound effects of game. */
        std::map<std::string, Music> _background_music_game; /**< The musics of game. */
};

/**
 * @brief The S_EnemyAI class manages all action of ennemies.
 */
class S_EnemyAI : public System {
    public:
        /**
         * @brief the constructor of the class S_EnemyAI by default.
         */
        S_EnemyAI() = default;

        /**
         * @brief the destructor of the class S_EnemyAI by default.
         */
        ~S_EnemyAI() = default;
};

/**
 * @brief The S_Collision class manages all collision during the game.
 */
class S_Collision : public System {
    public:
        /**
         * @brief the constructor of the class S_Collision.
         */
        S_Collision();

        /**
         * @brief the destructor of the class S_Collision.
         */
        ~S_Collision();

        void update() override;

        /**
         * @brief Check collision between two entities.
         *
         * @param entity1 The entity1 is the pointer of the first entity that we want to check.
         * @param entity2 The entity2 is the pointer of the second entity that we want to check.
         * @return true if there is a collision between the two entities, if else false.
         */
        bool checkCollision(IEntity* entity1, IEntity* entity2);

        int screenWidth = 800; /**< The screen width. */
        int screenHeight = 600; /**< The screen height. */
};

class S_EventManager : public System {
    public:
        /**
         * @brief the constructor of the class S_EventManager by default.
         */
        S_EventManager() = default;
    
        /**
         * @brief the destructor of the class S_EventManager by default.
         */
        ~S_EventManager() = default;

        void update() override;

        /**
         * @brief Check if a key has been touched.
         *
         * @param keys The keys is the button lists.
         * @return the number that indicates which key was activated.
         */
        int EventKeyPressed(std::list<int> keys);
};