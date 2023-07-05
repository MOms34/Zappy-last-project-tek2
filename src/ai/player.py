#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## IA
## File description:
## player
##

from src.ai.IAsocket import IASocket
from random import randint
from src.ai.constants import *
from src.ai.utils import *
import time

class Player:

    def __init__(self):
        self.socket = None
        self.inventory = {
            "food": 1200,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }

        self.network_func = {
            "ready": self.print_ready_message,
            "start": self.print_start_message,
            "texte": self.print_zone_message
        }

        self.team_member = [0] * 9 #level max
        self.team_name = ""
        self.last_check = "" # dernier objet checker/regardé
        self.level = 1 # starting level is 1
        self.zone = 0
        self.isReady = False
        self.isJoining = False

################################ GETTER AND SETTER #################################

    def setTeamName(self, _name):
        self.team_name =_name

    def getTeamName(self):
        name = self.team_name
        return name
    
    def getMissing(self):
        missing = []

        for stone in stones:
            if level_up_ressource[self.level][stone] > self.inventory[stone]:
                missing.append(stone)
        return missing
    
################################ NETWORK ###########################################

    def connectToServer(self, _parsing):
        self.socket = IASocket(_parsing["host"], int(_parsing["port"]))
        return (self.socket.connectToServer())

    def sendMessage(self, message):
        print(message)
        self.socket.sendMessage(message)

    def receiveMessage(self):
        return self.socket.receiveMessage()

    def checkAnswer(self, msg):
        if msg == None:
            return "other"
        ret = ""
        for m in msg.split("\n"):
            if m == "":
                if ret == "":
                    ret = "other"
                return (ret)
            if m == "dead":
                print("Il mange les pissenlits par les racines")
                exit(0)
            elif m == "eject":
                pass
            elif m.split(" ")[0] == "message":
                ret = self.network_func[m.split(" ")[-1].split(",")[0]](m)
                if ret == EXIT:
                    return ("skip")
                elif ret == SUCCESS:
                    ret = "other"
            else:
                ret = m
        return (ret)

################################## PRINT MESSGAE #################################

    def print_ready_message(self, message):
        value = int(message.split(":")[1])
        print("Received ready message")
        self.team_member[value] += 1
        return SUCCESS

    def print_start_message(self, message):
        parts = message.split(":")[1].split("-")
        value = int(parts[0])
        zone_id = int(parts[1])

        if not self.is_ready:
            print("Available members for value {}: {}".format(value, self.team_member[value]))
            self.team_member[value] -= levelUp_member[value] - 1
            print("Updated available members for value {}: {}".format(value, self.team_member[value]))
        
        if not self.isJoining and self.is_ready and value == self.level:
            print("New zone ID: {}".format(zone_id))
            self.zone_id = zone_id
            self.isJoining = True
        
        return EXIT

    def print_zone_message(self, message):
        parts = message.split(",")

        number_part = parts[0].strip()

        number = number_part.split(" ")[1]
        value = int(number)

        if self.isJoining and self.zone_id == value:
            print("Attempting to join zone: {}".format(self.zone_id))
            self.JoinZone(message)
            return EXIT
            
        return SUCCESS

    
