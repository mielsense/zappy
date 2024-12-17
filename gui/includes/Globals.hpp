/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#pragma once

#include <random>
#include <cstdint>
#include <raylib-cpp.hpp>

// global constants

const int FPS = 100;
const int MAP_DISPLAY_SIZE = 1000;
const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 850;
const float MOVE_SPEED = 200.0f;

// global expressions

using vec2 = Vector2;
using vec3 = Vector3;

// global functions

static inline uint64_t
generateRandomId()
{
    static std::random_device rd; // Seed for the random number engine
    static std::mt19937_64 gen(rd()); // Mersenne Twister engine
    static std::uniform_int_distribution<uint64_t> dis;

    return dis(gen);
}

#endif // GLOBALS_HPP
