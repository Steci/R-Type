/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.hpp
*/

#pragma once

#include "../../engine/include/Engine.hpp"
#include "../../engine/include/Network.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include <algorithm>
#include <map>
#include "Entity.hpp"
#include "System.hpp"
#include "Infos.hpp"

#define TICK_SPEED 66

namespace client {

    /**
     * @brief The Interaction sends information to the server.
    */
    class Interaction : public AInteraction{
        public:

            /**
             * @brief the constructor of the class Interaction in default params.
             *
            */
            Interaction() {
                _movement = 0;
                _shoot = 0;
                _quit = 0;
                _createGame = 0;
            };

            /**
             * @brief the destructor of the class Interaction by default.
             *
            */
            ~Interaction() {};

            /**
             * @brief allows you to serialize data in the form of std::vector<char>.
             *
             * @return std::vector<char> which will be sent to the server.
            */
            std::vector<char> serializeInteraction() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Interaction));
            }
    };

    /**
     * @brief The Frame receives information to the server.
    */
    class Frame : public AFrame {
        public:
            /**
             * @brief the constructor of the class Frame in default.
             *
            */
            Frame() {};

            /**
             * @brief the destructor of the class Frame by default.
             *
            */
            ~Frame() {};

            int getTick() const {return _tick;};
            int getIDServer() const {return _gameId;};
            void clearEntities() {_entities.clearEntities();};
            bool isEndMarker(const std::vector<char>::const_iterator& it, const std::vector<char>& data) {
                const std::string endMarker = "END";
                return std::distance(it, data.end()) >= endMarker.size() &&
                std::equal(endMarker.begin(), endMarker.end(), it);
            }
            void deserializeFrame(const std::vector<char>& serializedData);
    };

    class Menu
    {
        public:
            Menu() {};
            ~Menu() = default;

            void render(int screenWidth);
            bool getStatusMenu() {_mutex_status.lock();bool tmp = _status;_mutex_status.unlock();return tmp;};
            bool getJoinGame() {_mutex_joinGame.lock();bool tmp = _JoinGame;_mutex_joinGame.unlock();return tmp;};
            int getIdServerJoin() {_mutex_idServerJoin.lock();int tmp = _idServerJoin;_mutex_idServerJoin.unlock();return tmp;};
            bool getCreateGame() {_mutex_createGame.lock();bool tmp = _createGame;_mutex_createGame.unlock();return tmp;};
            std::string getError() {_mutex_error.lock();std::string tmp = _error;_mutex_error.unlock();return tmp;};
            std::vector<int> getIdGames() {_mutex_idGames.lock();std::vector<int> tmp = _idGames;_mutex_idGames.unlock();return tmp;};
            void setStatusMenu(bool status) {_mutex_status.lock();_status = status;_mutex_status.unlock();};
            void setJoinGame(bool joinGame) {_mutex_joinGame.lock();_JoinGame = joinGame;_mutex_joinGame.unlock();};
            void setIdServerJoin(int idServerJoin) {_mutex_idServerJoin.lock();_idServerJoin = idServerJoin;_mutex_idServerJoin.unlock();};
            void setCreateGame(bool createGame) {_mutex_createGame.lock();_createGame = createGame;_mutex_createGame.unlock();};
            void setError(std::string error) {_mutex_error.lock();_error = error;_mutex_error.unlock();};
            void setIdGames(std::vector<int> idGames) {_mutex_idGames.lock();_idGames = idGames;_mutex_idGames.unlock();};

        private:
            std::mutex _mutex_status;
            std::mutex _mutex_joinGame;
            std::mutex _mutex_createGame;
            std::mutex _mutex_idServerJoin;
            std::mutex _mutex_error;
            std::mutex _mutex_idGames;
            bool _status = true;
            bool _JoinGame = false;
            bool _createGame = false;
            int _idServerJoin = -1;
            std::vector<int> _idGames;
            std::string _error = "";
    };

    class Game
    {
        typedef void (Game::*functionsExecution)(int, SystemManager, SparseArray<IEntity>&);

        public:
            Game() {
                _tick = 0;
            };
            ~Game();
            void run();
            std::vector<Interaction> getInteractions() {_mutex_interactions.lock();std::vector<Interaction> tmp = _interactions;_mutex_interactions.unlock();return tmp;};
            void deleteInteraction(int nbr_interaction) {_mutex_interactions.lock();_interactions.erase(_interactions.begin() + nbr_interaction);_mutex_interactions.unlock();};
            void addFrame(Frame frame) {_mutex_frames.lock();_frames.push_back(frame);_mutex_frames.unlock();};
            void createTextures();
            Menu *getMenu() {return &_menu;};
            // à faire pour rajouter les frame à display
            // void addFrame(Frame frame) {_mutex_frame.lock();_frames.push_back(frame);_mutex_frame.unlock();};

            // il faut refaire toutes ses fonctions pour juste qu'elles récupère l'interraction et qu'elle l'envoi au serv via la class en dessous
            // pour remplir _interaction il faut lock _mutex puis l'unlock !!!!! si tu oublie l'un des 2 c'est la merde

        private:
            int _tickSpeed = TICK_SPEED;
            int _tick;
            std::mutex _mutex_interactions;
            std::vector<Interaction> _interactions;
            std::map<int, Infos> _ennemy_sprites;
            std::map<int, Infos> _player_sprites;
            std::map<int, Infos> _utils_sprites;
            // à faire pour récup les frame du jeu à display
            std::mutex _mutex_frames;
            std::vector<Frame> _frames; // ici mettre les frames à display
            void infoInteraction(int mov, int shoot, int quit, int createGame);
            Menu _menu;
    };
}