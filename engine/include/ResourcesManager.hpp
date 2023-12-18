/*
** EPITECH PROJECT, 2023
** GAME ENGINE
** File description:
** RessourcesManager
*/

#include <string>
#include <raylib>

#ifndef GAME_ENGINE_RESSOURCESMANAGER_HPP
    #define GAME_ENGINE_RESSOURCESMANAGER_HPP

namespace Engine {
    class ResourcesManager {
    public:
        /**
         * @brief Construct a new Resources Manager object
         *
         */
        ResourcesManager() = default;

        /**
         * @brief Destroy the Resources Manager object
         *
         */
        ~ResourcesManager();

        /**
         * @brief Load a Texture once time for optimisation
         *
         * @param path string to filepath for the texture
         * @return Texture2D&
         */
        Texture2D &LoadTextures(const std::string &path);

        /**
         * @brief Load a Image once time for optimisation
         *
         * @param path string to filepath for the picture
         * @return Image&
         */
        Image &LoadPictures(const std::string &path);

        /**
         * @brief Load a Music once time for optimisation
         *
         * @param path string to filepath for the picture
         * @return Music&
         */
        Music &LoadMusic(const std::string &path);

        /**
         * @brief Load a AudioStream once time for optimisation
         *
         * @param path string to filepath for the picture
         * @return AudioStream&
         */
        AudioStream &LoadAudio(const std::string &path);


    protected:
        std::map<const std::string, Texture2D> _texture;
        std::map<const std::string, Image> _image;
        std::map<const std::string, Music> _music;
        std::map<const std::string, AudioStream> _audio;
    private:
    };

    static ResourcesManager rManager;
}
#endif //GAME_ENGINE_RESSOURCESMANAGER_HPP