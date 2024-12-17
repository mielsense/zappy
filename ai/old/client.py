#
# Project: ZAPPY
# File: client.py
# Description: functions to handle client connection
#

from server_connection import ServerConnection


class Client:
    def __init__(self, team_name=None, hostname=None, port=None):
        self.team_name = team_name
        self.server_connection = ServerConnection(hostname, port)
        self.socket = self.server_connection.socket

    def connect_to_server(self):
        self.server_connection.connect(self.team_name)

    def send_command(self, command):
        self.server_connection.send_command_from_server(command)

    def receive_response(self):
        response = self.server_connection.receive_response_from_server()
        return response

    def close(self):
        self.server_connection.close()
