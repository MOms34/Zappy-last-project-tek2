#
# main.py
#

# Imports
from src.ai.player import Player
from src.ai.parse import Parse
import sys

# Global
player = Player()

# Launch Game
def launch_game():
	player.StartAll()
	player.StartGame()

# Main
def main():
	infos = Parse(sys.argv)
	if infos == None:
		return (84)
	print("Team name in main :")
	print(infos["name"])
	player.setTeamName(infos["name"])
	# print(infos["name"])
	print("player level: ")
	if player.connectToServer(infos) == -1:
		return (84)
	launch_game()
