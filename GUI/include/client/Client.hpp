/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** Server
*/

#pragma once

#include "ClientData.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include "ResourceEntity.hpp"
#include <QTcpSocket>
#include <QTextStream>
#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QString nameMachine, quint16 port);
    ~Client();
    void sendMessage(const QString& cmd);
    QString readMessage();
    void communicate(const QString& cmd);
    std::pair<int, int> getMapSize();
    std::vector<Zappy::GUI::ResourceType> getCellContent(int x, int y);

    ClientData _clientData;
signals:
    void initializationReceived();
    void newPlayerAdded(int playerId);
    void newEggAdded(int eggId, int playerId);
    void playerPositionChanged(int playerId);
    void playerInventoryReceived(int playerId);
    void cellUpdated(int x, int y, PlayerInventory playerInventory);
    void playerKilled(int playerId);
    void endOfGame(std::string teamName);
    void playerIncantationStarted(int id);
    void playerIncantationStoped(int x, int y);
    void teamAdded(std::string teamName);
    void eggIsReady(int eggId);
    void eggKilled(int eggId);
public slots:
    void receiveMessage();
private:
    QTcpSocket _socket;
    QString _nameMachine;
    quint16 _port;
    bool _isInit = false;
};
