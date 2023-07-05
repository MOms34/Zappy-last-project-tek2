/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Player
*/

#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QSceneLoader>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DAnimation/QAnimationClipLoader>
#include <Qt3DAnimation/QClipAnimator>
#include <Qt3DAnimation/QChannelMapping>
#include <Qt3DAnimation/QChannelMapper>
#include <Qt3DAnimation/QAbstractAnimation>
#include <QPropertyAnimation>
#include <iostream>
#include <QParallelAnimationGroup>

namespace Zappy {
    namespace GUI {
        class EggEntity : public Qt3DCore::QEntity
        {
        Q_OBJECT
        public:
            EggEntity(int id, int skinId, Qt3DCore::QNode *parent = nullptr);
            void changeEggTexture(bool isConnected);
        protected:
            void loadOBJ();
            Qt3DRender::QTexture2D *createTexture(const QString &path);
            Qt3DRender::QMesh *createMesh(const QString &path);
            int getId() const;
        private:
            Qt3DRender::QMesh *_mesh;
            Qt3DExtras::QPhongMaterial *_material;
            Qt3DCore::QTransform *_transform;
            Qt3DRender::QTexture2D *_eggTexture;
            Qt3DRender::QTexture2D *_eggConnectedTexture;
            Qt3DRender::QMesh *_eggMesh;
            Qt3DExtras::QTextureMaterial *_materialTex;
            int _id;
        };
    }
}