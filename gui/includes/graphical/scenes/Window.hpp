/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#pragma once

#include "data/Data.hpp"
#include "graphical/Scene.hpp"
#include "graphical/components/Utils.hpp"
#include "graphical/editor/Editor.hpp"
#include "graphical/entities/Egg.hpp"
#include "graphical/entities/Player.hpp"
#include "graphical/entities/Ressource.hpp"

#include "imgui.h"
#include "raylib-cpp.hpp"
#include "rlImGui.h"

namespace zappy
{

    class Window : public Scene
    {
        private:
            // camera setup
            raylib::Camera2D camera; // Camera for zooming
            float zoomLevel = 1.0f;         // Zoom level
            vec2 prevMousePosition; // Previous mouse position for panning
            bool isPanning = false;            // Whether panning is active

            Editor editor;
            Map map;

            raylib::Shader shader;
            raylib::RenderTexture2D target;

        public:
            Window(raylib::Window &window)
            : Scene(window), camera({0}), map(DATA.mapSize.x, DATA.mapSize.y), shader(0, fmt::format("{0}shaders/pixelizer.fs", ASSETS).c_str())
            {
                // raylib setup
                SetTargetFPS(FPS);
                DATA.fps = FPS;
                target = LoadRenderTexture(window.GetRenderWidth(), window.GetRenderHeight());

                camera.target = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
                camera.offset = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
                camera.rotation = 0.0f;

                zoomLevel = zoomLevel * (DATA.mapSize.x / 10);
                camera.zoom = zoomLevel;

                // imgui setup
                rlImGuiSetup(true);
                ImGuiIO &io = ImGui::GetIO();
                io.FontGlobalScale = 1.5f;

                ImGuiStyle& style = ImGui::GetStyle();

                style.Colors[ImGuiCol_TitleBgActive] = converta(255, 150, 237, 126);
                style.Colors[ImGuiCol_WindowBg] = converta(0, 0, 0, 160);
                style.Colors[ImGuiCol_Text] = converta(243, 226, 240);

                style.Colors[ImGuiCol_FrameBg] = converta(238, 171, 237, 138);
                style.Colors[ImGuiCol_FrameBgActive] = converta(198, 121, 220, 102);
                style.Colors[ImGuiCol_FrameBgHovered] = converta(198, 121, 220, 102);

                style.Colors[ImGuiCol_Button] = converta(238, 171, 237, 138);
                style.Colors[ImGuiCol_ButtonActive] = converta(198, 121, 220, 102);
                style.Colors[ImGuiCol_ButtonHovered] = converta(198, 121, 220, 102);

                style.Colors[ImGuiCol_SliderGrab] = converta(198, 121, 220, 102);
                style.Colors[ImGuiCol_SliderGrabActive] = converta(198, 121, 220, 102);

                style.Colors[ImGuiCol_Header] = converta(198, 121, 220, 102);
                style.Colors[ImGuiCol_HeaderActive] = converta(198, 121, 220, 102);
                style.Colors[ImGuiCol_HeaderHovered] = converta(238, 171, 237, 138);
            };
            ~Window() { rlImGuiShutdown(); };

            // class methods

            void handler() override;
            void update(float deltaTime) override;
            void updateCamera();
            void draw(float totalTime) override;
            void events();

            // drawing methods

            void overlay();

            // getters

            Map &getMap() { return map; };

    }; // class Window

} // zappy

#endif // WINDOW_HPP
