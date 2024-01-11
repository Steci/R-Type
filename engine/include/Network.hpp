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
        virtual bool isEndMarker(const std::vector<char>::const_iterator& it,
        const std::vector<char>& data) = 0;
        virtual bool operator==(const IFrame& other) const = 0;
        virtual bool operator!=(const IFrame& other) const = 0;
        // Frame& operator=(const Frame& other);
        virtual int getTick() const = 0;
        virtual void setArray(SparseArray<IEntity> entities) = 0;
        virtual SparseArray<IEntity> &getEntities() = 0;
};

class AFrame : public IFrame {
    public:
        AFrame() = default;
        ~AFrame() = default;
        void setTick(int tick) override {_tick = tick;};
        bool isEndMarker(const std::vector<char>::const_iterator& it,
        const std::vector<char>& data) override {
            const std::string endMarker = "END";
            return std::distance(it, data.end()) >= endMarker.size() &&
            std::equal(endMarker.begin(), endMarker.end(), it);
        }
        bool operator==(const IFrame& other) const override
        {return *this == other;};
        bool operator!=(const IFrame& other) const override
        {return !(*this == other);};
        // Frame& operator=(const Frame& other);
        int getTick() const override {return _tick;};
        void setArray(SparseArray<IEntity> entities) override
        {_entities = entities;};
        Sparse      Array<IEntity> &getEntities() override {return _entities;};
    protected:
        int _tick;
        // ici mettre les infos de la frame à display
        SparseArray<IEntity> _entities;
};