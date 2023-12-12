/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ErrorHandling.hpp
*/

#pragma once

#include <iostream>
#include <cstring>

class ErrorHandling {
    public:
        ErrorHandling() {};
        ~ErrorHandling() {};
        int errorHandling(int argc, char **argv);
    private:
        int checkFlags(int argc, char **argv);
        int checkPort(char *port);
        void help();
};