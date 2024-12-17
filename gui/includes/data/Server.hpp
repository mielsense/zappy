/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>

#include "utils/Logger.hpp"
#include "data/Data.hpp"

// globals

#define MAX_MESSAGE 64000

#pragma once

namespace zappy
{
    class Server
    {
        private:
            int sock;
            sockaddr_in server;
            std::string temporary; // used to build the message (in case segmented messages are received)

        public:
            Server() = default;
            ~Server() { close(sock); };

            // class methods

            void init(int port, std::string host);
            void update();
            void builder(std::string message);

            inline Packet
            get(const PacketType &type, bool wait = false, std::string options = "")
            {
                if (DATA.history.empty()) {
                    LOG("No history found, server is not yet ready", W);
                    return { PacketType::UNKNOWN_COMMAND, "no data" };
                }

                // send to the server
                std::string message = fmt::format("{}{}", convert(type), options != "" ? " " + options + "\n" : "\n");
                send(sock, message.c_str(), strlen(message.c_str()), 0);

                if (type != PacketType::PLAYER_POSITION && type != PacketType::PLAYER_LEVEL && type != PacketType::PLAYER_INVENTORY) {
                    if (!message.empty() && message.back() == '\n') {
                        message.pop_back();
                    }
                    LOG("Sent message to server : " + message, I);
                }

                // get the server response
                if (wait) {
                    while(DATA.current.back().type != type) {
                        update();
                    }

                    return DATA.current.back();
                }

                return { PacketType::UNKNOWN_COMMAND, "no data" };
            }

            // TODO : get rid of this is this will not be present in "serveur de référence"
            inline bool
            isWelcome()
            {
                if (temporary.find("WELCOME") != std::string::npos) {

                    Packet packet(PacketType::UNKNOWN_COMMAND, temporary);
                    DATA.current.push(packet);
                    DATA.history.push_back(packet);

                    LOG("Received message from server : " + temporary, I);
                    temporary = "";

                    return true;
                }

                return false;
            }

    }; // class Server
} // zappy

#endif // SERVER_HPP
