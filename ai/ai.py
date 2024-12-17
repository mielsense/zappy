from time import sleep
from server_connection import ServerConnection
from commands import Commands


class Ai:
    def __init__(self, server_address, server_port, team_name):
        self.server_connection = ServerConnection(server_address, server_port)
        self.commands = []
        self.team_name = team_name
        self.commands = Commands(self)
        self.init()

    def auth(self):
        self.server_connection.send(f"{self.team_name}\n")
        response = self.server_connection.receive()
        if not response[0].isdigit():
            print("[ERROR] auth failed: ", response)
            self.server_connection.close()
            exit(1)
        remaining_slots = int(response[0])
        response = self.server_connection.receive()
        map_size = response.split(" ")
        map_size = (int(map_size[0]), int(map_size[1]))
        print("[LOG] auth success")
        print("[INFO] server settings: ", remaining_slots, map_size)

    def init(self):
        self.server_connection.connect(self.team_name)
        response = self.server_connection.receive()
        # clean response string
        response = response.replace("\n", "")
        response = response.replace(" ", "")
        response = response.replace("\r", "")
        if not response == "WELCOME":
            print("[ERROR] init")
            self.server_connection.close()
            exit(1)
        else:
            self.auth()

    def algorithm(self):
        while True:
            self.commands.forward()
            self.commands.inventory()
            self.commands.look()

    def close(self):
        self.server_connection.close()
