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
        std::vector<std::string> errorHandling(int argc, char **argv);
    private:
        int checkPort(char *serverPort);
        int checkIP(char *serverIP);
        void help();
};
