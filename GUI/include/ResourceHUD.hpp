/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ResourceHUD
*/

#pragma once

#include "ResourceEntity.hpp"
#include <QLabel>
#include <QVBoxLayout>
#include "ClientData.hpp"

namespace Zappy {
    namespace GUI {
        class ResourceHUD : public QWidget {
            Q_OBJECT
        public:
            explicit ResourceHUD(QWidget *parent = nullptr);

            void clear();
            int resourceCount(const std::vector<Zappy::GUI::ResourceType>& resources, Zappy::GUI::ResourceType type);
            void updateResources(const std::vector<Zappy::GUI::ResourceType>& resources, std::pair<int, int> cellIndex);

        protected:
            QString resourceTypeToString(const Zappy::GUI::ResourceType& resourceType);

        private:
            QVBoxLayout *_layout;
            QLabel *_resourceLabel;
        };
    }
}
