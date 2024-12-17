/*
** EPITECH PROJECT, 2024
** gui
** File description:
** vim on top !
*/

#include "core/Core.hpp"
#include "utils/Error.hpp"
#include "utils/Logger.hpp"

#include <iostream>

using namespace zappy;
Logger logger; // global logger

int
main(int ac, char **av)
{
    Core core;
    LOG("Application started !");

    try {
        core.init(ac, av);
        core.run();
    } catch (const Error &e) {
        std::cerr << e.what() << std::endl;
        LOG(e.what(), E);
        return FAILURE;
    } catch (...) {
        std::cerr << "An unexpected error occured !" << std::endl;
        LOG("An unexpected error occured !", E);
        return FAILURE;
    }

    LOG("Application ended !");
    return SUCCESS;
}
