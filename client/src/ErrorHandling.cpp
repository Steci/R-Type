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

std::vector<std::string> ErrorHandling::errorHandling(int argc, char **argv)
{
    std::string port = "";
    std::string ipServer = "";

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
            help();
            exit(0);
        } else if (std::strcmp(argv[i], "-i") == 0 || std::strcmp(argv[i], "--ip") == 0) {
            if (i + 1 < argc) {
                if (checkIp(argv[i + 1]) == 84) {
                    std::cerr << "Invalid IP" << std::endl;
                    return {"84", ipServer, port};
                }
                ipServer = argv[i + 1];
                ++i;
            } else {
                std::cerr << "Invalid IP" << std::endl;
                return {"84", ipServer, port};
            }
        } else if (std::strcmp(argv[i], "-p") == 0 || std::strcmp(argv[i], "--port") == 0) {
            if (i + 1 < argc) {
                if (checkPort(argv[i + 1]) == 84) {
                    std::cerr << "Invalid port" << std::endl;
                    return {"84", ipServer, port};
                }
                port = argv[i + 1];
                ++i;
            } else {
                std::cerr << "Invalid port" << std::endl;
                return {"84", ipServer, port};
            }
        } else {
            std::cerr << "Invalid argument" << std::endl;
            return {"84", ipServer, port};
        }
    }
    return {"0", ipServer, port};
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

int ErrorHandling::checkIp(char *ip)
{
    int i = 0;

    while (ip[i] != '\0') {
        if ((ip[i] < '0' || ip[i] > '9') && ip[i] != '.')
            return 84;
        i++;
    }
    return 0;
}
