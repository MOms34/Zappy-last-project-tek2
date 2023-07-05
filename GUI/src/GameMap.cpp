/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameMap
*/

#include "GameMap.hpp"

Zappy::GUI::GameMap::GameMap(float length, float width, Zappy::GUI::ResourceHUD *resourceHUD, Client *server, QNode *parent) : QEntity(parent), _resourceHUD(resourceHUD), _server(server)
{
    for (float x = 0; x < length; ++x)
        for (float y = 0; y < width; ++y)
            createCube(x, y, length, width);
    QObject::connect(_server, &Client::cellUpdated, this, &GameMap::updateCells);
}

void Zappy::GUI::GameMap::updateCell(int x, int y, int nbResource, Zappy::GUI::ResourceType resource)
{
    if (_cellsEntity[std::make_pair(x, y)] && nbResource != _cellsEntity[std::make_pair(x, y)]->resourceCount(resource)) {
        int result = nbResource - _cellsEntity[std::make_pair(x, y)]->resourceCount(resource);
        if (result < 0) {
            for (int i = 0; i < result * -1; ++i) {
                _cellsEntity[std::make_pair(x, y)]->removeResource(resource);
            }
        } else {
            for (int i = 0; i < result; ++i) {
                _cellsEntity[std::make_pair(x, y)]->addResource(resource);
            }
        }
    }
}

void Zappy::GUI::GameMap::updateCells(int x, int y, PlayerInventory inventory)
{
    updateCell(x, y, inventory._food, Zappy::GUI::ResourceType::Food);
    updateCell(x, y, inventory._linemate, Zappy::GUI::ResourceType::Linemate);
    updateCell(x, y, inventory._deraumere, Zappy::GUI::ResourceType::Deraumere);
    updateCell(x, y, inventory._sibur, Zappy::GUI::ResourceType::Sibur);
    updateCell(x, y, inventory._mendiane, Zappy::GUI::ResourceType::Mendiane);
    updateCell(x, y, inventory._phiras, Zappy::GUI::ResourceType::Phiras);
    updateCell(x, y, inventory._thystame, Zappy::GUI::ResourceType::Thystame);
    if (_cellsEntity[std::make_pair(x, y)] && _cellsEntity[std::make_pair(x, y)] == _clickedEntity) {
        _resourceHUD->updateResources(_server->getCellContent(x, y), _cellsEntity[std::make_pair(x, y)]->getCoordinate());
    }
}

void Zappy::GUI::GameMap::handlePick(Qt3DRender::QPickEvent *event)
{
    if (_clickedEntity) {
        changeCubeTexture(_clickedEntity, _clickedEntity->findChild<Qt3DExtras::QTextureMaterial *>(), "GUI/assets/3D/ground.png");
    }
    Qt3DCore::QEntity *entity = qobject_cast<Qt3DCore::QEntity *>(event->entity());
    CellEntity *newClickedEntity = qobject_cast<CellEntity *>(entity);
    if (newClickedEntity) {
        if (_clickedEntity == newClickedEntity) {
            changeCubeTexture(_clickedEntity, _clickedEntity->findChild<Qt3DExtras::QTextureMaterial *>(), "GUI/assets/3D/ground.png");
            _clickedEntity = nullptr;
            _resourceHUD->clear();
        } else {
            std::pair<int, int> cellIndex = newClickedEntity->getCoordinate();
            changeCubeTexture(newClickedEntity, newClickedEntity->findChild<Qt3DExtras::QTextureMaterial *>(), "GUI/assets/3D/ground_selected.png");
            _clickedEntity = newClickedEntity;
            _resourceHUD->updateResources(_server->getCellContent(cellIndex.first, cellIndex.second), cellIndex);
        }
    }
}

void Zappy::GUI::GameMap::changeCubeTexture(Qt3DCore::QEntity *entity, Qt3DExtras::QTextureMaterial *material, const QString &texturePath)
{
    if (!entity || !material)
        return;
    Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D(entity);
    Qt3DRender::QTextureImage *textureImage = new Qt3DRender::QTextureImage();
    textureImage->setSource(QUrl::fromLocalFile(texturePath));
    texture->addTextureImage(textureImage);
    material->setTexture(texture);
}

void Zappy::GUI::GameMap::createCube(float x, float y, float length, float width)
{
    CellEntity *cellEntity = new CellEntity(x, y, length, width, this);
    _cellsEntity[std::make_pair(x, y)] = cellEntity;
    Qt3DRender::QObjectPicker *picker = new Qt3DRender::QObjectPicker(cellEntity);
    cellEntity->addComponent(picker);

    std::vector<Zappy::GUI::ResourceType> cellContent = _server->getCellContent(x, y);
    for (const auto& resourceType : cellContent)
        cellEntity->addResource(resourceType);

    connect(picker, &Qt3DRender::QObjectPicker::clicked, this, &GameMap::handlePick);
}

std::map<std::pair<int, int>, CellEntity*> Zappy::GUI::GameMap::getCells() const
{
    return _cellsEntity;
}
