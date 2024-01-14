/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Network.hpp
*/

#pragma once

#include <iostream>
#include <vector>
#include "Engine.hpp"

class IFrame {
    public:
        virtual void setTick(int tick) = 0;
        virtual void setGameId(int gameId) = 0;
        virtual void setArray(SparseArray<IEntity> entities) = 0;
        virtual bool isEndMarker(const std::vector<char>::const_iterator& it, const std::vector<char>& data) = 0;
        virtual bool operator==(const IFrame& other) const = 0;
        virtual bool operator!=(const IFrame& other) const = 0;
        // Frame& operator=(const Frame& other);
        virtual int getTick() const = 0;
        virtual SparseArray<IEntity> &getEntities() = 0;
};

class AFrame : public IFrame {
    public:
        AFrame() = default;
        ~AFrame() = default;
        void setTick(int tick) override {_tick = tick;};
        void setGameId(int gameId) override {_gameId = gameId;};
        bool isEndMarker(const std::vector<char>::const_iterator& it, const std::vector<char>& data) override {
            const std::string endMarker = "END";
            return std::distance(it, data.end()) >= endMarker.size() &&
            std::equal(endMarker.begin(), endMarker.end(), it);
        }
        bool operator==(const IFrame& other) const override {return *this == other;};
        bool operator!=(const IFrame& other) const override {return !(*this == other);};
        // Frame& operator=(const Frame& other);
        int getTick() const override {return _tick;};
        void setArray(SparseArray<IEntity> entities) override {_entities = entities;};
        SparseArray<IEntity> &getEntities() override {return _entities;};
    protected:
        int _tick;
        int _gameId;
        // ici mettre les infos de la frame à display
        SparseArray<IEntity> _entities;
};

class IInteraction {
    public:
        virtual void setInteraction(int mov, int shoot, int quit, int createGame) = 0;
        virtual int getMovement() const = 0;
        virtual int getShoot() const = 0;
        virtual int getQuit() const = 0;
        virtual int getCreateGame() const = 0;
};

class AInteraction : public IInteraction{
    public:
        AInteraction() = default;
        ~AInteraction() = default;
        void setInteraction(int mov, int shoot, int quit, int createGame) override {
            _movement = mov;
            _shoot = shoot;
            _quit = quit;
            _createGame = createGame;
        };
        int getMovement() const override {return _movement;};
        int getShoot() const override {return _shoot;};
        int getQuit() const override {return _quit;};
        int getCreateGame() const override {return _createGame;};
    protected:
        int _movement = 0;
        int _shoot = 0;
        int _quit = 0;
        int _createGame = 0;
};

class IProtocole {
    public:
        virtual void deserializeProtocole(const std::vector<char>& serializedData) = 0;
        virtual std::vector<char> serializeProtocole() = 0;
};

class AProtocole : public IProtocole{
    public:
        AProtocole() = default;
        ~AProtocole() = default;
        void setPing(int ping) {_ping = ping;};
        void setPong(int pong) {_pong = pong;};
        int getPing() const {return _ping;};
        int getPong() const {return _pong;};
        void deserializeProtocole(const std::vector<char>& serializedData) override {
            *this = *reinterpret_cast<const AProtocole*>(serializedData.data());
        }
        std::vector<char> serializeProtocole() override {
            const char* data = reinterpret_cast<const char*>(this);
            return std::vector<char>(data, data + sizeof(AProtocole));
        }
    protected:
        int _ping = 0;
        int _pong = 0;
};

class IConnection {
    public:
        virtual int getConnect() const = 0;
        virtual int getConnected() const = 0;
        virtual int getCreateGame() const = 0;
        virtual void setCreateGame(int createGame) = 0;
        virtual void setConnected(int connected) = 0;
        virtual int getId() const = 0;
        virtual void setId(int id) = 0;
        virtual void setJoinGame(int joinGame) = 0;
        virtual int getJoinGame() const = 0;
        virtual void setGameId(int gameId) = 0;
        virtual int getGameId() const = 0;
        virtual void setGameIds(std::vector<int> gameIds) = 0;
        virtual std::vector<int> getGameIds() const = 0;
        virtual std::vector<char> serializeConnection() = 0;
        virtual void deserializeConnection(std::vector<char> data) = 0;
};

class AConnection : public IConnection {
    public:
        AConnection() = default;
        ~AConnection() = default;
        int getConnect() const override {return _connect;};
        int getConnected() const override {return _connected;};
        int getCreateGame() const override {return _createGame;};
        void setCreateGame(int createGame) override {_createGame = createGame;};
        void setConnected(int connected) override {_connected = connected;};
        void setId(int id) override {_id = id;};
        int getId() const override {return _id;};
        void setJoinGame(int joinGame) override {_JoinGame = joinGame;};
        int getJoinGame() const override {return _JoinGame;};
        void setGameId(int gameId) override {_gameId = gameId;};
        int getGameId() const override {return _gameId;};
        void setGameIds(std::vector<int> gameIds) override {_gameIds = gameIds;};
        std::vector<int> getGameIds() const override {return _gameIds;};
        std::vector<char> serializeConnection() override;
        void deserializeConnection(std::vector<char> data) override;
    protected:
        int _createGame;
        int _connect;
        int _connected;
        int _JoinGame;
        int _id;
        int _gameId;
        std::vector<int> _gameIds;
};
