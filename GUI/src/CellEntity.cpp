/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** CellEntity
*/

#include "CellEntity.hpp"

CellEntity::CellEntity(float x, float y, float length, float width, Qt3DCore::QNode *parent) : Qt3DCore::QEntity(parent),_x(x), _y(y)
{
    Qt3DExtras::QCuboidMesh *cubeMesh = new Qt3DExtras::QCuboidMesh();
    cubeMesh->setXExtent(1.0f);
    cubeMesh->setYExtent(1.0f);
    cubeMesh->setZExtent(1.0f);

    Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D(this);
    Qt3DRender::QTextureImage *textureImage = new Qt3DRender::QTextureImage();
    textureImage->setSource(QUrl::fromLocalFile("GUI/assets/3D/ground.png"));
    texture->addTextureImage(textureImage);

    Qt3DExtras::QTextureMaterial *material = new Qt3DExtras::QTextureMaterial();
    material->setTexture(texture);

    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
    transform->setTranslation(QVector3D(x - length / 2.0f + 0.5f, y - width / 2.0f + 0.5f, 0.0f));

    addComponent(cubeMesh);
    addComponent(material);
    addComponent(transform);
}

void CellEntity::deleteResource(Zappy::GUI::ResourceEntity *resource)
{
    delete resource;
}

void CellEntity::addResource(const Zappy::GUI::ResourceType &resource)
{
    Zappy::GUI::ResourceEntity *resourceEntity = new Zappy::GUI::ResourceEntity(resource, this);
    QObject::connect(resourceEntity, &Zappy::GUI::ResourceEntity::stop, this, &CellEntity::deleteResource);
    Qt3DCore::QTransform *transform = resourceEntity->findChild<Qt3DCore::QTransform *>();
    if (transform) {
        float offsetX = (QRandomGenerator::global()->bounded(0.8) - 0.4);
        float offsetY = (QRandomGenerator::global()->bounded(0.8) - 0.4);
        if (resource == Zappy::GUI::ResourceType::Food)
            transform->setTranslation(QVector3D(offsetX, offsetY, 0.56));
        else
            transform->setTranslation(QVector3D(offsetX, offsetY, 0.52));
    }
    _resources.append(resourceEntity);
}

QList<Zappy::GUI::ResourceEntity*> CellEntity::getResources() const
{
    return _resources;
}

std::pair<int, int> CellEntity::getCoordinate() const
{
    return std::make_pair(_x, _y);
}

int CellEntity::resourceCount(Zappy::GUI::ResourceType type)
{
    int count = 0;
    for (Zappy::GUI::ResourceEntity *resource : _resources)
        if (resource->resource() == type)
            ++count;
    return count;
}

void CellEntity::removeResource(Zappy::GUI::ResourceType type)
{
    int i = 0;
    for (Zappy::GUI::ResourceEntity *resource : _resources) {
        if (resource->resource() == type) {
            resource->removeResource();
            break;
        }
        ++i;
    }
    _resources.removeAt(i);
}
