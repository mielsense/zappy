#
# Project: ZAPPY
# File: inventory.py
# Description: functions to interact with the inventory
#

class Inventory:
    def __init__(self, server_connection):
        self.server_connection = server_connection
        self.inventory = {
            'food': 0,
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane': 0,
            'phiras': 0,
            'thystame': 0
        }
        self.level = 1

    def get_inventory(self):
        self.server_connection.send_command('Inventory')
        inventory_response = self.server_connection.receive_response()
        self.update_inventory(inventory_response)
        return inventory_response

    def update_inventory(self, inventory_response):
        inventory_response = inventory_response.strip('[]').split(',')
        for item in inventory_response:
            if ' ' in item:
                key, value = item.split()
                self.inventory[key] = int(value)

    def print_inventory(self):
        for resource, quantity in self.inventory.items():
            print(f"{resource}: {quantity}")
