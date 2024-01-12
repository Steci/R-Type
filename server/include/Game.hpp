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

#define TICK_SPEED 66

namespace server
{
    class Interaction { // cette class va être envoyé au server pour lui dire ce qu'on fait donc toute interraction avec le jeu passe par ici
        public:
            Interaction() {};
            ~Interaction() {};

            int getMovement() const {return _movement;};
            int getShoot() const {return _shoot;};
            int getQuit() const {return _quit;};

            int getClientID() const {return _client_id;};
            int getConnect() const {return _connect;};
            int getCreateGame() const {return _createGame;};
            void setClientID(int clientID) {_client_id = clientID;};
            void setConnect(int connect) {_connect = connect;};
            void deserializeInteraction(const std::vector<char>& serializedData) {
                *this = *reinterpret_cast<const Interaction*>(serializedData.data());
            }
        private:
            int _movement = -1; // ici mettre mettre le mouvement qu'on veut et laisser à 0 si rien (par ex 1 pour gauche, 2 pour droite, etc... tu peux mettre ce que tu veux c'est juste des exemple donc si tu veux 40000000 c'est gauche faut juste penser à respecter cette valeur côté server)
            int _shoot = -1; // 0 si rien 1 si quelque chose
            int _quit = -1; // 0 si rien 1 si le client veut quitter
            int _createGame = -1; // 0 si rien 1 si le client veut créer une game
            //etc... rajouter les variables communes au dessus de se commentaire
            int _connect = -1; // 0 si rien 1 si le client veut se connecter
            int _client_id;
    };

    class Frame : public AFrame{
        public:
            Frame() = default;
            ~Frame() = default;
            std::vector<char> serializeFrame();
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
            void setGameId(int game_id) {_game_id = game_id;};
            int getGameId() const {return _game_id;};
            // écrire les fonctions pour vérifier si on a le droit de faire ses commandes
            Game& operator=(const Game& other)
            {
                // Self-assignment detection
                if (this == &other)
                    return *this;

                // Copy simple fields
                _tickSpeed = other._tickSpeed;
                _tick = other._tick;
                _game_id = other._game_id;

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
            int _game_id;
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
    };
}
