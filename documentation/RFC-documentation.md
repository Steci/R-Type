# R-TYPE Network

## Authors
Théo Villemer
Léa Guillemard
Guillaume Son nom de famille est casse couilles (Clement--Boniel-Veyron)
Laetitia Bousch
Malek Gatoufi

## Abstract
The goal of this documentation is to understand and be able to use the networking from our r-type project.

## Introduction
For the need of the communication of the r-type project we need a way to communicate between client and server that why we create it.

## Architecture
### 1) Client to Server
There is 2 Class send from Client to Server:
- Connection
- Interaction

Connection is used while the client isn't connected to a game and Interaction is used when he is.

#### Connection
There is 5 variables:
- int _createGame (either 0 if no and 1 if yes) used to know if the client want to create a game
- int _connected (either 0 if no and 1 if yes) variable get from the server used to know that the server have correctly connected the client
- int _JoinGame (either 0 if no and 1 if yes for sending and receive 2 if gameIds are send) used to know if the client want to get the ids of already existing games and if send with a game id (with _gameId)
- int _gameId (a number equal or greater than 0) used to know which server the client want to join, useless if _JoinGame isn't set to 1
- std::vector\<int\> _gameIds (list of numbers equal or greater than 0) variable get from the server that list all games

#### Interaction
There is 3 variables:
- int _movement (from 1 to 4) send which movement is made to the server (1 = UP, 2 = Right, 3 = Down, 4 = Left)
- int _shoot (either 0 if no and 1 if yes) used to know if the client have shoot
- int _quit (either 0 if no and 1 if yes) used to know if the client have disconnect

### 2) Server To Client
There is 2 Class send from Client to Server:
- Connection
- Frame

Connection is used while the client isn't connected to a game and Frame when he is
#### Connection
Read Connection part from the Client to server.

#### Frame
There is 2 variables:
- int _tick (a number equal or greater than 0) send the tick X to the client to know which frame is it
- SparseArray\<IEntity\> a list of every entity in the game