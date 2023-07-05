/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** PlayerEntity
*/

#include "PlayerEntity.hpp"

Zappy::GUI::PlayerEntity::PlayerEntity(int id, int skinId, Qt3DCore::QNode *parent) : Qt3DCore::QEntity(parent), _id(id)
{
    _playerTexture = createTexture("GUI/assets/3D/player/player_texture" + QString::number(skinId) + ".JPEG");
    _playerSelectedTexture = createTexture("GUI/assets/3D/player/player_texture.png");
    _playerMesh = createMesh("GUI/assets/3D/player/model.obj");
    loadOBJ();
}

void Zappy::GUI::PlayerEntity::initBounceAnimation()
{
    Qt3DCore::QTransform *transform = findChild<Qt3DCore::QTransform *>();
    _floatingAnimation = new QPropertyAnimation(transform, "translation");
    _floatingAnimation->setEasingCurve(QEasingCurve::InOutSine);
    QVector3D startValue = transform->translation();
    QVector3D midValue = startValue + QVector3D(0, 0, 0.3);
    _floatingAnimation->setStartValue(startValue);
    _floatingAnimation->setKeyValueAt(0.5, midValue);
    _floatingAnimation->setEndValue(startValue);
    _floatingAnimation->setDuration(1000);

    _floatingAnimation->setLoopCount(-1);
}

void Zappy::GUI::PlayerEntity::move(float x, float y)
{
    if (_floatingAnimation)
        stopAnimation();
    _inMouvement = true;
    QPropertyAnimation *animation = new QPropertyAnimation(_transform, "translation");
    QVector3D startValue = _transform->translation();
    QVector3D endValue = QVector3D(x, y, 0.5);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->setDuration(300);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    QObject::connect(animation, &QPropertyAnimation::finished, [this](){
        initBounceAnimation();
        startBounceAnimation();
        _inMouvement = false;
    });
}

void Zappy::GUI::PlayerEntity::animRotation(int orientation)
{
    stopAnimation();
    QPropertyAnimation *animation = new QPropertyAnimation(_transform, "rotation");
    QQuaternion startValue = _transform->rotation();
    QQuaternion endValue;
    switch (orientation) {
        case 1: //nord
            endValue = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 180.0f);
            break;
        case 2: //est
            endValue = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 90.0f);
            break;
        case 3: //sud
            endValue = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 0.0f);
            break;
        case 4: //ouest
            endValue = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 270.0f);
            break;
    }
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->setDuration(1000);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    QObject::connect(animation, &QPropertyAnimation::finished, [this](){
        initBounceAnimation();
        startBounceAnimation();
    });
}

void Zappy::GUI::PlayerEntity::animIncantation()
{
    while (_inMouvement);
    stopAnimation();
    _incantationAnim = new QPropertyAnimation(_transform, "rotation");
    _incantationAnim->setStartValue(_transform->rotation());
    _incantationAnim->setKeyValueAt(0.5, QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 180.0f));
    _incantationAnim->setEndValue(QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 180.0f));
    _incantationAnim->setDuration(500);
    _incantationAnim->start(QAbstractAnimation::DeleteWhenStopped);
    _incantationAnim->setLoopCount(-1);

    QObject::connect(_incantationAnim, &QPropertyAnimation::finished, [this](){
        initBounceAnimation();
        startBounceAnimation();
    });
}

void Zappy::GUI::PlayerEntity::stopIncantation()
{
    if (_incantationAnim) {
        _incantationAnim->stop();
        _incantationAnim = nullptr;
    }
}

void Zappy::GUI::PlayerEntity::startBounceAnimation()
{
    _floatingAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Zappy::GUI::PlayerEntity::stopAnimation()
{
    if (_floatingAnimation) {
        _floatingAnimation->stop();
        _floatingAnimation = nullptr;
    }
}

void Zappy::GUI::PlayerEntity::changePlayerTexture(bool isSelected)
{
if (isSelected)
    _materialTex->setTexture(_playerSelectedTexture);
else
    _materialTex->setTexture(_playerTexture);
}

int Zappy::GUI::PlayerEntity::getId() const { return _id; }

void Zappy::GUI::PlayerEntity::loadOBJ()
{
    _material = new Qt3DExtras::QPhongMaterial();
    _transform = new Qt3DCore::QTransform();
    _transform->setScale(0.020f);

    _materialTex = new Qt3DExtras::QTextureMaterial();
    _materialTex->setTexture(_playerTexture);

    addComponent(_materialTex);
    addComponent(_playerMesh);
    addComponent(_transform);
    changePlayerTexture(true);
    changePlayerTexture(false);
}

Qt3DRender::QTexture2D *Zappy::GUI::PlayerEntity::createTexture(const QString &path)
{
    Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D();
    Qt3DRender::QTextureImage *textureImage = new Qt3DRender::QTextureImage();
    textureImage->setSource(QUrl::fromLocalFile(path));
    texture->addTextureImage(textureImage);
    return texture;
}

Qt3DRender::QMesh *Zappy::GUI::PlayerEntity::createMesh(const QString &path)
{
    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
    mesh->setSource(QUrl::fromLocalFile(path));
    return mesh;
}
