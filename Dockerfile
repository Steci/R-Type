FROM ubuntu:latest AS builder

# Mise à jour et installation des dépendances
RUN apt-get update && \
    apt-get install -y sudo build-essential git mesa-common-dev cmake curl pkg-config unzip tar zip ninja-build libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev && \
    rm -rf /var/lib/apt/lists/*

# Copie des fichiers source
WORKDIR /app
COPY . .

# Création du répertoire de construction et compilation du projet
RUN cmake ./
RUN cmake --build ./
RUN ./server