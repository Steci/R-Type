FROM alpine:3.17.0 AS builder

# Installation des dépendances
RUN apk update && apk add --no-cache sudo build-base git mesa-dev cmake curl unzip tar zip ninja libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev && rm -rf /var/cache/apk/*



# Clonage de vcpkg
WORKDIR /home
RUN git clone https://github.com/Microsoft/vcpkg.git

# Configuration de vcpkg
WORKDIR /home/vcpkg
RUN ./bootstrap-vcpkg.sh
RUN ./vcpkg integrate install

# Copie du fichier de chaîne d'outils dans le répertoire de travail
WORKDIR /engine
COPY engine /engine

# Copie du contenu de /app et vcpkg.json
WORKDIR /app
COPY server/vcpkg.json .
COPY server /app

# Création du répertoire de construction et compilation du projet
WORKDIR /app/build
RUN cmake ..
RUN cmake --build . --config Release

# CMD spécifique à votre application
CMD ["./server_build"]
