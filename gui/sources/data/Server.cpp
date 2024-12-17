/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "data/Server.hpp"
#include <sstream>

using namespace zappy;

void
Server::init(int port, std::string host)
{
    // create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        ERROR("Socket creation failed");
    }

    // set the server address
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, host.c_str(), &server.sin_addr) <= 0) {
        close(sock);
        ERROR("Invalid server address/ Address not supported");
    }

    // connect to the server
    if (connect(sock, (sockaddr *)&server, sizeof(server)) < 0) {
        close(sock);
        ERROR("Connection with server Failed");
    }

    // set the socket to non-blocking
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    // declare the server as a graphic client
    std::string message = "GRAPHIC\n";
    send(sock, message.c_str(), strlen(message.c_str()), 0);
}

void
Server::update()
{
    int received;
    char buffer[MAX_MESSAGE] = { 0 };

    // get the server response
    received = recv(sock, buffer, MAX_MESSAGE, 0);
    if (received <= 0 && temporary == "") {
        return;
    }
    buffer[received] = '\0';

    // verify the data
    builder(std::string(buffer));
}

void
Server::builder(std::string message)
{
    std::istringstream content(message);
    std::string line;

    // if server has not sent a message after the last update (and temporary is not empty)
    // then last message is complete
    if (message.empty()) {
        std::string content;
        PacketType type = convert(temporary, content);
        Packet packet(type, content);

        LOG("Received message from server : " + content);
        temporary = "";

        DATA.current.push(packet);
        DATA.history.push_back(packet);

        return;
    }

    // if the message is a new packet then pack the current buffer (temporary) into a Packet
    while (std::getline(content, line)) {
        if (hasPacket(line) && !isWelcome()) {
            std::string content;
            PacketType type = convert(temporary, content);
            Packet packet(type, content);

            // if the message is needed then log it
            if (type != PacketType::PLAYER_POSITION && type != PacketType::PLAYER_LEVEL && type != PacketType::PLAYER_INVENTORY) {
                LOG("Received message from server : " + content);
            } else {
                std::string latestPacketData;

                for (auto it = DATA.history.rbegin(); it != DATA.history.rend(); ++it) {
                    if (it->type == type) {
                        latestPacketData = it->data;
                        break;
                    }
                }

                if (latestPacketData != content) {
                    LOG("Received message from server : " + content);
                }
            }

            DATA.current.push(packet);
            DATA.history.push_back(packet);
            temporary = "";
        }
        temporary += line;
    }
}
