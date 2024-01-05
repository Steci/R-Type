/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.hpp
*/

#pragma once

#include "../../engine/include/Engine.hpp"
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
            void setInteraction() {}; //ici laetitia tu mettre le mouvement qui nous intéresse à la valeur qu'on veut
            void clearInteraction(); //ici laetitia tu clear les intéraction donc celles que tu vas rajouter aussi
            std::vector<char> serializeInteraction() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Interaction));
            }
            void deserializeInteraction(const std::vector<char>& serializedData) {
                *this = *reinterpret_cast<const Interaction*>(serializedData.data());
            }
        private:
            int _movement = 0; // ici mettre mettre le mouvement qu'on veut et laisser à 0 si rien (par ex 1 pour gauche, 2 pour droite, etc... tu peux mettre ce que tu veux c'est juste des exemple donc si tu veux 40000000 c'est gauche faut juste penser à respecter cette valeur côté server)
            int _shoot = 0; // 0 si rien 1 si quelque chose
            int _quit = 0; // 0 si rien 1 si le client veut quitter
            //etc...
    };

    class Frame {
        public:
            Frame() {}; // penser à remplir le constructeur si besoin
            ~Frame() {}; // penser à remplir le destructeur si besoin
            void setTick(int tick) {_tick = tick;};
            std::vector<char> serializeFrame() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Frame));
            }
            bool operator==(const Frame& other) const {return *this == other;}
            bool operator!=(const Frame& other) const {return !(*this == other);}
            Frame& operator=(const Frame& other);
            int getTick() const {return _tick;};
        private:
            int _tick;
            // ici mettre les infos de la frame à display
    };

    class Game
    {
        typedef void (Game::*functionsExecution)(int, SystemManager, SparseArray<IEntity>&);

        public:
            Game();
            ~Game();
            void run();
            void addInteraction(Interaction interaction) {_mutex.lock();_interaction_client = interaction;_mutex.unlock();};
            std::vector<std::string> getFunctions() {return _functions;}
            std::pair<std::string, std::string> parseCommand(const std::string& input);
            std::vector<std::string> getFunctionsClient();
            std::vector<Frame> getFrames() {_mutex_frame.lock();std::vector<Frame> frame = _frames;_mutex_frame.unlock();return frame;};

            // écrire les fonctions pour vérifier si on a le droit de faire ses commandes

            // void actionUpCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            // void actionDownCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            // void actionLeftCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            // void actionRightCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            // void actionDebugCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            // void actionQuitCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            // void actionConnectCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            // void actionShootCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            // void actionDamageCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            // void actionScoreCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);


        private:
            int _tickSpeed = TICK_SPEED;
            int _tick;
            std::mutex _mutex;
            Interaction _interaction_client;
            // std::vector<std::string> _functions_server;
            // std::map<int, Key> m{{KEY_A, Key}, {KEY_RIGHT, Key}, {KEY_LEFT, Key}, {KEY_DOWN, Key}, {KEY_ESCAPE, Key}};
            typedef void (*Key)(int button);
            std::vector<std::string> _functions;
            std::vector<std::string> _functions_client;
            std::mutex _mutex_client;
            std::map<std::string, functionsExecution> _fonctions_map;
            std::mutex _mutex_frame;
            std::vector<Frame> _frames; // ici mettre les frames à display
            void fillFrame();
    };
}
