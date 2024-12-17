class Commands:
    def __init__(self, ai):
        self.ai = ai

    def inventory(self):
        self.ai.server_connection.send("Inventory\n")
        self.ai.server_connection.receive()

    def forward(self):
        self.ai.server_connection.send("Forward\n")
        self.ai.server_connection.receive()

    def look(self):
        self.ai.server_connection.send("Look\n")
        self.ai.server_connection.receive()
