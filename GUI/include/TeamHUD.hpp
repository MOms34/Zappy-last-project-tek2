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

namespace Zappy {
    namespace GUI {
        class TeamHUD : public QWidget {
            Q_OBJECT
        public:
            explicit TeamHUD(QWidget *parent = nullptr);
            void updateTeamsInfo(std::map<std::string, int> teams);

        private:
            QVBoxLayout *_layout;
            QLabel *_playerLabel;
            std::map<int, QString> _mapColor;
        };
    }
}
