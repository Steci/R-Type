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
         * @brief Check the port
         * 
         * @param serverPort is the port to check
         * @return int is the port checked
         */
        std::vector<std::string> errorHandling(int argc, char **argv);
    private:
        /**
         * @brief Check the port
         * 
         * @param serverPort is the port to check
         * @return int is the port checked
         */
        int checkPort(char *serverPort);

        /**
         * @brief Check the IP
         * 
         * @param serverIP is the IP to check
         * @return int is the IP checked
         */
        int checkIP(char *serverIP);

        /**
         * @brief Display the help
         * 
         */
        void help();
};
