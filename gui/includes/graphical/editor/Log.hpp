/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef LOG_HPP
#define LOG_HPP

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cstring>

namespace zappy
{
    class Log
    {
        public:
            std::vector<std::string>& logLines;
            bool autoScroll = true;
            char searchBuffer[128] = "";

            bool active = false;

        public:
            Log(std::vector<std::string>& logLines) : logLines(logLines) {}
            ~Log() = default;

            void reset()
            {
                memset(searchBuffer, 0, sizeof(searchBuffer));
            }
    }; // class Log
} // namespace zappy


#endif // LOG_HPP
