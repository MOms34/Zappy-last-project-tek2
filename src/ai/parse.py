#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## IA
## File description:
## parse
##
def printUsage(_bin_name):
    print("USAGE: " + _bin_name + " -p port -n name -h machine")
    print("\tport is the port number")
    print("\tname is the name of the team")
    print("\tmachine is the name of the machine; localhost by default")
        
def getParam(_param, _argv, _i):
    flag = {
        "-p": "port",
        "-n": "name",
        "-h": "host"
    }
    argvs = ["-p", "-n", "-h"]
    for argv in argvs:
        if _argv[_i] == argv:
            _param[flag[argv]] = _argv[_i + 1]
            return _param
    return 1

def Parse(_argv):
    length = len(_argv)

    parsing = {
        "host": "localhost",
        "name": "",
        "port": 0
    }
    if length == 1:
        return 1
    for param in _argv:
        if param == "-help":
            printUsage(_argv[0])
            exit(0)
    for i in range(1, length):
        if i % 2 == 1:
            parsing = getParam(parsing, _argv, i)
        if parsing == 1:
            printUsage(_argv[0])
            return 1
    return parsing
