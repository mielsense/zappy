#
# Project: ZAPPY
# File: server_connection.py
# Description: functions to handle server connection
#

import socket
import time


class ServerConnection:
    def __init__(self, hostname, port):
        self.host = hostname
        self.port = port
        self.socket = socket.socket()

    def connect(self, team_name):
        try:
            self.socket.connect((self.host, self.port))
            welcome_message = self.socket.recv(1024).decode('utf-8').strip()
            print("Received message from server:", welcome_message)
            if "WELCOME" in welcome_message:
                print("Sending team name to server: ", team_name)
                self.socket.sendall((team_name + "\n").encode())
                additional_message = self.receive_response_from_server()
                print("Received additional message from server:",
                      additional_message)
                if additional_message == "ko":
                    print(
                        "ERROR: Received 'ko' from server, connection failed.")
                    exit(1)
        except Exception as e:
            print("ERROR: connect to server", e)
            exit(1)

    def send_command_from_server(self, command):
        try:
            print(f"Sending command: {command}")
            self.socket.sendall((command + '\n').encode())
            response = self.receive_response_from_server()
            return response
        except Exception as e:
            print(f"Error sending command {command}: {e}")

    def receive_response_from_server(self):
        try:
            response = self.socket.recv(1024).decode('utf-8').strip()
            while not response:
                time.sleep(1)
                response = self.socket.recv(1024).decode('utf-8').strip()
            print(f"Received response: {response}")
            return response
        except Exception as e:
            print(f"Error receiving response: {e}")
            return ""

    def close(self):
        if hasattr(self, 'socket'):
            self.socket.close()
