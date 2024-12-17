/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/components/Inventory.hpp"

using namespace zappy;

void
Inventory::draw()
{
    // Draw the inventory texture
    texture.Draw(position, 0.0f, 2.5f);

    // Draw the resource counts
    int slotHeight = 58;  // Further increase slot height for more spacing
    int textPadding = 10; // Adjust padding from the bottom right corner
    int fontSize = 25;    // Increase font size for better visibility

    vec2 textPos = position;
    textPos.y += 45; // Adjust starting vertical position
    textPos.x -= 38; // Adjust starting horizontal position to move text left

    // Define the correct order of resources
    std::vector<RessourceType> resourceOrder = {
        RessourceType::FOOD,
        RessourceType::LINEMATE,
        RessourceType::DERAUMERE,
        RessourceType::SIBUR,
        RessourceType::MENDIANE,
        RessourceType::PHIRAS,
        RessourceType::THYSTAME
    };

    for (const auto& type : resourceOrder) {
        std::string countText = std::to_string(count[type]);
        int offset = 0;

        if (count[type] > 9 && count[type] != 11) {
            offset = 8;
        }

        raylib::DrawText(countText.c_str(),
                         textPos.x + texture.width * 3 - textPadding - offset,
                         textPos.y - textPadding,
                         fontSize,
                         WHITE);
        textPos.y += slotHeight; // Move to the next slot position
    }
}
