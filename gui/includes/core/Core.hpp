/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef CORE_HPP
#define CORE_HPP

#pragma once

#include "Events.hpp"
#include "data/Server.hpp"
#include "graphical/scenes/Window.hpp"

#include <vector>
#include <memory>
#include <chrono>
#include <map>

// global constants

#define TITLE "zappy"

namespace zappy
{

    struct Arguments
    {
        int port;
        std::string host;
    };

    class Core
    {
        private:
            Server server; // server data (calls to server)
            Arguments arguments; // command line arguments

            // graphical
            std::map<SceneType, std::unique_ptr<Scene>> scenes; // scenes

            // server communication
            double lastTickTime = 0; // to keep track of the last tick time
            double currentTime = 0; // current time in seconds

        public:
            Core() = default;
            ~Core() = default;

            // class methods

            void init(int ac, char **av);
            void initScenes(raylib::Window &window);
            void run();
            void update();

    }; // class Core

    // helper functions
    inline double
    ts(const std::chrono::duration<double>& duration)
    {
        return duration.count();
    }

} // namespace zappy

#endif // CORE_HPP
