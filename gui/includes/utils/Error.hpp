/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef ERROR_HPP
#define ERROR_HPP

#pragma once

#include <iostream>

#define ERROR(message) throw zappy::Error(message)
#define FAILURE 84
#define SUCCESS 0

namespace zappy
{
    class Error : public std::exception
    {
        private:
            std::string message;

        public:
            explicit Error(const std::string &message = "Unknown error!") : message("\033[1;31m[error] : \033[0m" + message + "!") {}
            ~Error() = default;

            // class methods

            const char *what() const noexcept override{ return message.c_str(); }
    }; // class Error
} // namespace zappy

#endif // ERROR_HPP
