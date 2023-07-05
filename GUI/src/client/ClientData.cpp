/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** Parse
*/

#include "ClientData.hpp"

void ClientData::parseMSZ(std::stringstream& ss)
{
    ss >> _XSize >> _YSize;
}

void ClientData::parseBCT(std::stringstream& ss )
{
    int x, y;
    ss >> x >> y;
    std::vector<int> resources_for_cell(7);
    for (int i = 0; i < 7; i++)
        ss >> resources_for_cell[i];
    _resources[{x, y}] = resources_for_cell;
    for (const auto &resource : resources_for_cell)
        std::cout << resource << " ";
    std::cout << "\n";
}

void ClientData::parseMCT(std::stringstream& ss)
{
    std::string line;
    while (std::getline(ss, line)) {
        std::stringstream ss_line(line);
        std::string first_token;
        ss_line >> first_token;
        if (first_token == "bct") {
            int x, y;
            ss_line >> x >> y;
            std::vector<int> cell_resources;
            int resource;

            while (ss_line >> resource)
                cell_resources.push_back(resource);
            _resources[{x, y}] = cell_resources;
        } else {
            line = line.substr(1);
            std::stringstream ss_line(line);
            std::string token;
            ss_line >> token >> token;

            std::vector<int> cell_resources;
            int resource;

            while (ss_line >> resource)
                cell_resources.push_back(resource);
            _resources[{0, 0}] = cell_resources;
        }
    }
}

void ClientData::parseTNA(std::stringstream& ss)
{
    std::string teamName;
    std::getline(ss, teamName);
    teamName = teamName.substr(1);
    _teams.push_back(teamName);
    std::cout << "tna added" << std::endl;
}


void ClientData::parseData(const std::string &data)
{
    std::stringstream ss(data);
    std::string command;
    ss >> command;
    if (command == "msz") {
        parseMSZ(ss);
    } else if (command == "bct") {
        (data.length() >= 100) ? parseMCT(ss) : parseBCT(ss);
    } else if (command == "tna") {
        parseTNA(ss);
    } else if (command == "ppo") {
        int id, x, y, orientation;
        ss >> id >> x >> y >> orientation;
        _players[id]._x = x;
        _players[id]._y = y;
        _players[id]._orientation = orientation;
    } else if (command == "plv") {
        int id, level;
        ss >> id >> level;
        _players[id]._level = level;
    } else if (command == "pin") {
        int id, x, y;
        ss >> id >> x >> y;
        ss >> _players[id]._inventory._food >> _players[id]._inventory._linemate >> _players[id]._inventory._deraumere >> _players[id]._inventory._sibur >> _players[id]._inventory._mendiane >> _players[id]._inventory._phiras>> _players[id]._inventory._thystame;
    } else if (command == "sgt") {
        ss >> _timeUnit;
        std::cout << "Current time unit for the execution of actions : " << _timeUnit << "\n";
    } else if (command == "sst") {
        ss >> _timeUnit;
        std::cout << "New time unit for the execution of actions : " << _timeUnit << "\n";
    } else if (command == "pnw") {
        PlayerData newPlayer;
        ss >> newPlayer._id >> newPlayer._x >> newPlayer._y >> newPlayer._orientation >> newPlayer._level >> newPlayer._teamName;
        _players[newPlayer._id] = newPlayer;
    } else if (command == "pex") {
        int playerNumber;
        ss >> playerNumber;
        _players[playerNumber];
    } else if (command == "pbc") {
    } else if (command == "pic") {
    } else if (command == "pie") {
        ss >> _XSize >> _YSize >> _incantationResult;
    } else if (command == "pfk") {
    } else if (command == "pdr") {
    } else if (command == "pgt") {
    } else if (command == "pdi") {
    } else if (command == "enw") {
        EggData eggData;
        int playerId;
        ss >> eggData._id >> playerId >> eggData._x >> eggData._y;
        _eggs[eggData._id] = eggData;
        std::cout << "egg " << eggData._id << " is added" << std::endl;
    } else if (command == "ebo") {
    } else if (command == "edi") {
    } else if (command == "seg") {
    } else if (command == "smg") {
    }
}

int ClientData::getXSize() const { return _XSize; }

int ClientData::getYSize() const { return _YSize; }

const std::map<std::pair<int, int>, std::vector<int>>& ClientData::getResources() const { return _resources; }

const std::vector<std::string>& ClientData::getTeams() const { return _teams; }

std::string ClientData::getGraphicName() const { return _graphicName; }

PlayerData ClientData::getPlayer(int id) const
{
    return _players.at(id);
}

EggData ClientData::getEgg(int id) const { return _eggs.at(id); }

std::map<int, PlayerData> ClientData::getPlayers() const { return _players; }
