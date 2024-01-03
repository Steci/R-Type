FROM ubuntu:latest AS builder

# Mise à jour et installation des dépendances
RUN apt-get update && \
    apt-get install -y sudo build-essential git mesa-common-dev cmake curl pkg-config unzip tar zip ninja-build libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev && \
    rm -rf /var/lib/apt/lists/*

# Clonage de vcpkg
WORKDIR /home
RUN git clone https://github.com/Microsoft/vcpkg.git

# Configuration de vcpkg
WORKDIR /home/vcpkg
RUN ./bootstrap-vcpkg.sh
RUN ./vcpkg integrate install --triplet x64-linux

# Copie des fichiers source
WORKDIR /app
COPY . .

# Mise à jour du chemin pour inclure cmake avant chaque commande nécessitant cmake

# Installation des dépendances avec vcpkg
WORKDIR /app/server/
RUN /home/vcpkg/vcpkg install --feature-flags=manifests,codespeed --overlay-triplets=/home/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake

WORKDIR /app/
RUN /home/vcpkg/vcpkg install --feature-flags=manifests,codespeed --overlay-triplets=/home/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake
WORKDIR /app/

# --feature-flags=manifests,codespeed --overlay-triplets=/home/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake

# Création du répertoire de construction et compilation du projet
RUN cmake ./
RUN cmake --build ./
RUN ./server_build

# Copie des fichiers de sortie dans le répertoire de travail
#WORKDIR /app
#RUN cp /app/build/server_build /app/server_build

# CMD spécifique à votre application
# CMD ["./makebuild.sh"]
