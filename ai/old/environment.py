#
# Project: ZAPPY
# File: environment.py
# Description: functions to check environment
#

class Environment:
    def __init__(self, commands):
        self.commands = commands
        self.map = {}
        self.direction = 0  # 0: Up, 1: Right, 2: Down, 3: Left

    def explore_map(self):
        steps = [self.commands.forward, self.commands.look, self.commands.right]
        for step in steps:
            response = step()
            print(f"{step.__name__} response: {response}")
            if response == 'ko':
                print(f"Command {step.__name__} failed")

    def update_map(self, look_str):
        tiles = look_str.strip('[]').split(',')
        for index, tile in enumerate(tiles):
            self.map[index] = tile.split()

    def print_map(self):
        for position, resources in self.map.items():
            print(f"Tile {position}: {resources}")

    def rotate_right(self):
        self.direction = (self.direction + 1) % 4
        self.commands.turn_right()

    def rotate_left(self):
        self.direction = (self.direction - 1) % 4
        self.commands.turn_left()

    # TODO: Test move_to_tile
    def move_to_tile(self, target_tile):
        current_direction = self.direction  # Sauvegarde la direction actuelle
        movements = self.calculate_movements(target_tile)  # Calcule les mouvements nécessaires vers la tuile cible
        for move in movements:  # Pour chaque mouvement calculé
            if move == 'F':  # Si le mouvement est 'Forward'
                self.commands.forward()  # Exécute la commande d'avancer
            elif move == 'R':  # Si le mouvement est 'Right'
                self.rotate_right()  # Tourne à droite
            elif move == 'L':  # Si le mouvement est 'Left'
                self.rotate_left()  # Tourne à gauche

    def calculate_movements(self, target_tile):
        movements = []  # Initialise une liste de mouvements vide
        tile_index = int(target_tile)  # Convertit la tuile cible en index
        if tile_index == 0:  # Si la tuile cible est la tuile actuelle
            return movements  # Retourne la liste vide (aucun mouvement nécessaire)

        current_x, current_y = 0, 0  # Position initiale (0, 0)
        target_x, target_y = self.calculate_target_coordinates(tile_index)  # Calcule les coordonnées cibles
        delta_x = target_x - current_x  # Différence en x
        delta_y = target_y - current_y  # Différence en y

        if delta_y > 0:  # Si la différence en y est positive
            for _ in range(delta_y):  # Pour chaque unité de différence
                movements.append('F')  # Ajoute 'Forward' aux mouvements
        elif delta_y < 0:  # Si la différence en y est négative
            self.rotate_right()  # Tourne à droite
            self.rotate_right()  # Tourne à droite (demi-tour)
            for _ in range(abs(delta_y)):  # Pour chaque unité de différence absolue
                movements.append('F')  # Ajoute 'Forward' aux mouvements
            self.rotate_right()  # Tourne à droite
            self.rotate_right()  # Tourne à droite (retour à la direction initiale)

        if delta_x > 0:  # Si la différence en x est positive
            self.rotate_right()  # Tourne à droite
            for _ in range(delta_x):  # Pour chaque unité de différence
                movements.append('F')  # Ajoute 'Forward' aux mouvements
            self.rotate_left()  # Tourne à gauche (retour à la direction initiale)
        elif delta_x < 0:  # Si la différence en x est négative
            self.rotate_left()  # Tourne à gauche
            for _ in range(abs(delta_x)):  # Pour chaque unité de différence absolue
                movements.append('F')  # Ajoute 'Forward' aux mouvements
            self.rotate_right()  # Tourne à droite (retour à la direction initiale)

        return movements  # Retourne la liste de mouvements

    @staticmethod
    def calculate_target_coordinates(tile_index):
        if tile_index == 0:  # Si l'index de la tuile est 0
            return 0, 0  # Retourne les coordonnées (0, 0)

        layer = 1  # Initialise le niveau à 1
        while tile_index > (layer * layer + layer):  # Tant que l'index de la tuile est supérieur à la formule
            layer += 1  # Augmente le niveau

        layer_start_index = (layer - 1) * (layer - 1) + (layer - 1)  # Calcul l'index de début du niveau
        position_in_layer = tile_index - layer_start_index - 1  # Calcul la position dans le niveau
        max_index_in_layer = 2 * layer  # Calcul l'index maximum dans le niveau

        x = (position_in_layer % (max_index_in_layer + 1)) - layer  # Calcul les coordonnées x
        y = layer - (position_in_layer // (max_index_in_layer + 1))  # Calcul les coordonnées y

        return x, y  # Retourne les coordonnées calculées

    def max_to_go(self):
        look_response = self.commands.look()
        parsed_response = look_response.strip('[]').split(',')
        return len(parsed_response)