########################## METHODS #########################

    def checkPlayerNeeds(self, _obj):
        if _obj == "":
            return False
        if _obj == "food" or self.inventory[_obj] < max_inventory[_obj]:
            return True
        return False
    
    def FindAndTake(self):
        found = self.look()
        for obj in found.split(",")[0].split(" "):
            if obj == "player": # case deja prise par uun joueur
                continue
            if self.checkPlayerNeeds(obj):
                self.takeObject(obj)

    def LookingForStones(self, missing_item):
        infos = {
            "found": False,
            "case": 0
        }

        stone_index = 0
        while stone_index < len(missing_item):
            stone = missing_item[stone_index]
            case_index = 0
            case_list = self.last_check.split(",")
            while case_index < len(case_list):
                case = case_list[case_index]
                obj_index = 0
                obj_list = case.split(" ")
                while obj_index < len(obj_list):
                    obj = obj_list[obj_index]
                    if obj == stone:
                        infos["found"] = True
                        infos["case"] = case_index
                        return infos
                    obj_index += 1
                case_index += 1
            stone_index += 1
        return infos
    
    def Move(self, target_tile):
        destination = Position()
        i = 0

        for step_range in vision:
            if min(step_range) <= target_tile <= max(step_range):
                destination.y = i
                destination.x = target_tile - (max(step_range) - int((max(step_range) - min(step_range)) / 2 ))
            i = i + 1
        if destination.x < 0:
            self.TurnLeft()
        elif destination.x > 0:
            self.TurnRight()

        for _ in my_range(0, abs(destination.x)):
            self.MoveForward()

        if destination.x < 0:
            self.TurnRight()
        elif destination.x > 0:
            self.TurnLeft()

        for _ in my_range(0, destination.y):
            self.MoveForward()

    def FindMember(self):
        print ("dispo : " + str(self.team_member[self.level]) + " | need : " + str(levelUp_member[self.level]))
        if self.team_member[self.level] == levelUp_member[self.level] - 1:
            return True
        return False
    
    def isTeamComplete(self):
        count = 0

        message = self.look()
        for elem in message.split(",")[0].split(" "):
            if elem == "player":
                count = count + 1
        if count < levelUp_member[self.level]:
            return True
        self.Broadcast("texte")
        print(">> zone:" + str(self.zone_id))
        return False
    
    def Gather(self):

        print("Start gathering")
        if self.level == 1:
            self.StartIncantation(True)
            return 0

        call_count = 0
        self.zone_id = randint(1000, 3000)
        self.Broadcast("texte")

        while self.isTeamComplete() and call_count < 20:
            self.Broadcast("texte")
            print(">> zone: ")
            self.TurnLeft()
            print("wait")
            # call_count = call_count + 1
        self.zone_id = 0

        if call_count < 20:
            self.StartIncantation(True)

    def PlayGame(self, missing):
        global round

        if missing[0] != "food":
            print("Missing: " + str(missing))
        info = self.LookingForStones(missing)
        if info["found"]:
            self.Move(info["case"])
            self.FindAndTake()
            return 0
        if randint(0, 1) == 0:
            self.TurnLeft()
        else:
            self.TurnRight()
        self.MoveForward()
        self.FindAndTake()
        round = round + 1

        if round == 4:
            turn = 0
            self.TurnRight()
            for i in range(0, 5):
                self.MoveForward()
        return self.PlayGame(missing)

    # def GatherPlayer(self):

    #     print("Start gathering, lvl:", self.level)
    #     if self.level == 1:
    #         self.StartIncantation(True)
    #         return 0

    #     while True:
    #         broadcast_message = self.ReceiveBroadcast()
    #         print("broadcast : ", broadcast_message)
    #         if broadcast_message is not None:
    #             self.FollowBroadcast(broadcast_message)
    #         else:
    #             self.Broadcast("ready")
    #             print("WEEEEWEEEE")
    #         res = self.StartIncantation(True)
    #         if res == "ok":
    #             break


    # def ReceiveBroadcast(self):
    #     message = self.receiveMessage()
    #     if message is None:
    #         return None
    #     if message.startswith("message "):
    #         parts = message.split(":")
    #         dir = parts[1]. strip()
    #         return dir
    #     return None

    # def FollowBroadcast(self):
    #     f

    def JoinZone(self, _message):
        toFind = int(_message.split(",")[0].split(" ")[1])
        print("Join zone : " +_message)
        print("Where : " + str(toFind))

        if toFind == 0:
            self.StartIncantation(False)
            return 0
        elif toFind == 1:
            self.MoveForward()
        elif toFind in [2, 3, 4]:
            self.TurnLeft()
            self.MoveForward()
        elif toFind in [6, 7, 8]:
            self.TurnRight()
            self.MoveForward()
        elif toFind in 5:
            self.TurnLeft()
            self.TurnLeft()
        return self.checkAnswer(self.receiveMessage())
    
    def start(self):
        self.FindAndTake()

    def GatherAll(self):
        if not self.isReady and self.FindMember():
            self.isReady = True
            self.Gather()
        elif not self.isReady:
            self.Broadcast("texte")
            self.isReady = True
        
    def StartGame(self):
        print(">> Play")
        self.start
        while True:
            missing = self.getMissing()
            if missing:
                self.PlayGame(missing)
            else:
                self.PlayGame(["food"])
                self.GatherAll()

    def StartAll(self):
        self.receiveMessage()
        self.sendMessage(self.team_name)
        self.receiveMessage()
        self.receiveMessage()

########################## MOVEMENTS #########################

    def TurnRight(self):

        self.sendMessage("Right")
        self.inventory["food"] = self.inventory["food"] - 7

        response = ""
        while response not in ["ok", "ko", "skip"]:
            response = self.receiveMessage()
        return response
    
    def TurnLeft(self):
        self.sendMessage("Left")
        self.inventory["food"] = self.inventory["food"] - 7
        # response = self.receiveMessage()
        # if response != "ok\n":
        #     print("Error: turn left")
        # return response
        while True:
            response = self.receiveMessage()
            if response in ["ok", "ko", "skip"]:
                break
        return response
        # response = ""
        # while response not in ["ok", "ko", "skip"]:
        #     print("in turn left loop\n")
        #     print(response)
        #     response = self.checkAnswer(self.receiveMessage())
        # return response

    def MoveForward(self):
        self.sendMessage("Forward")
        self.inventory["food"] = self.inventory["food"] - 7

        response = ""
        while response not in ["ok", "ko", "skip"]:
            response = self.receiveMessage()
        return response

