/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ResourceEntity
*/

#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QTexture>
#include <Qt3DExtras/QPhongMaterial>
#include <QPropertyAnimation>

namespace Zappy {
    namespace GUI {
        enum ResourceType {
            Food,
            Linemate, //Bleu
            Deraumere, //Vert
            Sibur, //Rouge
            Mendiane, //Violet
            Phiras, // Argent
            Thystame, // Jaune
        };

        class ResourceEntity : public Qt3DCore::QEntity
        {
            Q_OBJECT
        public:
            ResourceEntity(const ResourceType &resource, Qt3DCore::QNode *parent = nullptr);
            ResourceType resource() const;
            Qt3DRender::QTexture2D *createTexture(const QString &path);
            Qt3DRender::QMesh *createMesh(const QString &path);
            void removeResource();

        signals:
            void stop(ResourceEntity* entity);
        protected:
            void loadOBJ();
        private:
            ResourceType _resource;
            Qt3DRender::QMesh *_mesh;
            Qt3DExtras::QPhongMaterial *_material;
            Qt3DCore::QTransform *_transform;
            Qt3DRender::QTexture2D *_colaTexture;
            Qt3DRender::QMesh *_colaMesh;
            Qt3DRender::QMesh *_diamondMesh;
        };
    }
}