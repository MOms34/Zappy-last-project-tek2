#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## IA
## File description:
## utils
##

# utils.py

# def my_range(a, b):
#     if a < b:
#         return range(a, b)
#     return range(b, a)

# def swap(vector):
#     tmp = vector.x
#     vector.x = vector.y
#     vector.y = tmp
#     return vector

# def same_sign(a, b):
#     if a < 0 and b < 0:
#         return True
#     elif a > 0 and b > 0:
#         return True
#     elif a == 0 and b == 0:
#         return True
#     return False

# class Pos:
#     x = 0
#     y = 0

# utils.py

def my_range(a, b):
    start = min(a, b)
    stop = max(a, b)
    return range(start, stop)

def my_swap(vector):
    vector.x, vector.y = vector.y, vector.x
    return vector

def is_same_sign(a, b):
    return (a < 0 and b < 0) or (a > 0 and b > 0) or (a == 0 and b == 0)

class Position:
    x = 0
    y = 0

