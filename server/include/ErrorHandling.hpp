/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ErrorHandling.hpp
*/

#pragma once

#include <iostream>
#include <cstring>
#include <vector>

class ErrorHandling {
    public:
        ErrorHandling() {};
        ~ErrorHandling() {};
        std::vector<int> errorHandling(int argc, char **argv);
    private:
        int checkPort(char *port);
        void help();
};