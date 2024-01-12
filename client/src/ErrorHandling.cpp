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
    std::string serverPort = "";
    std::string serverIP = "";

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
            help();
            return {"0", serverIP, serverPort};
        } else if (std::strcmp(argv[i], "-i") == 0 || std::strcmp(argv[i], "--ip") == 0) {
            if (i + 1 < argc) {
                if (checkIP(argv[i + 1]) == 84) {
                    std::cerr << "Invalid IP" << std::endl;
                    return {"84", serverIP, serverPort};
                }
                serverIP = argv[i + 1];
                ++i;
            } else {
                std::cerr << "Invalid IP" << std::endl;
                return {"84", serverIP, serverPort};
            }
        } else if (std::strcmp(argv[i], "-p") == 0 || std::strcmp(argv[i], "--port") == 0) {
            if (i + 1 < argc) {
                if (checkPort(argv[i + 1]) == 84) {
                    std::cerr << "Invalid port" << std::endl;
                    return {"84", serverIP, serverPort};
                }
                serverPort = argv[i + 1];
                ++i;
            } else {
                std::cerr << "Invalid port" << std::endl;
                return {"84", serverIP, serverPort};
            }
        } else {
            std::cerr << "Invalid argument" << std::endl;
            return {"84", serverIP, serverPort};
        }
    }
    return {"0", serverIP, serverPort};
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

int ErrorHandling::checkIP(char *serverIP)
{
    int i = 0;

    while (serverIP[i] != '\0') {
        if ((serverIP[i] < '0' || serverIP[i] > '9') && serverIP[i] != '.')
            return 84;
        i++;
    }
    return 0;
}
