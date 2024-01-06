/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ErrorHandling.hpp
*/

#pragma once

#include <cstring>
#include <string>
#include <vector>

class ErrorHandling {
    public:
        ErrorHandling() {};
        ~ErrorHandling() {};
        std::vector<std::string> errorHandling(int argc, const char **argv);
    private:
        int checkPort(const char *serverPort);
        int checkIP(const char *serverIP);
        void help();
};
