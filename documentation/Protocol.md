# <center>Network Communication</center>

<center><span style="color:rgb(102,178,255)">Blue Commands are server commands.</span></center>

<center><span style="color:rgb(255,128,0)">Orange Commands are client commands (thanks lua).</span></center>

The server tickrate is the frequency at which the server processes and updates game events. This includes player movements, physics calculations, AI updates, and other gameplay mechanics.

Default Server Port : 9001


<U>TEMPLATE FOR ADDING COMMANDS TO THE DOCUMENTATION:</U>
- <span style="color:rgb(102,178,255)">**COMMAND**</span> <span style="color:rgb(255,128,0)">**NAME**</span> [PARAMETERS] (OPTIONAL PARAMETERS)
- Command Description
- (IF PRESENT) : Command Response

# <center>Network Communication</center>

## <center><span style="color:rgb(102,178,255)">**SERVER COMMANDS**</span></center>

- <span style="color:rgb(102,178,255)">**kill**</span>
  - Kills the server and disconnects all the clients. Only the admin can do that.

- <span style="color:rgb(102,178,255)">**kick**</span> **[client id] (message)**
  - Kicks the specified client of the server.

- <span style="color:rgb(102,178,255)">**set_tickrate**</span> **[new tickrate]**
  - Sets the tickrate of the server (66 by default). Only the admin can do that.
  - Send new tickrate to client.

- <span style="color:rgb(102,178,255)">**update**</span> **[id entity] [type info]**
  - Send new game information.

- <span style="color:rgb(102,178,255)">**error**</span> **[error info]**
  - Send error.


## <center><span style="color:rgb(255,128,0)">**CLIENT COMMANDS**</span></center>

- <span style="color:rgb(255,128,0)">**connect**</span> **[server ip] (server port)**
  - Connects the client to the specified server ip. By default, the port is set to 9001 but can be passed as an optional argument by the client.
    - Server returns the id of the client when successfully connected.
    - Server returns a message if the connection has been refused for some reason.


- <span style="color:rgb(255,128,0)">**disconnect**</span>
  - Disconnect the client from the current server.

- <span style="color:rgb(255,128,0)">**ping**</span>
  - Ask the current server the user’s ping.
    - Response : The user’s ping.


- <span style="color:rgb(255,128,0)">**input**</span> **[touch]**
  - Ask for the permission to do that touch.
  - Don’t wait for the server answer and do it anyway, if not allow rollback.

