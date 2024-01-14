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
    class Interaction : public AInteraction{
        public:
            Interaction() {
                _movement = -1;
                _shoot = -1;
                _quit = -1;
                _createGame = -1;
            };
            ~Interaction() {};
            int getClientID() const {return _client_id;};
            int getConnect() const {return _connect;};
            void setClientID(int clientID) {_client_id = clientID;};
            void setConnect(int connect) {_connect = connect;};
            void setMovement(int newMov) {_movement = newMov;};
            void setGameId(int gameId) {_game_id = gameId;};
            int getGameId() const {return _game_id;};
            void deserializeInteraction(const std::vector<char>& serializedData) {
                *this = *reinterpret_cast<const Interaction*>(serializedData.data());
            }
            std::vector<char> serializeInteraction() {return {};};
        private:
            int _connect = -1;
            int _client_id = -1;
            int _game_id = -1;
    };

    class Frame : public AFrame{
        public:
            Frame() = default;
            ~Frame() = default;
            std::vector<char> serializeFrame();
            int getTick() const {return _tick;};
            int getIDServer() const {return _gameId;};
            void clearEntities() {_entities.clearEntities();};
            bool isEndMarker(const std::vector<char>::const_iterator& it, const std::vector<char>& data) {
                const std::string endMarker = "END";
                return static_cast<std::string::size_type>(std::distance(it, data.end())) >= endMarker.size() &&
                       std::equal(endMarker.begin(), endMarker.end(), it);
            }
            void deserializeFrame(const std::vector<char>& serializedData);
    };

    class Game
    {
        typedef void (Game::*functionsExecution)(int, SystemManager, SparseArray<IEntity>&);

        public:
            Game();
            ~Game() = default;
            void run();
            void addInteraction(Interaction interaction) {_mutex.lock();_interaction_client.push_back(interaction);_mutex.unlock();};
            std::vector<std::string> getFunctions() {return _functions;}
            std::pair<std::string, std::string> parseCommand(const std::string& input);
            std::vector<std::string> getFunctionsClient();
            std::vector<Frame> getFrames() {_mutex_frame.lock();std::vector<Frame> frame = _frames;_mutex_frame.unlock();return frame;};
            void setGameId(int gameId) {_gameId = gameId;};
            int getGameId() const {return _gameId;};
            void setLastTickSend(int tick) {_mutex_tick_send.lock();_last_tick_send = tick;_mutex_tick_send.unlock();};
            int getLastTickSend() const {return _last_tick_send;};
            void setAvailaibleId(int id) {
                if (id > 4)
                    _avalaible_id = -1;
                else
                    _avalaible_id = id;
            };
            int getAvailaibleId() const {return _avalaible_id;};
            // écrire les fonctions pour vérifier si on a le droit de faire ses commandes
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
            void fillFrame(SparseArray<IEntity> entities);
            int _avalaible_id = 1;
    };
}