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
    std::vector<int> error = error_handling.errorHandling(argc, argv);

    if (error[0] == 84)
        return (84);
    try {
        server::Server serv(error[1], error[2]);
        return serv.run();
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
}