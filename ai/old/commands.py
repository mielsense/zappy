#
# Project: ZAPPY
# File: commands.py
# Description: functions to handle commands for the AI
#

class Commands:
    def __init__(self, client):
        self.client = client

    def send_command(self, command):
        if self.client.socket:
            self.client.send_command(command)
            response = self.client.receive_response()
            if response == 'ko':
                print(f"Command {command} failed")
            return response
        else:
            print("Error: Socket is not open")
            return None

    def forward(self):
        return self.send_command('Forward')

    def right(self):
        return self.send_command('Right')

    def left(self):
        return self.send_command('Left')

    def look(self):
        response = self.send_command('Look')
        print(f"Raw Look response: {response}")
        if response.startswith("[") and response.endswith("]"):
            content = response[1:-1]
            print(f"Valid look response format: {content}")
            return content.split(', ')
        else:
            print(f"Unexpected look response format: {response}")
            return []

    @staticmethod
    def parse_look_response(response):
        parsed_response = {}
        for index, tile in enumerate(response):
            if tile:
                parsed_response[index] = tile.split()
        return parsed_response

    def inventory(self):
        response = self.send_command('Inventory')
        print(f"Raw Inventory response: {response}")
        if response.startswith("[") and response.endswith("]"):
            content = response[1:-1]
            items = content.split(', ')
            inventory_str = ', '.join(items)
            print(f"Parsed inventory: {inventory_str}")
            return inventory_str
        else:
            print(f"Unexpected inventory response format: {response}")
            return ""

    @staticmethod
    def parse_inventory_response(response):
        inventory = {}
        items = response.strip('{}').split(', ')
        for item in items:
            parts = item.split(': ')
            if len(parts) == 2:
                key, value = parts
                inventory[key.strip("'")] = int(value)
        return inventory

    def broadcast(self, message):
        return self.send_command(f'Broadcast {message}')

    def connect_nbr(self):
        return self.send_command('Connect_nbr')

    def fork(self):
        return self.send_command('Fork')

    def eject(self):
        return self.send_command('Eject')

    def take_object(self, object_name):
        command = f"Take {object_name}"
        self.send_command(command)
        if self.client.receive_response() == 'ok':
            return True
        if self.client.receive_response() == 'ko':
            return False

    def set_object(self, obj):
        command = f"Set {obj}"
        self.send_command(command)
        if self.client.receive_response() == 'ok':
            return True
        if self.client.receive_response() == 'ko':
            return False

    def incantation(self):
        return self.send_command('Incantation')
