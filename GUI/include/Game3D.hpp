/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game3D
*/

#pragma once

#include "HUDs.hpp"
#include "GameMap.hpp"
#include "qt3dwidget.h"
#include "PlayerEntity.hpp"
#include "EggEntity.hpp"

#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QSpotLight>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QForwardRenderer>
#include <QVBoxLayout>
#include <QVector3D>
#include <QShortcut>

#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>


namespace Zappy {
    namespace GUI {
        class Game3D : public QWidget
        {
            Q_OBJECT

        public:

            Game3D(Client *client, QWidget *parent);
            ~Game3D();

            void setCamera();
            void setLight(QVector3D position);
            std::pair<float, float> getCellCoordinates(float x, float y);
            void setPlayerRotation(PlayerEntity *player, int orientation);
            void setPlayerRotation(int id, int orientation);
            void startPlayerAnimation(int id);

        private slots:
            void handleInitialization();
            void addPlayer(int playerId);
            void addEgg(int eggId, int playerId);
            void changePlayerPosition(int playerId);
            void playerStartIncantation(int playerId);
            void playerStopIncantation(int x, int y);
            void playerPick(Qt3DRender::QPickEvent *event);
            void updatePlayerInventory(int playerId);
            void playerKill(int playerId);
            void addTeam(std::string teamName);
            void moveCameraLeft();
            void moveCameraRight();
            void moveCameraUp();
            void moveCameraDown();
            void eggReady(int eggId);
            void eggKill(int eggId);

        signals:
            void endOfGame();
        public:
            Client *_client;
        private:
            Qt3DWidget *_view;
            Qt3DCore::QEntity *_rootEntity;
            Zappy::GUI::ResourceHUD *_resourceHUD;
            Zappy::GUI::PlayerHUD *_playerHUD;
            Zappy::GUI::TeamHUD *_teamHUD;
            Zappy::GUI::GameMap *_gameMap;
            std::map<int, PlayerEntity*> _players;
            std::map<int, EggEntity*> _eggs;
            std::map<std::string, int> _teams;
            PlayerEntity *_playerClicked = nullptr;
            QShortcut *_leftShortcut;
            QShortcut *_rightShortcut;
            QShortcut *_upShortcut;
            QShortcut *_downShortcut;
        };
    }
}