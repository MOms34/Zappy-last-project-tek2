/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** eggEntity
*/

#include "EggEntity.hpp"

Zappy::GUI::EggEntity::EggEntity(int id, int skinId, Qt3DCore::QNode *parent) : Qt3DCore::QEntity(parent), _id(id)
{
    _eggTexture = createTexture("GUI/assets/3D/player/player_texture.png");
    _eggConnectedTexture = createTexture("GUI/assets/3D/player/player_texture" + QString::number(skinId) + ".JPEG");
    _eggMesh = createMesh("GUI/assets/3D/player/egg.obj");
    loadOBJ();
}

void Zappy::GUI::EggEntity::changeEggTexture(bool isConnected)
{
    if (isConnected)
        _materialTex->setTexture(_eggConnectedTexture);
    else
        _materialTex->setTexture(_eggTexture);
}

void Zappy::GUI::EggEntity::loadOBJ()
{
    _material = new Qt3DExtras::QPhongMaterial();
    _transform = new Qt3DCore::QTransform();
    _transform->setScale(0.010f);

    _materialTex = new Qt3DExtras::QTextureMaterial();
    _materialTex->setTexture(_eggTexture);

    addComponent(_materialTex);
    addComponent(_eggMesh);
    addComponent(_transform);
    changeEggTexture(true);
    changeEggTexture(false);
}

Qt3DRender::QTexture2D *Zappy::GUI::EggEntity::createTexture(const QString &path)
{
    Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D();
    Qt3DRender::QTextureImage *textureImage = new Qt3DRender::QTextureImage();
    textureImage->setSource(QUrl::fromLocalFile(path));
    texture->addTextureImage(textureImage);
    return texture;
}

Qt3DRender::QMesh *Zappy::GUI::EggEntity::createMesh(const QString &path)
{
    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
    mesh->setSource(QUrl::fromLocalFile(path));
    return mesh;
}

int Zappy::GUI::EggEntity::getId() const { return _id; }