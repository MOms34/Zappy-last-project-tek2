/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ResourceEntity
*/

#include "ResourceEntity.hpp"

#include <Qt3DRender/QTexture>
#include <Qt3DExtras/QTextureMaterial>

Zappy::GUI::ResourceEntity::ResourceEntity(const Zappy::GUI::ResourceType &resource, Qt3DCore::QNode *parent)
: Qt3DCore::QEntity(parent), _resource(resource)
{
    _colaTexture = createTexture("GUI/assets/3D/resources/cola_can_tex.jpg");
    _colaMesh = createMesh("GUI/assets/3D/resources/cola_can.obj");
    _diamondMesh = createMesh("GUI/assets/3D/resources/diamond.obj");
    loadOBJ();
}

Qt3DRender::QTexture2D *Zappy::GUI::ResourceEntity::createTexture(const QString &path)
{
    Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D();
    Qt3DRender::QTextureImage *textureImage = new Qt3DRender::QTextureImage();
    textureImage->setSource(QUrl::fromLocalFile(path));
    texture->addTextureImage(textureImage);
    return texture;
}

Qt3DRender::QMesh *Zappy::GUI::ResourceEntity::createMesh(const QString &path)
{
    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
    mesh->setSource(QUrl::fromLocalFile(path));
    return mesh;
}

Zappy::GUI::ResourceType Zappy::GUI::ResourceEntity::resource() const
{
    return _resource;
}

void Zappy::GUI::ResourceEntity::loadOBJ()
{
    _material = new Qt3DExtras::QPhongMaterial();
    _transform = new Qt3DCore::QTransform();
    _transform->setScale(0.05f);

    switch (_resource) {
        case ResourceType::Food:
        {
            _transform->setScale(0.01f);
            Qt3DExtras::QTextureMaterial *material = new Qt3DExtras::QTextureMaterial();
            material->setTexture(_colaTexture);
            addComponent(material);
            addComponent(_colaMesh);
            break;
        }
        case ResourceType::Linemate:
            _material->setDiffuse(QColor(0, 0, 255, 30));
            _material->setSpecular(Qt::white);
            addComponent(_material);
            addComponent(_diamondMesh);
            break;
        case ResourceType::Deraumere:
            _material->setDiffuse(QColor(0, 255, 0, 30));
            _material->setSpecular(Qt::white);
            addComponent(_material);
            addComponent(_diamondMesh);
            break;
        case ResourceType::Sibur:
            _material->setDiffuse(QColor(255, 0, 0, 30));
            _material->setSpecular(Qt::white);
            addComponent(_material);
            addComponent(_diamondMesh);
            break;
        case ResourceType::Mendiane:
            _material->setDiffuse(QColor(170, 0, 255, 30));
            _material->setSpecular(Qt::white);
            addComponent(_material);
            addComponent(_diamondMesh);
            break;
        case ResourceType::Phiras:
            _material->setDiffuse(QColor(184, 184, 184, 30));
            _material->setSpecular(Qt::white);
            addComponent(_material);
            addComponent(_diamondMesh);
            break;
        case ResourceType::Thystame:
            _material->setDiffuse(QColor(255, 255, 0, 30));
            _material->setSpecular(Qt::white);
            addComponent(_material);
            addComponent(_diamondMesh);
            break;
    }
    _transform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 90));
    addComponent(_transform);
}

void Zappy::GUI::ResourceEntity::removeResource()
{
    QPropertyAnimation *animation = new QPropertyAnimation(_transform, "translation");

    QVector3D startValue = _transform->translation();

    QVector3D endValue = startValue + QVector3D(0, 0, 1);

    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->setDuration(1000);

    QObject::connect(animation, &QPropertyAnimation::finished, this, [this]() {
        emit stop(this);
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

