/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameMap
*/

#pragma once

#include "CellEntity.hpp"
#include "HUDs.hpp"
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureImage>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickEvent>
#include <iostream>
#include "Client.hpp"


namespace Zappy {
    namespace GUI {
    class GameMap : public Qt3DCore::QEntity
    {
    public:
        GameMap(float length, float width, Zappy::GUI::ResourceHUD *resourceHUD, Client *server, QNode *parent = nullptr);
        std::map<std::pair<int, int>, CellEntity*> getCells() const;
    private slots:
        void handlePick(Qt3DRender::QPickEvent *event);
        void updateCells(int x, int y, PlayerInventory playerInventory);
        void updateCell(int x, int y, int nbResource, Zappy::GUI::ResourceType resource);

    protected:
        void changeCubeTexture(Qt3DCore::QEntity *entity, Qt3DExtras::QTextureMaterial *material, const QString &texturePath);
        void createCube(float x, float y, float length, float width);

    private:
        CellEntity *_clickedEntity = nullptr;
        Zappy::GUI::ResourceHUD *_resourceHUD;
        std::map<std::pair<int, int>, CellEntity*> _cellsEntity;
        Client *_server;
    };
    }
}
