#
# Project: ZAPPY
# File: incantation.py
# Description: functions to handle incantation
#

class Incantation:
    def __init__(self, commands):
        self.commands = commands
        self.level = 1

    def start_incantation(self):
        if self.commands.incantation() == 'ok':
            self.commands.broadcast('Elevation underway')
            self.level += 1
            return True
        return False

    def cancel_incantation(self):
        self.commands.broadcast('Incantation cancelled')
        return True

#    def can_level_up(self, inventory):
#        required_resources = self.get_required_resources_for_level(self.level)
#        return all(inventory.get(resource, 0) >= required_resources[resource] for resource in required_resources)

    def have_enough_resources(self):
        inventory_response = self.commands.inventory()
        required_resources = self.get_required_resources_for_level(self.level)
        return all(resource in inventory_response for resource in required_resources)

    @staticmethod
    def get_required_resources_for_level(level):
        levels = {
            1: {'linemate': 1},
            2: {'linemate': 1, 'deraumere': 1, 'sibur': 1},
            3: {'linemate': 2, 'sibur': 1, 'phiras': 2},
            4: {'linemate': 1, 'deraumere': 1, 'sibur': 2, 'phiras': 1},
            5: {'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3},
            6: {'linemate': 1, 'deraumere': 2, 'sibur': 3, 'phiras': 1},
            7: {'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2,
                'phiras': 2, 'thystame': 1}
        }
        return levels.get(level, {})

    def check_incantation(self):
        if self.have_enough_resources():
            return True
        return False
