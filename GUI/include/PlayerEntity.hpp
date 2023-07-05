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
        class PlayerEntity : public Qt3DCore::QEntity
        {
        Q_OBJECT
        public:
            PlayerEntity(int id, int skinId, Qt3DCore::QNode *parent = nullptr);
            void initBounceAnimation();
            void move(float x, float y);
            void animRotation(int orientation);
            void animIncantation();
            void stopIncantation();
            void startBounceAnimation();
            void stopAnimation();
        void changePlayerTexture(bool isSelected);
        int getId() const;
        protected:
            void loadOBJ();
            Qt3DRender::QTexture2D *createTexture(const QString &path);
            Qt3DRender::QMesh *createMesh(const QString &path);
        private:
            Qt3DRender::QMesh *_mesh;
            Qt3DExtras::QPhongMaterial *_material;
            Qt3DCore::QTransform *_transform;
            Qt3DRender::QTexture2D *_playerTexture;
            Qt3DRender::QTexture2D *_playerSelectedTexture;
            Qt3DRender::QMesh *_playerMesh;
            int _id;
            QPropertyAnimation *_floatingAnimation;
            Qt3DExtras::QTextureMaterial *_materialTex;
            QPropertyAnimation *_incantationAnim = nullptr;
            bool _inMouvement = false;
        };
    }
}