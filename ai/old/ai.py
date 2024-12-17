#
# Project: ZAPPY
# File: ai.py
# Description: mains functions for the AI and make decisions
#

from incantation import Incantation
from resources import Resources
from inventory import Inventory
from environment import Environment


class AI:
    def __init__(self, client, commands):
        self.client = client
        self.commands = commands
        self.incantation = Incantation(commands)
        self.current_tile = (0, 0)
        self.resources = Resources(client)
        self.inventory = Inventory(client)
        self.environment = Environment(client)

    def make_decision(self):
        while True:
            inventory_response = self.commands.inventory()
            inventory = self.commands.parse_inventory_response(
                inventory_response)
            # Prioritize finding food if food level is low
            # TODO check the pertinence of the condition maybe switch
            # with the incantation first
            if self.resources.is_hungry(inventory):
                self.resources.search_and_collect_food()
            else:
                if self.incantation.check_incantation():
                    self.incantation.start_incantation()
                else:
                    self.explore_and_collect()

    def explore_and_collect(self):
        look_response = self.commands.look()
        items_to_collect = ['linemate', 'deraumere',
                            'sibur', 'mendiane', 'phiras', 'thystame']

        # Vérifier et collecter les objets visibles
        for item in items_to_collect:
            if item in look_response:
                self.commands.take_object(item)
                return  # Sortir après avoir trouvé un objet à collecter

        # Sinon, chercher dans les ressources
        for item in items_to_collect:
            item_response = self.resources.find_item(item)
            if item_response is not None:
                self.environment.move_to_tile(item_response)
                self.commands.take_object(item)
                return  # Sortir après avoir trouvé et collecté un objet

    def algorithm(self):
        print("Executing algorithm")
        look_result = self.commands.look()
        print(f"Look result: {look_result}")
        inventory_response = self.commands.inventory()
        inventory = self.commands.parse_inventory_response(
            str(inventory_response))
        print(f"Inventory: {inventory}")
        self.make_decision()
        print("Algorithm executed")
