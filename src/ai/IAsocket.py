#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## IA
## File description:
## socket
##

import socket
glob = False

class IASocket:

    def __init__(self, host, port):
        self.socket = None
        self.host = host
        self.port = port

    def connectToServer(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.settimeout(5)
        try:
            self.socket.connect((self.host, self.port))
        except Exception as e:
            print("socket : {}".format(e))
            return 1
        return 0
    
    def disconnectFromServer(self):
        self.socket.close()

    def sendMessage(self, message):
        if glob:
            print(message)
        self.socket.send(str.encode(message + "\n"))

    def receiveMessage(self):
        try:
            message = self.socket.recv(2048).decode().replace('\n', "")
            if glob:
                print(message, end="")
            return message
        except socket.timeout:
            return None
        