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
#include <map>
#include "Entity.hpp"
#include "System.hpp"

#define TICK_SPEED 30
#define DESIRED_SPEED 60


namespace server
{
    /**
     * @brief Class that represent the interaction between the client and the server
     * 
     */
    class Interaction : public AInteraction{
        public:
            /**
             * @brief Construct a new Interaction object
             * 
             */
            Interaction() {
                _movement = -1;
                _shoot = -1;
                _quit = -1;
                _createGame = -1;
            };
            
            /**
             * @brief Destroy the Interaction object
             * 
             */
            ~Interaction() {};

            /**
             * @brief Get the Client I D object
             * 
             * @return int is the client id
             */
            int getClientID() const {return _client_id;};

            /**
             * @brief Get the Connect object
             * 
             * @return int is the connect
             */
            int getConnect() const {return _connect;};

            /**
             * @brief Set the Client I D object
             * 
             * @param clientID is the client id
             */
            void setClientID(int clientID) {_client_id = clientID;};

            /**
             * @brief Set the Connect object
             * 
             * @param connect is the connect
             */
            void setConnect(int connect) {_connect = connect;};

            /**
             * @brief Set the Movement object
             * 
             * @param newMov is the movement
             */
            void setMovement(int newMov) {_movement = newMov;};

            /**
             * @brief Set the Game Id object
             * 
             * @param gameId is the game id
             */
            void setGameId(int gameId) {_game_id = gameId;};

            /**
             * @brief Get the Game Id object
             * 
             * @return int is the game id
             */
            int getGameId() const {return _game_id;};

            /**
             * @brief Deserialize the interaction
             * 
             * @param serializedData is the data to deserialize
             */
            void deserializeInteraction(const std::vector<char>& serializedData) {
                *this = *reinterpret_cast<const Interaction*>(serializedData.data());
            }

            /**
             * @brief Serialize the interaction
             * 
             * @return std::vector<char> is the serialized interaction
             */
            std::vector<char> serializeInteraction() {return {};};
        private:
            int _connect = -1;
            int _client_id = -1;
            int _game_id = -1;
    };

    /**
     * @brief Frame class that represent the frame send by the server
     * 
     */
    class Frame : public AFrame{
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
             * @brief Set the Tick object
             * 
             * @return std::vector<char> is the serialized frame
             */
            std::vector<char> serializeFrame();

            /**
             * @brief Get the Tick object
             * 
             * @return int is the tick
             */
            int getTick() const {return _tick;};
            
            /**
             * @brief Get Server
             * 
             * @return int is the server id
             */
            int getIDServer() const {return _gameId;};

            /**
             * @brief Clear the entities
             * 
             */
            void clearEntities() {_entities.clearEntities();};

            /**
             * @brief Check if is the end
             * 
             * @param it is the iterator
             * @param data is the data
             * @return true if is the end
             * @return false if is not the end
             */
            bool isEndMarker(const std::vector<char>::const_iterator& it, const std::vector<char>& data) {
                const std::string endMarker = "END";
                return std::distance(it, data.end()) >= endMarker.size() &&
                std::equal(endMarker.begin(), endMarker.end(), it);
            }

            /**
             * @brief Deserialize the frame
             * 
             * @param serializedData is the data to deserialize
             */
            void deserializeFrame(const std::vector<char>& serializedData);
    };

    /**
     * @brief Class that represent the game
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
            Game();

            /**
             * @brief Destroy the Game object
             * 
             */
            ~Game() = default;

            /**
             * @brief Run the game
             * 
             */
            void run();

            /**
             * @brief Add an interaction
             * 
             * @param interaction is the interaction
             */
            void addInteraction(Interaction interaction) {_mutex.lock();_interaction_client.push_back(interaction);_mutex.unlock();};

            /**
             * @brief Get the Functions object
             * 
             * @return std::vector<std::string> is the functions
             */
            std::vector<std::string> getFunctions() {return _functions;}

            /**
             * @brief Parse the command
             * 
             * @param input is the input
             * @return std::pair<std::string, std::string> is the command
             */
            std::pair<std::string, std::string> parseCommand(const std::string& input);

            /**
             * @brief Get the Functions Client object
             * 
             * @return std::vector<std::string> is the functions client
             */
            std::vector<std::string> getFunctionsClient();

            /**
             * @brief Get the Frames object
             * 
             * @return std::vector<Frame> is the frames
             */
            std::vector<Frame> getFrames() {_mutex_frame.lock();std::vector<Frame> frame = _frames;_mutex_frame.unlock();return frame;};

            /**
             * @brief Set the Game Id object
             * 
             * @param gameId is the game id
             */
            void setGameId(int gameId) {_gameId = gameId;};

            /**
             * @brief Get the Game Id object
             * 
             * @return int is the game id
             */
            int getGameId() const {return _gameId;};

            /**
             * @brief Set the Last Tick Send object
             * 
             * @param tick is the tick
             */
            void setLastTickSend(int tick) {_mutex_tick_send.lock();_last_tick_send = tick;_mutex_tick_send.unlock();};

            /**
             * @brief Get the Last Tick Send object
             * 
             * @return int is the last tick send
             */
            int getLastTickSend() const {return _last_tick_send;};

            /**
             * @brief Set the Tick object
             * 
             * @param tick is the tick
             */
            void setAvailaibleId(int id) {
                if (id > 4)
                    _avalaible_id = -1;
                else
                    _avalaible_id = id;
            };

            /**
             * @brief Get the Availaible Id object
             * 
             * @return int is the availaible id
             */
            int getAvailaibleId() const {return _avalaible_id;};
            
            /**
             * @brief Copy assignment operator
             * 
             * @param other is the other game
             * @return Game& is the game
             */
            Game& operator=(const Game& other)
            {
                // Self-assignment detection
                if (this == &other)
                    return *this;

                // Copy simple fields
                _tickSpeed = other._tickSpeed;
                _tick = other._tick;
                _gameId = other._gameId;

                // For vectors and maps, you can typically use the default copy assignment
                _interaction_client = other._interaction_client;
                _functions = other._functions;
                _functions_client = other._functions_client;
                _fonctions_map = other._fonctions_map;
                _frames = other._frames;

                // Note: mutexes and other synchronization primitives should not be copied.
                // You may need to think about how to handle them in the context of your program.

                return *this;
            }

        private:
            int _tickSpeed = TICK_SPEED;
            int _tick;
            std::mutex _mutex_tick_send;
            int _last_tick_send = 0;
            int _gameId;
            std::mutex _mutex;
            std::vector<Interaction> _interaction_client;
            typedef void (*Key)(int button);
            std::vector<std::string> _functions;
            std::vector<std::string> _functions_client;
            std::mutex _mutex_client;
            std::map<std::string, functionsExecution> _fonctions_map;
            std::mutex _mutex_frame;
            std::vector<Frame> _frames; // ici mettre les frames à display

            /**
             * @brief Fill the frame with the entities
             * 
             * @param entities the entities to put in the frame
             */
            void fillFrame(SparseArray<IEntity> entities);
            int _avalaible_id = 1;
    };
}