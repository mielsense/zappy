/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/components/Utils.hpp"

ImVec4
converta(int r, int g, int b, int a)
{
    // convert 0-255 to 0-1
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
