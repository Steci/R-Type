/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include "Game.hpp"

client::Game::Game()
{
    _tick = 0;
    //faite tout ce que vous avez besoin avec la window ici
}

client::Game::~Game()
{
}

void client::Game::run()
{
    while (1) {
        testInteraction();
        // _mutex_frames.lock();
        // if (_frames.size() != 0)
        //     std::cout << "frame tick : " << _frames.back().getTick() << std::endl;
        // _mutex_frames.unlock();
        //tout le bordel d'affichage + détection de touches
    }
}

void client::Game::testInteraction()
{
    Interaction inter;

    _mutex_frames.lock();
    _mutex_interactions.lock();
    if (_frames.size() != 0 && _frames.back().getTick() == 100 && _interactions.size() == 0) {
        std::cout << "test interaction" << std::endl;
        inter.setInteraction(1);
        _interactions.push_back(inter);
    }
    _mutex_interactions.unlock();
    _mutex_frames.unlock();
}