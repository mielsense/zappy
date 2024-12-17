/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "core/Core.hpp"
#include "graphical/scenes/End.hpp"
#include "graphical/scenes/Menu.hpp"
#include "graphical/scenes/Scoreboard.hpp"

#include <thread>

#define USAGE "Usage: ./zappy_gui -p [port] (-h [host])"
#define TICK_INTERVAL (1.0 / DATA.timeUnit) // interval in seconds

using namespace zappy;
Data data; // global data

void
Core::init(int ac, char **av)
{
    if (ac != 3 && ac != 5) {
        ERROR(USAGE);
    }

    // port
    arguments.port = std::stoi(av[2]);
    if (std::string(av[1]) != "-p" || arguments.port <= 0) {
        ERROR(USAGE);
    }

    // host (optional)
    if (ac == 5) {
        arguments.host = av[4];
        if (std::string(av[3]) != "-h" || arguments.host.empty()) {
            ERROR(USAGE);
        }
    } else {
        arguments.host = "127.0.0.1"; // default host (localhost)
    }
}

void
Core::initScenes(raylib::Window &window)
{
    scenes[SceneType::MENU] = std::make_unique<Menu>(window);
    scenes[SceneType::WINDOW] = std::make_unique<Window>(window);
    scenes[SceneType::END] = std::make_unique<End>(window);
    scenes[SceneType::SCOREBOARD] = std::make_unique<Scoreboard>(window);
}

void
Core::run()
{
    raylib::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
    initScenes(window);

    Window &graphical = dynamic_cast<Window &>(*scenes[SceneType::WINDOW]);
    Events events(graphical.getMap(), server);

    // default data
    DATA.background.update(fmt::format("{}backgrounds/night.png", ASSETS));


    // init the server
    // then wait for the two first packets (confirmation messages)
    // + get the map size and content
    server.init(arguments.port, arguments.host);
    while (!server.isWelcome()) {
        server.update();
    }

    server.get(PacketType::MAP_SIZE);
    server.get(PacketType::MAP_CONTENT);
    server.get(PacketType::TIME_UNIT_REQUEST);
    server.get(PacketType::TEAM_NAMES);
    events.handler();

    // init tick time
    using clock = std::chrono::high_resolution_clock;
    auto startTime = clock::now();

    // main loop
    while (!window.ShouldClose()) {
        auto now = clock::now();
        currentTime = ts(now - startTime);

        // handle logic that runs every tick
        if (currentTime - lastTickTime >= TICK_INTERVAL) {
            update();         // ask the server for new data
            server.update();  // update server data (get packets sent by the server)
            events.handler(); // handle events

            lastTickTime = currentTime;
        }

        scenes[DATA.currentScene]->handler();
    }
}

// ask the server for new data every server tick
void
Core::update()
{
    // player info
    if (!DATA.players.empty()) {

        // for every player in the game
        // request their position, level and inventory
        for (auto &player : DATA.players) {
            std::string options = fmt::format("#{}", player.id);
            server.get(PacketType::PLAYER_POSITION, false, options);
            server.get(PacketType::PLAYER_LEVEL, false, options);
            server.get(PacketType::PLAYER_INVENTORY, false, options);
        }
    }
}