########################## ACTIONS 1 #########################

    def look(self):
        self.sendMessage("Look")
        self.inventory["food"] = self.inventory["food"] - 7
        # i = 0
        # while True:
        #     response = self.checkAnswer(self.receiveMessage())
        #     if response == "skip" or (response[0] == "[" and len(response) > 5):
        #         break
        # obj = response[2:-2]
        # self.last_check = obj
        # return obj
        response = self.checkAnswer(self.receiveMessage())
        while response not in ["skip", ""] and (response[0] != "[" or len(response) <= 5):
        #     print("bboucle look : ")
        #     print(i)
        #     print(response)
            response = self.checkAnswer(self.receiveMessage())
        obj = response[2:-2]
        self.last_check = obj
        return obj
    
    def Handle_inventory(self):
        self.sendMessage("Inventory")
        self.inventory["food"] = self.inventory["food"] - 1

        response = ""
        while not (response == "skip" or (response and response[0] == "[" and len(response) > 5)):
            response = self.checkAnswer(self.receiveMessage())
        
        obj = response[2:-2]
        return obj
    
    def Broadcast(self, _message):
        self.sendMessage("Broadcast " + _message)
        self.inventory["food"] = self.inventory["food"] - 7

        response = ""
        while response not in ["ok", "ko", "skip"]:
            response = self.checkAnswer(self.receiveMessage())
            print("MSG RECEIVED BD", response)
        return response
    
########################## ACTIONS 2 #########################

    def HandleConnectNumber(self):
        self.sendMessage("Connect_nbr")
        # doesn't consume food

        response = ""
        while not (response == "skip" or isinstance(response, int) and response in range(200)):
            response = self.checkAnswer(self.receiveMessage())
        return response
    
    def HandleEject(self):
        self.sendMessage("Eject")
        self.inventory["food"] = self.inventory["food"] - 7

        while True:
            response = self.checkAnswer(self.receiveMessage())
            if response in ["ok", "ko", "skip"]:
                break
        return response
    
    def HandleFork(self):
        self.sendMessage("Fork")
        self.inventory["food"] = self.inventory["food"] - 42

        while True:
            response = self.checkAnswer(self.receiveMessage())
            if response in ["ok", "ko", "skip"]:
                break
        return response
    
########################## ACTIONS 3 #########################

    def takeObject(self, _obj):
        self.sendMessage("Take " + _obj)
        self.inventory["food"] = self.inventory["food"] - 7

        response = self.checkAnswer(self.receiveMessage())
        while response not in ["ok", "ko", "skip"]:
            response = self.checkAnswer(self.receiveMessage())

        success = response == "ok"
        if success:
            self.inventory[_obj] += 1
            if _obj == "food":
                self.inventory[_obj] += 119
        return success
    
    def setObject(self, _obj):
        self.sendMessage("Set " +_obj)
        self.inventory["food"] = self.inventory["food"] - 7

        response = ""
        while response not in ["ok", "ko", "skip"]:
            response = self.receiveMessage()
        success = True if response == "ok" else False
        if success:
            self.inventory[_obj] = self.inventory[_obj] - 1
        return success

    def HandleIncantation(self, is_active):
        active_status = {True: "active", False: "passive"}
        message_count = 0

        print("Incantation: " + active_status[is_active])
        self.inventory["food"] -= 300
        if is_active:
            self.sendMessage("Incantation")
        while True:
            response = self.checkAnswer(self.receiveMessage())
            message_count += 1
            if response in ["Elevation underway", "ko", "skip"]:
                break
            if message_count >= 2:
                response = "ko"
                break
        if response == "ko":
            return response
        while True:
            response = self.checkAnswer(self.receiveMessage())
            if response.split(" ")[0] in ["Current", "ko", "skip"]:
                break
        return response

    def StartIncantation(self, is_active):
        print("Start Incantation")
        for stone, count in level_up_ressource[self.level].items():
            for i in range(0, count):
                self.setObject(stone)
        if self.HandleIncantation(True):
            self.level += 1
        self.isReady = False
        self.isJoining = False
        print(">> level: " + str(self.level))
        self.HandleFork()


