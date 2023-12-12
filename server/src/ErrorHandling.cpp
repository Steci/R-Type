/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** errorHandling.cpp
*/

#include "ErrorHandling.hpp"
#include <iostream>
#include <vector>

void ErrorHandling::help()
{
    std::cout << "USAGE: ./r-type_server [OPTIONS]" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "\t-h, --help\t\t\tDisplay this help message" << std::endl;
    std::cout << "\t-p, --port=PORT\t\t\tSet the port of the server" << std::endl;
}

int ErrorHandling::errorHandling(int argc, char **argv)
{
    if (checkFlags(argc, argv) == 84)
        return 84;
    return 0;
}

int ErrorHandling::checkFlags(int argc, char **argv)
{
    std::vector<std::string> flags = {"-p", "--port", "-h", "--help"};
    bool checked = false;


    for (int i = 1; i < argc; ++i) {
        checked = false;
        for (auto flag = flags.begin(); flag != flags.end(); flag++) {
            if (argv[i] == *flag) {
                if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
                    help();
                    exit(0);
                }
                checked = true;
                ++i;
                break;
            }
        }
        if (!checked) {
            std::cerr << "Invalid flag: " << argv[i] << std::endl;
            help();
            return 84;
        }
    }
    return 0;
}

int ErrorHandling::checkPort(char *port)
{
    int i = 0;

    while (port[i] != '\0') {
        if (port[i] < '0' || port[i] > '9')
            return 84;
        i++;
    }
    return 0;
}
