/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(QString nameMachine, quint16 port) : QObject(), _nameMachine(nameMachine), _port(port)
{
    _socket.connectToHost(_nameMachine, _port);
    if (!_socket.waitForConnected(5000)) {
        throw std::runtime_error("Connexion failed: " + std::to_string(_port));
    }
    QObject::connect(&_socket, &QTcpSocket::readyRead, this, &Client::receiveMessage);

    sendMessage("GRAPHIC\n");
}

Client::~Client()
{
    _socket.disconnectFromHost();
}


void Client::sendMessage(const QString& cmd)
{
    std::cout << "Command: " << cmd.toStdString() << std::endl;
    QTextStream(&_socket) << cmd;
}

QString Client::readMessage()
{
    if (_socket.waitForReadyRead(5000)) {
        return _socket.readAll();
    }
    return QString();
}

void Client::communicate(const QString& cmd)
{
    sendMessage(cmd);
}

std::pair<int, int> Client::getMapSize()
{
    int width = _clientData.getXSize();
    int height = _clientData.getYSize();
    return std::pair<int, int>(width, height);
}

std::vector<Zappy::GUI::ResourceType> Client::getCellContent(int x, int y)
{
    const std::map<std::pair<int, int>, std::vector<int>>& resources = _clientData.getResources();
    auto it = resources.find(std::make_pair(x, y));
    if (it != resources.end()) {
        const std::vector<int>& resourceQuantities = it->second;
        std::vector<Zappy::GUI::ResourceType> tileContent;
        for (int i = 0; i < (int)resourceQuantities.size(); ++i) {
            Zappy::GUI::ResourceType resourceType = static_cast<Zappy::GUI::ResourceType>(i);
            for (int j = 0; j < (int)resourceQuantities[i]; ++j) {
                tileContent.push_back(resourceType);
            }
        }
        return tileContent;
    }
    return std::vector<Zappy::GUI::ResourceType>();
}

void Client::receiveMessage() {
    QString fullMessage = _socket.readAll();
    std::cout << "Received message:\n" << fullMessage.toStdString() << std::endl;

    QTextStream stream(&fullMessage);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        _clientData.parseData(line.toStdString());
        if (line.startsWith("pnw")) {
            std::string cmd;
            int id;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> id;
            emit newPlayerAdded(id);
        } else if (line.startsWith("ppo")) {
            std::string cmd;
            int id;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> id;
            emit playerPositionChanged(id);
        } else if (line.startsWith("pin")) {
            std::string cmd;
            int id;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> id;
            emit playerInventoryReceived(id);
        } else if (line.startsWith("bct")) {
            int x, y;
            PlayerInventory inventory;
            std::stringstream ss(line.toStdString());
            std::string cmd;
            ss >> cmd >> x >> y;
            ss >> inventory._food >> inventory._linemate >> inventory._deraumere >> inventory._sibur >> inventory._mendiane >> inventory._phiras>> inventory._thystame;
            emit cellUpdated(x, y, inventory);
        } else if (line.startsWith("pdi")) {
            std::string cmd;
            int id;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> id;
            emit playerKilled(id);
        } else if (line.startsWith("seg")) {
            std::string cmd;
            std::string teamName;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> teamName;
            emit endOfGame(teamName);
        } else if (line.startsWith("pic")) {
            std::string cmd;
            int x, y, l;
            std::vector<int> players;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> x >> y >> l;
            int playerId;
            while (ss >> playerId)
                emit playerIncantationStarted(playerId);
        } else if (line.startsWith("pie")) {
            std::string cmd;
            int x, y;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> x >> y;
            emit playerIncantationStoped(x, y);
        } else if (line.startsWith("enw")) {
            std::string cmd;
            int id, playerId;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> id >> playerId;
            std::cout << id << " egg sended" << std::endl;
            emit newEggAdded(id, playerId);
        } else if (line.startsWith("tna")) {
            std::string cmd, teamName;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> teamName;
            emit teamAdded(teamName);
        } else if (line.startsWith("eht")) {
            std::string cmd;
            int eggId;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> eggId;
            emit eggIsReady(eggId);
        } else if (line.startsWith("edi")) {
            std::string cmd;
            int eggId;
            std::stringstream ss(line.toStdString());
            ss >> cmd >> eggId;
            emit eggKilled(eggId);
        }
    }
    if (!_clientData.getResources().empty() && !_isInit) {
        _isInit = true;
        emit initializationReceived();
    }
}

