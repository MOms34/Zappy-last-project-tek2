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
        class PlayerHUD : public QWidget {
            Q_OBJECT
        public:
            explicit PlayerHUD(QWidget *parent = nullptr);

            void clear();
            void updatePlayerInfo(PlayerData playerData);

        private:
            QVBoxLayout *_layout;
            QLabel *_playerLabel;
        };
    };
}
