import socket
from time import sleep


class ServerConnection:
    def __init__(self, hostname, port):
        self.host = hostname
        self.port = port
        self.socket = socket.socket()

    def connect(self, team_name):
        try:
            print(f"[LOG] connecting to server {self.host}:{self.port}")
            self.socket.connect((self.host, self.port))
            print("[LOG] connected to server")
        except Exception as e:
            print("[ERROR] cannot connect to server: ", e)
            exit(1)

    def close(self):
        if hasattr(self, 'socket'):
            self.socket.close()

    def send(self, message):
        try:
            print("[LOG] sending message: ", message.replace("\n", ""))
            self.socket.sendall(message.encode())
        except Exception as e:
            print("[ERROR] cannot send message: ", e)
            exit(1)

    def receive(self):
        try:
            response = self.socket.recv(1024).decode()
            response = response.replace("\r", "")
            response = response.replace("\n", "")
            print("[SERVER] received message: ", response)
            return response
        except Exception as e:
            print("[ERROR] cannot receive message", e)
            exit(1)
