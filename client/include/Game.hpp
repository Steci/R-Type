/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.hpp
*/

#pragma once

#include "Engine.hpp"
#include "EngineNetwork.hpp"
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
     * @brief Interaction class
     * 
     */
    class Interaction : public AInteraction{
        public:
            /**
             * @brief Construct a new Interaction object
             * 
             */
            Interaction() {
                _movement = 0;
                _shoot = 0;
                _quit = 0;
                _createGame = 0;
            };

            /**
             * @brief Destroy the Interaction object
             * 
             */
            ~Interaction() {};

            /**
             * @brief Get the Movement object Serialized
             * 
             * @return std::vector<char> is the movement serialized
             */
            std::vector<char> serializeInteraction() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Interaction));
            }

            /**
             * @brief Get the Client ID object
             * 
             */
            int getClientID() const {return 0;};

            /**
             * @brief Get the Connect object
             * 
             */
            int getConnect() const {return 0;};

            /**
             * @brief Set the Client ID object
             * 
             * @param clientID is the client ID
             */
            void setClientID(int clientID) {};

            /**
             * @brief Set the Connect object
             * 
             * @param connect is the connect
             */
            void setConnect(int connect) {};

            
            /**
             * @brief Deserialize the interaction
             * 
             * @param serializedData is the serialized data
             */
            void deserializeInteraction(const std::vector<char>& serializedData) {};
        private:
            int _connect = -1;
            int _client_id = -1;
    };

    /**
     * @brief Frame class
     * 
     */
    class Frame : public AFrame {
        public:
            /**
             * @brief Construct a new Frame object
             * 
             */
            Frame() = default;

            /**
             * @brief Destroy the Frame object
             * 
             */
            ~Frame() = default;


            /**
             * @brief Get the Serialized Frame object
             * 
             * @return * std::vector<char> 
             */
            std::vector<char> serializeFrame();

            /**
             * @brief Get the Tick object
             * 
             * @return int is the tick
             */
            int getTick() const {return _tick;};

            /**
             * @brief Get id of the server
             * 
             * @return  int is the id of the server
             */
            int getIDServer() const {return _gameId;};

            /**
             * @brief Clear all entities
             * 
             */
            void clearEntities() {_entities.clearEntities();};

            /**
             * @brief Check if is end marker
             * 
             * @param it is the iterator
             * @param data is the data
             * @return bool is the end marker
             */
            bool isEndMarker(const std::vector<char>::const_iterator& it, const std::vector<char>& data) {
                const std::string endMarker = "END";
                return std::distance(it, data.end()) >= endMarker.size() &&
                std::equal(endMarker.begin(), endMarker.end(), it);
            }

            /**
             * @brief Deserialize the frame
             * 
             * @param serializedData is the serialized data
             */
            void deserializeFrame(const std::vector<char>& serializedData);
    };

    /**
     * @brief Menu class
     * 
     */
    class Menu
    {
        public:

            /**
             * @brief Construct a new Menu object
             * 
             */
            Menu() {};

            /**
             * @brief Destroy the Menu object
             * 
             */
            ~Menu() = default;

            /**
             * @brief Render the menu
             * 
             * @param screenWidth is the screen width
             */
            void render(int screenWidth);

            /**
             * @brief Get the Status Menu object
             * 
             * @return true if the menu is open
             * @return false if the menu is close
             */
            bool getStatusMenu() {_mutex_status.lock();bool tmp = _status;_mutex_status.unlock();return tmp;};

            /**
             * @brief Get the Join Game object
             * 
             * @return true if the player want to join a game
             * @return false if the player don't want to join a game
             */
            bool getJoinGame() {_mutex_joinGame.lock();bool tmp = _JoinGame;_mutex_joinGame.unlock();return tmp;};

            /**
             * @brief Get the Id Server Join object
             * 
             * @return int is the id of the server to join
             */
            int getIdServerJoin() {_mutex_idServerJoin.lock();int tmp = _idServerJoin;_mutex_idServerJoin.unlock();return tmp;};

            /**
             * @brief Get the Selected Party object
             * 
             * @return int is the selected party
             */
            int getSelectedParty() {_mutex_selectedParty.lock();int tmp = _selectedParty;_mutex_selectedParty.unlock();return tmp;};

            /**
             * @brief Get the Create Game object
             * 
             * @return true if the player want to create a game
             * @return false if the player don't want to create a game
             */
            bool getCreateGame() {_mutex_createGame.lock();bool tmp = _createGame;_mutex_createGame.unlock();return tmp;};

            /**
             * @brief Get the Error object
             * 
             * @return std::string is the error
             */
            std::string getError() {_mutex_error.lock();std::string tmp = _error;_mutex_error.unlock();return tmp;};

            /**
             * @brief Get the Id Games object
             * 
             * @return std::vector<int> is the id of the games
             */
            std::vector<int> getIdGames() {_mutex_idGames.lock();std::vector<int> tmp = _idGames;_mutex_idGames.unlock();return tmp;};

            /**
             * @brief Set the Status Menu object
             * 
             * @param status is the status of the menu
             */
            void setStatusMenu(bool status) {_mutex_status.lock();_status = status;_mutex_status.unlock();};

            /**
             * @brief Set the Join Game object
             * 
             * @param joinGame is the join game
             */
            void setJoinGame(bool joinGame) {_mutex_joinGame.lock();_JoinGame = joinGame;_mutex_joinGame.unlock();};

            /**
             * @brief Set the Id Server Join object
             * 
             * @param idServerJoin is the id of the server to join
             */
            void setIdServerJoin(int idServerJoin) {_mutex_idServerJoin.lock();_idServerJoin = idServerJoin;_mutex_idServerJoin.unlock();};

            /**
             * @brief Set the Selected Party object
             * 
             * @param selectedParty is the selected party
             */
            void setSelectedParty(int selectedParty) {_mutex_selectedParty.lock();_selectedParty = selectedParty;_mutex_selectedParty.unlock();};

            /**
             * @brief Set the Create Game object
             * 
             * @param createGame is the create game
             */
            void setCreateGame(bool createGame) {_mutex_createGame.lock();_createGame = createGame;_mutex_createGame.unlock();};

            /**
             * @brief Set the Error object
             * 
             * @param error is the error
             */
            void setError(std::string error) {_mutex_error.lock();_error = error;_mutex_error.unlock();};

            /**
             * @brief Set the Id Games object
             * 
             * @param idGames is the id of the games
             */
            void setIdGames(std::vector<int> idGames) {_mutex_idGames.lock();_idGames = idGames;_mutex_idGames.unlock();};

        private:
            std::mutex _mutex_status;
            std::mutex _mutex_joinGame;
            std::mutex _mutex_createGame;
            std::mutex _mutex_idServerJoin;
            std::mutex _mutex_selectedParty;
            std::mutex _mutex_error;
            std::mutex _mutex_idGames;
            bool _status = true;
            bool _JoinGame = false;
            bool _createGame = false;
            int _idServerJoin = -1;
            int _selectedParty = -1;
            std::vector<int> _idGames;
            std::string _error = "";
    };

    /**
     * @brief Game class
     * 
     */
    class Game
    {
        typedef void (Game::*functionsExecution)(int, SystemManager, SparseArray<IEntity>&);

        public:

            /**
             * @brief Construct a new Game object
             * 
             */
            Game(): _tickSpeed(TICK_SPEED), _tick(0) {};

            /**
             * @brief Destroy the Game object
             * 
             */
            ~Game();

            /**
             * @brief Run the game
             * 
             */
            void run();

            /**
             * @brief Get the Interactions object
             * 
             * @return std::vector<Interaction> is the interactions
             */
            std::vector<Interaction> getInteractions() {_mutex_interactions.lock();std::vector<Interaction> tmp = _interactions;_mutex_interactions.unlock();return tmp;};
            
            /**
             * @brief Get the Frames object
             * 
             * @param nbr_interaction is the number of interaction
             */
            void deleteInteraction(int nbr_interaction) {
                _mutex_interactions.lock();
                if (!_interactions.empty() && nbr_interaction < _interactions.size()) {
                    _interactions.erase(_interactions.begin() + nbr_interaction);
                } else {
                    _interactions.clear();
                }
                _mutex_interactions.unlock();
            };
            //void deleteInteraction(int nbr_interaction) {_mutex_interactions.lock();_interactions.erase(_interactions.begin() + nbr_interaction);_mutex_interactions.unlock();};
            
            /**
             * @brief Get the Frames object
             * 
             * @param frame is the frame
             */
            void addFrame(Frame frame) {_mutex_frames.lock();_frames.push_back(frame);_mutex_frames.unlock();};

            /**
             * @brief Get the Frames object
             * 
             * @return std::vector<Frame> is the frames
             */
            void createTextures();

            /**
             * @brief Get the Frames object
             * 
             * @return std::vector<Frame> is the frames
             */
            Menu *getMenu() {return &_menu;};

            /**
             * @brief Get the Frames object
             * 
             * @return std::vector<Frame> is the frames
             */
            bool getStatusGame() {return _statusGame;};

        private:
            bool _statusGame = false;
            int _tickSpeed = TICK_SPEED;
            int _tick;
            std::mutex _mutex_interactions;
            std::vector<Interaction> _interactions;
            std::map<int, Infos> _ennemy_sprites;
            std::map<int, Infos> _player_sprites;
            std::map<int, Infos> _utils_sprites;
            std::mutex _mutex_frames;
            std::vector<Frame> _frames;

            /**
             * @brief Get the Frames object
             * 
             * @return std::vector<Frame> is the frames
             */
            void infoInteraction(int mov, int shoot, int quit, int createGame);
            Menu _menu;
    };
}
