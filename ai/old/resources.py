#
# Project: ZAPPY
# File: resources.py
# Description: functions to get resources
#

from client import Client
from commands import Commands
from environment import Environment


class Resources:
    def __init__(self, client):
        self.client = Client(client)
        self.commands = Commands(self.client)
        self.env = Environment(self.commands)

    def get_food(self):
        look_response = self.commands.look()
        if 'food' in look_response:
            if self.commands.take_object('food'):
                return True
            else:
                find_response = self.find_item('food')
                self.env.move_to_tile(find_response)
                self.get_food()
        return True

    def get_linemate(self):
        look_response = self.commands.look()
        if 'linemate' in look_response:
            if self.commands.take_object('linemate'):
                return True
            else:
                find_response = self.find_item('linemate')
                self.env.move_to_tile(find_response)
                self.get_food()
        return True

    def get_deraumere(self):
        look_response = self.commands.look()
        if 'deraumere' in look_response:
            if self.commands.take_object('deraumere'):
                return True
            else:
                find_response = self.find_item('deraumere')
                self.env.move_to_tile(find_response)
                self.get_food()
        return True

    def get_sibur(self):
        look_response = self.commands.look()
        if 'sibur' in look_response:
            if self.commands.take_object('sibur'):
                return True
            else:
                find_response = self.find_item('sibur')
                self.env.move_to_tile(find_response)
                self.get_food()
        return True

    def get_mendiane(self):
        look_response = self.commands.look()
        if 'mendiane' in look_response:
            if self.commands.take_object('mendiane'):
                return True
            else:
                find_response = self.find_item('mendiane')
                self.env.move_to_tile(find_response)
                self.get_food()
        return True

    def get_phiras(self):
        look_response = self.commands.look()
        if 'phiras' in look_response:
            if self.commands.take_object('phiras'):
                return True
            else:
                find_response = self.find_item('phiras')
                self.env.move_to_tile(find_response)
                self.get_food()
        return True

    def get_thystame(self):
        look_response = self.commands.look()
        if 'thystame' in look_response:
            if self.commands.take_object('thystame'):
                return True
            else:
                find_response = self.find_item('thystame')
                self.env.move_to_tile(find_response)
                self.get_food()
        return True

    def get_all_resources(self):
        return self.get_food(), self.get_linemate(), self.get_deraumere(), self.get_sibur(), self.get_mendiane(), self.get_phiras(), self.get_thystame()

    def collect_food(self):
        response = self.commands.take_object('food')
        if response == 'ok':
            print("Successfully collected food")
        else:
            print("Failed to collect food")

    def find_item(self, item):
        look_response = self.commands.look()
        parsed_response = self.commands.parse_look_response(look_response)
        for tile_index, objects in parsed_response.items():
            if item in objects:
                return tile_index
        return None

    def search_and_collect_food(self):
        tile_with_food = self.find_item('food')
        if tile_with_food is not None:
            self.env.move_to_tile(tile_with_food)
            self.collect_food()
            if self.is_hungry(self.commands.parse_inventory_response(self.commands.inventory())):
                self.search_and_collect_food()
            else:
                print("Food level is sufficient")
                return True
        else:
            return False

    @staticmethod
    def is_hungry(inventory):
        return inventory.get('food', 0) < 10
