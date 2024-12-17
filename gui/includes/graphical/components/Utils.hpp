/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef UTILS_HPP
#define UTILS_HPP

#pragma once

#include <raylib-cpp.hpp>
#include <raylib.h>
#include <imgui.h>

// function prototypes

ImVec4 converta(int r, int g, int b, int a = 255);
void dottedLines(int posX, int posY, int width, int height, float thickness = 2.0f, Color color = RAYWHITE);

#endif // UTILS_HPP
