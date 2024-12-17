/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef EDITOR_HPP
#define EDITOR_HPP

#pragma once

#include "Log.hpp"
#include "data/Data.hpp"
#include "utils/Logger.hpp"
#include "graphical/editor/Filebrowser.hpp"
#include "graphical/entities/Player.hpp"

#include <imgui.h>
#include <iostream>

namespace zappy
{
    class Editor
    {
        private:
            ImGui::FileBrowser fileDialog;
            Log log;

        public:
            Editor()
            : log(logger.getLogLines())
            {
                fileDialog.SetTitle("Select a file");
                fileDialog.SetTypeFilters({ ".jpg", ".png" });
                fileDialog.SetCurrentDirectory("./assets/backgrounds/");
            }
            ~Editor() = default;

            // class attributes
            bool active = false;

            // class methods

            void update();
            void draw();
            void player(Player &player, bool active);
            void drawLog();

    }; // class Editor

} // zappy

// function prototypes
void HelpMarker(const char *desc);

#endif // EDITOR_HPP
