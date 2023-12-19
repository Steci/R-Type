/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include "Network.hpp"

bool server::Client::operator==(const Client& other) const
{
    return _id == other.getId() && _name == other.getName();
}

server::Client& server::Client::operator=(const Client& other)
{
    _addr = other.getAddr();
    _id = other.getId();
    return *this;
}