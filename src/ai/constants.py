#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## IA
## File description:
## constants
##

# constants.py

# Rules
vision = [(0, 0), (1, 3), (4, 8), (9, 15), (16, 24), (25, 36), (37, 51), (52, 69), (70, 90)]
stones = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
levelUp_member = [0, 1, 2, 2, 4, 4, 6, 6]
max_inventory = {
	"linemate": 9,
	"deraumere": 8,
	"sibur": 10,
	"mendiane": 5,
	"phiras": 6,
	"thystame": 1
}
level_up_ressource = [{},
	{
		"linemate": 1,
		"deraumere": 0,
		"sibur": 0,
		"mendiane": 0,
		"phiras": 0,
		"thystame": 0
	},
	{
		"linemate": 1,
		"deraumere": 1,
		"sibur": 1,
		"mendiane": 0,
		"phiras": 0,
		"thystame": 0
	},
	{
		"linemate": 2,
		"deraumere": 0,
		"sibur": 1,
		"mendiane": 0,
		"phiras": 2,
		"thystame": 0
	},
	{
		"linemate": 1,
		"deraumere": 1,
		"sibur": 2,
		"mendiane": 0,
		"phiras": 1,
		"thystame": 0
	},
	{
		"linemate": 1,
		"deraumere": 2,
		"sibur": 1,
		"mendiane": 3,
		"phiras": 0,
		"thystame": 0
	},
	{
		"linemate": 1,
		"deraumere": 2,
		"sibur": 3,
		"mendiane": 0,
		"phiras": 1,
		"thystame": 0
	},
	{
		"linemate": 2,
		"deraumere": 2,
		"sibur": 2,
		"mendiane": 2,
		"phiras": 2,
		"thystame": 1
	}
]
round = 0

# Macros
LEVEL_MAX = 8
MIN_FOOD = 120

ACTIVE = True
PASSIVE = False

SUCCESS = 0
EXIT = 1
