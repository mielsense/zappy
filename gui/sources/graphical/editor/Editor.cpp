/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/editor/Editor.hpp"
#include "utils/Logger.hpp"

#include <chrono>

using namespace zappy;

void
Editor::update()
{
    ImGuiWindowFlags window_flags = 0;

    // start editor
    if (!ImGui::Begin("Editor", &active, window_flags)) {
        ImGui::End();
        return;
    }

    draw();
    if (DATA.examinePlayerId != 0) {
        uint64_t target = DATA.examinePlayerId;
        bool active = true;

        auto it = std::find_if(
            DATA.players.begin(), DATA.players.end(), [target](const Player &player) { return player.id == target; });

        if (it != DATA.players.end()) {
            player(*it, active);
        }
    }

    ImGui::End(); // end editor
}

void
Editor::draw()
{
    // general info
    ImGui::SetWindowFontScale(1.1f);
    ImGui::Text("General info");
    ImGui::SetWindowFontScale(1);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15.0f);

    ImGui::Text("%d fps", GetFPS());
    ImGui::SameLine();
    HelpMarker("Display the current frame rate.");

    ImGui::Text("%f ms", GetFrameTime());
    ImGui::SameLine();
    HelpMarker("Display the time it took to render the last frame.");

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
    ImGui::Separator();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

    // ame settings
    ImGui::SetWindowFontScale(1.1f);
    ImGui::Text("Game settings");
    ImGui::SetWindowFontScale(1);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15.0f);

    ImGui::Text("Players: %lu", DATA.players.size());

    if (ImGui::BeginTable("Players", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Coordinates");
        ImGui::TableHeadersRow();

        for (auto const &player : DATA.players) {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%llu", player.id);

            if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                DATA.examinePlayerId = player.id;
            }

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("{ %.1f, %.1f }", player.coordinates.x, player.coordinates.y);

            if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                DATA.examinePlayerId = player.id;
            }
        }

        ImGui::EndTable();
    }

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
    ImGui::Separator();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

    // graphics settings
    ImGui::SetWindowFontScale(1.1f);
    ImGui::Text("Graphics settings");
    ImGui::SetWindowFontScale(1);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15.0f);

    ImGui::Text("Map size");

    ImGui::InputFloat("x", &DATA.mapSize.x);
    ImGui::SameLine();
    ImGui::InputFloat("y", &DATA.mapSize.y);

    if (ImGui::SliderInt("Max FPS", &DATA.fps, 1, 240)) {
        SetTargetFPS(DATA.fps);
    }
    ImGui::SameLine();
    HelpMarker("CTRL+click to input value.");

    if (ImGui::Button("Change the background"))
        fileDialog.Open();
    ImGui::SameLine();
    HelpMarker("Opens a file dialog to change the background.");

    fileDialog.Display();
    if (fileDialog.HasSelected()) {
        DATA.background.update(fileDialog.GetSelected().string());
        fileDialog.ClearSelected();
    }

    // log
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
    if (ImGui::Button("Show logs")) {
        log.active = !log.active;
    }

    if (log.active) {
        drawLog();
    }
}

void
Editor::player(Player &player, bool active)
{
    ImGui::Begin(fmt::format("Player {}", player.id).c_str(), &active);

    ImGui::Text("id: %llu", player.id);
    ImGui::Text("team: %s", player.team.c_str());
    ImGui::Text("level: %d", player.level);

    ImGui::Separator();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

    ImGui::Text("position: (%.1f, %.1f)", player.position.x, player.position.y);
    ImGui::Text("coordinates: (%.1f, %.1f)", player.coordinates.x, player.coordinates.y);

    // set position
    {
        ImGui::Text("Set position");
        ImGui::SameLine();
        HelpMarker("Set the entities position by entering the coordinates.");

        static int x = 0;
        static int y = 0;

        ImGui::InputInt("x", &x);
        ImGui::InputInt("y", &y);
        if (ImGui::Button("Set")) {
            if (x < 0 || x >= DATA.mapSize.x || y < 0 || y >= DATA.mapSize.y) {
                LOG(fmt::format("Invalid set coordinates [{0},{1}] for player {2}", x, y, player.id), E);
                x = 0;
                y = 0;
                return;
            }

            player.walk({ static_cast<float>(x), static_cast<float>(y) });
            LOG(fmt::format("Set coordinates [{0},{1}] for player {2}", x, y, player.id), I);
            x = 0;
            y = 0;
        }
    }

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
    ImGui::Separator();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

    ImGui::Text("Inventory");
    if (ImGui::BeginTable("Inventory", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("Item");
        ImGui::TableSetupColumn("Quantity");
        ImGui::TableHeadersRow();

        for (auto const &ressource : player.inventory.count) {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", getRessourceTypeString(ressource.first).c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", ressource.second);
        }
        ImGui::EndTable();
    }

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
    ImGui::Separator();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

    ImGui::SliderFloat("speed", &player.speed, 100.0f, 500.0f);
    ImGui::SameLine();
    HelpMarker("CTRL+click to input value.");

    if (ImGui::Button("Start incantation")) {
        player.startIncantation();
    }
    ImGui::SameLine();
    HelpMarker("Start the incantation animation.");

    if (ImGui::Button("Stop incantation")) {
        std::string result = "OK";
        player.stopIncantation(result);
    }
    ImGui::SameLine();
    HelpMarker("Stop the incantation animation.");

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
    ImGui::Separator();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

    if (ImGui::Button("Test Broadcast")) {
        player.broadcast.active = true;
        player.broadcast.message = "Hello World !";
        player.broadcast.start = std::chrono::system_clock::now();
    }
    ImGui::SameLine();
    HelpMarker("Broadcast a message.");

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
    ImGui::Separator();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

    if (ImGui::Button("Delete")) {
        uint64_t target = player.id;
        auto it = std::find_if(DATA.players.begin(), DATA.players.end(), [target](const Player &player) {
            return player.id == target;
        });
        DATA.players.erase(it);
        LOG(fmt::format("Deleted player {0}", target), W);
    }
    ImGui::SameLine();
    HelpMarker("Delete the entities.");

    ImGui::End();

    if (!active) {
        DATA.examinePlayerId = 0;
    }
}

void
Editor::drawLog()
{
    ImGui::Begin("Logs", &log.active);

    ImGui::Text("Logs:");
    ImGui::SameLine();
    ImGui::Checkbox("Auto-scroll", &log.autoScroll);
    ImGui::SameLine();
    ImGui::InputText("Search", log.searchBuffer, IM_ARRAYSIZE(log.searchBuffer));
    ImGui::SameLine();
    if (ImGui::Button("Clear")) {
        log.logLines.clear();
    }

    ImGui::Separator();
    ImGui::BeginChild("LogLines", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto &logLine : log.logLines) {
        if (strlen(log.searchBuffer) == 0 || logLine.find(log.searchBuffer) != std::string::npos) {
            if (logLine.find("[ERROR]") != std::string::npos) {
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255)); // Red color for errors
                ImGui::TextWrapped("%s", logLine.c_str());
                ImGui::PopStyleColor();
            } else if (logLine.find("[WARNING]") != std::string::npos) {
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255)); // Yellow color for warnings
                ImGui::TextWrapped("%s", logLine.c_str());
                ImGui::PopStyleColor();
            } else {
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(173, 216, 230, 255)); // Blueish color for info logs
                ImGui::TextWrapped("%s", logLine.c_str());
                ImGui::PopStyleColor();
            }
        }
    }

    if (log.autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}
