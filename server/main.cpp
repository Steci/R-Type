/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** main.cpp
*/

#include "ErrorHandling.hpp"
#include "Server.hpp"

int main(int argc, char **argv)
{
    ErrorHandling error_handling;

    try {
        server::Server serv(9001, 4);

        if (error_handling.errorHandling(argc, argv) == 84)
            return (84);
        return serv.run();
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
}
