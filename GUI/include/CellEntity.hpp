/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** CellEntity
*/

#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureImage>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QPickEvent>
#include <Qt3DExtras/QConeMesh>
#include <iostream>
#include <unordered_map>
#include <QRandomGenerator>
#include <ResourceEntity.hpp>


class CellEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    CellEntity(float x, float y, float length, float width, Qt3DCore::QNode *parent = nullptr);
    void addResource(const Zappy::GUI::ResourceType &resource);
    QList<Zappy::GUI::ResourceEntity*> getResources() const;
    std::pair<int, int> getCoordinate() const;
    int resourceCount(Zappy::GUI::ResourceType type);
    void removeResource(Zappy::GUI::ResourceType type);

    private slots:
        void deleteResource(Zappy::GUI::ResourceEntity *resource);
private:
    QList<Zappy::GUI::ResourceEntity*> _resources;
    int _x;
    int _y;
};
