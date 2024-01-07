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
#include <sstream>
#include <algorithm>
#include <map>
#include "Entity.hpp"
#include "System.hpp"
#include "Infos.hpp"

#define TICK_SPEED 66

namespace client {

    // cette class va être envoyé au server pour lui dire ce qu'on fait donc toute interraction avec le jeu passe par ici
    // cette class existe aussi dans le server donc fait gaffe si tu changes un truc faut aussi le changer côté serveur mais à terme elle existera qu'à un endroit (oui j'aurais pu le faire dès le début mais je suis crevé et si je change mtn ça va être un bordel sans nom)
    class Interaction {
        public:
            Interaction() {};
            ~Interaction() {};
            //ici laetitia tu mettre l'interaction qui nous intéresse à la valeur qu'on veut et surtout hésite pas à le changer prck c'est que du fonctionel là
            void setInteraction(int mov = 0, int shoot = 0, int quit = 0) {
                _movement = mov;
                _shoot = shoot;
                _quit = quit;
            }
            std::vector<char> serializeInteraction() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Interaction));
            }
        private:
            int _movement = 0; // ici mettre mettre le mouvement qu'on veut et laisser à 0 si rien (par ex 1 pour gauche, 2 pour droite, etc... tu peux mettre ce que tu veux c'est juste des exemple donc si tu veux 40000000 c'est gauche faut juste penser à respecter cette valeur côté server) !!!!!! jamais négatif !!!!!!
            int _shoot = 0; // 0 si rien 1 si quelque chose
            int _quit = 0; // 0 si rien 1 si le client veut quitter
    };

    class Frame {
        public:
            Frame() {}; // penser à remplir le constructeur si besoin
            ~Frame() {}; // penser à remplir le destructeur si besoin
            int getTick() const {return _tick;};
            bool isEndMarker(const std::vector<char>::const_iterator& it, const std::vector<char>& data) {
                const std::string endMarker = "END";
                return std::distance(it, data.end()) >= endMarker.size() &&
                std::equal(endMarker.begin(), endMarker.end(), it);
            }
            void deserializeFrame(const std::vector<char>& serializedData) {
                auto it = serializedData.begin();

                if (std::distance(it, serializedData.end()) >= sizeof(_tick)) {
                    std::memcpy(&_tick, &it, sizeof(_tick));
                    it += sizeof(_tick);
                }
                while (it < serializedData.end() && !isEndMarker(it, serializedData)) {
                    std::string entityType;
                    while (it != serializedData.end() && *it != '\0') {
                        entityType.push_back(*it);
                        ++it;
                    }
                    ++it;
                    if (entityType == "E_Player") {
                        int position_x, position_y;
                        float size_x, size_y;
                        std::memcpy(&position_x, &*it, sizeof(position_x));
                        it += sizeof(position_x);
                        std::memcpy(&position_y, &*it, sizeof(position_y));
                        it += sizeof(position_y);
                        std::memcpy(&size_x, &*it, sizeof(size_x));
                        it += sizeof(size_x);
                        std::memcpy(&size_y, &*it, sizeof(size_y));
                        it += sizeof(size_y);

                        auto player = std::make_shared<E_Player>(position_x, position_y, size_x, size_y);
                        _entities.add(player);
                    } else if (entityType == "E_Enemy") {
                        int position_x, position_y;
                        float size_x, size_y;
                        std::memcpy(&position_x, &*it, sizeof(position_x));
                        it += sizeof(position_x);
                        std::memcpy(&position_y, &*it, sizeof(position_y));
                        it += sizeof(position_y);
                        std::memcpy(&size_x, &*it, sizeof(size_x));
                        it += sizeof(size_x);
                        std::memcpy(&size_y, &*it, sizeof(size_y));
                        it += sizeof(size_y);

                        auto enemy = std::make_shared<E_Enemy>(position_x, position_y, size_x, size_y);
                        _entities.add(enemy);
                    } else if (entityType == "E_Bullet") {
                        int damage, position_x, position_y, idCreator;
                        float size_x, size_y, velocity_x, velocity_y;
                        std::memcpy(&damage, &it, sizeof(damage));
                        it += sizeof(damage);
                        std::memcpy(&position_x, &it, sizeof(position_x));
                        it += sizeof(position_x);
                        std::memcpy(&position_y, &it, sizeof(position_y));
                        it += sizeof(position_y);
                        std::memcpy(&size_x, &it, sizeof(size_x));
                        it += sizeof(size_x);
                        std::memcpy(&size_y, &it, sizeof(size_y));
                        it += sizeof(size_y);
                        std::memcpy(&velocity_x, &it, sizeof(velocity_x));
                        it += sizeof(velocity_x);
                        std::memcpy(&velocity_y, &it, sizeof(velocity_y));
                        it += sizeof(velocity_y);
                        std::memcpy(&idCreator, &it, sizeof(idCreator));
                        it += sizeof(idCreator);

                        auto bullet = std::make_shared<E_Bullet>(damage, position_x, position_y, size_x, size_y, velocity_x, velocity_y, idCreator);
                        _entities.add(bullet);
                    }
                    if (isEndMarker(it, serializedData)) {
                        break;
                    }
                }
            }
            SparseArray<IEntity> &getEntities() { return _entities; }
        private:
            int _tick = -1;
            // ici mettre les infos de la frame à display
            SparseArray<IEntity> _entities;
    };

    class Game
    {
        typedef void (Game::*functionsExecution)(int, SystemManager, SparseArray<IEntity>&);

        public:
            Game() {
                _tick = 0;
                _ennemy_sprites[1] = Infos(65.2, 66, "./assets/r-typesheet24.png");
                _player_sprites[1] = Infos(33.2, 17.2, "./assets/r-typesheet42.png");
                //faite tout ce que vous avez besoin avec la window ici
            };
            ~Game() = default;
            void run();
            std::vector<Interaction> getInteractions() {_mutex_interactions.lock();std::vector<Interaction> tmp = _interactions;_mutex_interactions.unlock();return tmp;};
            void deleteInteraction(int nbr_interaction) {_mutex_interactions.lock();_interactions.erase(_interactions.begin() + nbr_interaction);_mutex_interactions.unlock();};
            void addFrame(Frame frame) {_mutex_frames.lock();_frames.push_back(frame);_mutex_frames.unlock();};
            // à faire pour rajouter les frame à display
            // void addFrame(Frame frame) {_mutex_frame.lock();_frames.push_back(frame);_mutex_frame.unlock();};

            // il faut refaire toutes ses fonctions pour juste qu'elles récupère l'interraction et qu'elle l'envoi au serv via la class en dessous
            // pour remplir _interaction il faut lock _mutex puis l'unlock !!!!! si tu oublie l'un des 2 c'est la merde

            void actionUpCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction);
            void actionDownCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction);
            void actionLeftCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction);
            void actionRightCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction);
            void actionQuitCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction);
            void actionConnectCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction);
            void actionShootCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction);
            void actionDamageCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction);
            void actionScoreCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction);


        private:
            int _tickSpeed = TICK_SPEED;
            int _tick;
            std::mutex _mutex_interactions;
            std::vector<Interaction> _interactions;
            std::map<int, Infos> _ennemy_sprites;
            std::map<int, Infos> _player_sprites;
            // à faire pour récup les frame du jeu à display
            std::mutex _mutex_frames;
            std::vector<Frame> _frames; // ici mettre les frames à display
            void testInteraction();
    };

}