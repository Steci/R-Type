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

/**
 * @brief ErrorHandling class
 * 
 */
class ErrorHandling {
    public:
        /**
         * @brief Construct a new Error Handling object
         * 
         */
        ErrorHandling() {};

        /**
         * @brief Destroy the Error Handling object
         * 
         */
        ~ErrorHandling() {};

        /**
         * @brief error handling for the server
         * 
         * @param argc is the number of arguments
         * @param argv is the arguments
         * @return std::vector<int> is the vector of the port and the max clients
         */
        std::vector<int> errorHandling(int argc, char **argv);
    private:
        /**
         * @brief check if the port is a number
         * 
         * @param port is the port
         * @return int is the port
         */
        int checkPort(char *port);

        /**
         * @brief check if the max clients is a number
         * 
         */
        void help();
};
