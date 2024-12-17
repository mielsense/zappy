# Zappy
A networked game platform where AI players gather resources and evolve on a tile-based world called Trantor. This project demonstrates the implementation of a game server, graphical client, and autonomous AI in a distributed system.

![Game Overview](https://github.com/user-attachments/assets/2c6c31f1-57d7-48bf-8d9e-43390b68c1b0)

## Overview
Zappy is structured in three main components:
- A server (C) that manages the game world and all game logic
- A graphical client (C++) that visualizes the game state
- AI clients (Python) that control individual players

Players must collect resources, level up through elevation rituals, and work together to become the first team to get 6 players to the maximum level.

## Screenshots

### Interactive Entity Editor
![SCR-20241217-moev](https://github.com/user-attachments/assets/ff263859-81dd-4770-8a8e-1590928f8278)

Our custom editor allows real-time interaction with the game world:
- Select and inspect any entity on the map
- Trigger and monitor broadcasts between players
- Watch and control elevation rituals
- Track resource distribution
- Monitor team progress and player status

### Game Visualization
![SCR-20240617-esyv](https://github.com/user-attachments/assets/90ddce13-cd9e-44c0-ad9d-57283f5ba8e5)
![SCR-20241217-mnzc](https://github.com/user-attachments/assets/8328a83a-501e-40ab-a8bc-beb5cd6227f8)

The isometric game world provides clear visualization of:
- Resource distribution across tiles
- Player positions and levels
- Team differentiations
- Ongoing rituals and broadcasts

## Interactive Editor Features

The Zappy GUI includes a powerful built-in editor that provides real-time control and monitoring of the game:

### Entity Selection
- Click on any entity to view its detailed information
- Track player inventory and status
- Monitor resource counts per tile
- View team affiliations and levels

### Event Monitoring
- Track and trigger broadcast messages
- Monitor elevation rituals in progress
- Watch resource spawning events
- Follow player movements and actions

### Debug Controls
- Force spawn resources
- Trigger specific game events
- Monitor server-client synchronization
- View detailed entity states

## Features

### Server
- Multi-threaded game server built in C
- Manages all game logic and world state
- Handles multiple simultaneous client connections
- Resource management and spawning system
- Implements complete game rules including elevation rituals
- Uses select() for non-blocking socket multiplexing

### Graphical Client
- Built with Raylib and ImGui
- Isometric visualization of the game world
- Real-time game state updates
- Resource and player visualization
- Team/player status tracking
- Sound system integration

### AI Client
- Written in Python
- Autonomous player control
- Resource gathering strategy
- Team coordination capabilities
- Elevation ritual management

## Building and Running

### Prerequisites
- C compiler (gcc recommended)
- C++17 compatible compiler
- Python 3.x
- CMake

### Build Instructions
```bash
# Clone the repository
git clone https://github.com/mielsense/zappy
cd zappy

# Build the server
make zappy_server

# Build the graphical client
make zappy_gui

# Build the AI client
make zappy_ai
```

### Running the Game

1. Start the server:
```bash
./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
```
Server arguments:
- `-p port`: Port number
- `-x width`: World width
- `-y height`: World height
- `-n names`: Team names
- `-c clientsNb`: Max clients per team
- `-f freq`: Time unit reciprocal

2. Start the graphical client:
```bash
./zappy_gui -p port -h machine
```
GUI arguments:
- `-p port`: Port number
- `-h machine`: Server hostname

3. Launch AI clients:
```bash
./zappy_ai -p port -n name -h machine
```
AI arguments:
- `-p port`: Port number
- `-n name`: Team name
- `-h machine`: Server hostname (default: localhost)

## Game Rules

### Resources
The game world contains various resources:
- Food (essential for survival)
- Linemate
- Deraumere
- Sibur
- Mendiane
- Phiras
- Thystame

### Elevation
Players can level up through elevation rituals which require:
- Specific numbers of players at the same level
- Specific combinations of resources
- All participating players to be on the same tile

### Vision and Communication
- Players have limited vision that increases with level
- Players can broadcast messages to communicate
- Sound propagates in specific directions

## Protocol Documentation
The server implements two separate protocols:
- AI Client Protocol: Controls player actions and game state updates
- GUI Protocol: Real-time visualization data

## Team
This project was developed by a team of 5 students (including me), I handled all the GUI part.

## License
This project is licensed under the terms of the [LICENSE](LICENSE) file included in this repository.
