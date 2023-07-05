/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** Parse
*/

#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <sstream>

struct PlayerInventory
{
    int _food = 0;
    int _linemate = 0;
    int _deraumere = 0;
    int _sibur = 0;
    int _mendiane = 0;
    int _phiras = 0;
    int _thystame = 0;
};

struct PlayerData
{
    int _id = -1;
    int _x = -1;
    int _y = -1;
    int _orientation = -1;
    int _level = -1;
    std::string _teamName = "null";
    PlayerInventory _inventory;
};

struct EggData
{
    int _id = -1;
    int _x = -1;
    int _y = -1;
};

class ClientData
{
public:
    int getXSize() const;
    int getYSize() const;
    const std::map<std::pair<int, int>, std::vector<int>>& getResources() const;
    const std::vector<std::string>& getTeams() const;
    std::string getGraphicName() const;
    PlayerData getPlayer(int id) const;
    EggData getEgg(int id) const;
    std::map<int, PlayerData> getPlayers() const;

    void parseData(const std::string &data);
protected:
    void parseMSZ(std::stringstream& ss);
    void parseBCT(std::stringstream& ss);
    void parseMCT(std::stringstream& ss);
    void parseTNA(std::stringstream& ss);

private:
    int _XSize = 0;
    int _YSize = 0;
    std::map<std::pair<int, int>, std::vector<int>> _resources;
    std::map<int, PlayerData> _players;
    std::map<int, EggData> _eggs;
    std::vector<std::string> _teams;
    int _eggNumber = 0;
    int _timeUnit = 0;
    int _incantationResult = 0;
    std::string _graphicName = "localhost";
};

