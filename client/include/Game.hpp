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

namespace client {

    // cette class va être envoyé au server pour lui dire ce qu'on fait donc toute interraction avec le jeu passe par ici
    // cette class existe aussi dans le server donc fait gaffe si tu changes un truc faut aussi le changer côté serveur mais à terme elle existera qu'à un endroit (oui j'aurais pu le faire dès le début mais je suis crevé et si je change mtn ça va être un bordel sans nom)
    class Interaction {
        public:
            Interaction() {};
            ~Interaction() {};
            void setInteraction(int inter); //ici laetitia tu mettre l'interaction qui nous intéresse à la valeur qu'on veut et surtout hésite pas à le changer prck c'est que du fonctionel là
            std::vector<char> serializeInteraction() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Interaction));
            }
        private:
            int _movement = 0; // ici mettre mettre le mouvement qu'on veut et laisser à 0 si rien (par ex 1 pour gauche, 2 pour droite, etc... tu peux mettre ce que tu veux c'est juste des exemple donc si tu veux 40000000 c'est gauche faut juste penser à respecter cette valeur côté server) !!!!!! jamais négatif !!!!!!
            int _shoot = 0; // 0 si rien 1 si quelque chose
            int _quit = 0; // 0 si rien 1 si le client veut quitter
            //etc...
    };

    class Frame {
        public:
            Frame() {}; // penser à remplir le constructeur si besoin
            ~Frame() {}; // penser à remplir le destructeur si besoin
            int getTick() const {return _tick;};
            void deserializeFrame(const std::vector<char>& serializedData) {
                *this = *reinterpret_cast<const Frame*>(serializedData.data());
            }
        private:
            int _tick = -1;
            // ici mettre les infos de la frame à display
    };

    class Game
    {
        typedef void (Game::*functionsExecution)(int, SystemManager, SparseArray<IEntity>&);

        public:
            Game();
            ~Game();
            void run();
            std::vector<Interaction> getInteractions() {_mutex_interactions.lock();std::vector<Interaction> tmp = _interactions;_mutex_interactions.unlock();return tmp;};
            void deleteInteraction(int nbr_interaction) {_mutex_interactions.lock();_interactions.erase(_interactions.begin() + nbr_interaction);_mutex_interactions.unlock();};
            void addFrame(Frame frame) {_mutex_frames.lock();_frames.push_back(frame);_mutex_frames.unlock();};
            // à faire pour rajouter les frame à display
            // void addFrame(Frame frame) {_mutex_frame.lock();_frames.push_back(frame);_mutex_frame.unlock();};

            // il faut refaire toutes ses fonctions pour juste qu'elles récupère l'interraction et qu'elle l'envoi au serv via la class en dessous
            // pour remplir _interaction il faut lock _mutex puis l'unlock !!!!! si tu oublie l'un des 2 c'est la merde

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
            std::mutex _mutex_interactions;
            std::vector<Interaction> _interactions;
            // à faire pour récup les frame du jeu à display
            std::mutex _mutex_frames;
            std::vector<Frame> _frames; // ici mettre les frames à display
            void testInteraction();
    };

}