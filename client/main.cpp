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
    std::vector<std::string> error = error_handling.errorHandling(argc, argv);

    if (error[0] == "84")
        return (84);
    try {
        client::Client client(error[1], std::atoi(error[2].c_str()));
        return client.run();
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
}
