# RType Project

Welcome to the RType project! This project offers a multiplayer game inspired by the classic "R-Type." Follow the instructions below to install it on Windows, macOS, and Linux.

## Installation

### Prerequisites

Before getting started, make sure you have the following tools installed on your system:

- [Git](https://git-scm.com/)
- [CMake](https://cmake.org/)

### Installation Steps

1. Clone the RType repository.

   ```bash
   git clone git@github.com:Steci/R-Type.git
   cd rtype
   ```
2. Configure the project with CMake.

   ```bash
   cmake .
   ```
3. Build the project.

   ```bash
   cmake --build .
   ```

After these steps, you will have generated three executable files: the server (`server`), the client (`client`), and the engine library (`engine`).

## Execution

### On a Local System

1. To run the server, use the following command:

   ```bash
   ./server
   ```
2. Next, launch the client in another terminal.

   ```bash
   ./client
   ```

### Using Docker

1. Ensure that Docker is installed on your machine.
2. Clone the RType project.

   ```bash
   git clone git@github.com:Steci/R-Type.git
   cd rtype
   ```
3. Start the server using Docker.

   ```bash
   docker-compose up -d --build
   ```

This will launch the server in detached mode, allowing players from around the world to connect. Enjoy the RType game!

## Contribute

We encourage any contributions to the RType project. If you want to contribute, please refer to our CONTRIBUTING.md guide.

## Releases

Check our [releases](https://github.com/Steci/R-Type/releases/tag/v1.0.0) page for the latest version of the game.

## Source Code

The source code is available on our [GitHub repository](https://github.com/Steci/R-Type/releases/tag/v1.0.0). Feel free to explore, fork, and contribute!

## Contacts

For any questions or issues, feel free to contact us:

- Email: rtype@lekmax.fr
- Discord: [Discord Server](https://discord.gg/kxKJn3zK)

## About

This RType project was carried out as part of an Epitech 3rd-year project. The development team, consisting of five students, collaborated to create this unique gaming experience.

### Development Team

- Léa GUILLEMARD lea.guillemard@epitech.eu
- Malek GATOUFI malek.gatoufi@epitech.eu
- Laetitia BOUSCH laetitia.bousch@epitech.eu
- Guillaume CLEMENT BONNIEL VEYRON guillaume.clement-bonniel-veyron@epitech.eu
- Théo VILLEMER theo.villemer@epitech.eu
