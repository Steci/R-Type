/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main.cpp
*/

#include "ErrorHandling.hpp"
#include "Client.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    ErrorHandling error_handling;

    try {
        client::Client client("127.0.0.1", 9002);

        if (error_handling.errorHandling(argc, argv) == 84)
            return (84);
        return client.run();
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
}

// TODO: Params for the client binary:
//          - -p --port
//          - -i --ip


// TODO: Network class:
//         - Network run
//         - fillSocket
//         - fillAddr
//         - bindSocket
