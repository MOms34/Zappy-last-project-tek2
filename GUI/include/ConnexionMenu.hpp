/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** ConnexionMenu
*/

#pragma once

#include <QWidget>
#include "ui_connexion_menu.h"
#include <QObject>

namespace Zappy {
    namespace GUI {
        class ConnexionMenu : public QWidget
        {
            Q_OBJECT
        public:

            ConnexionMenu(QWidget *parent = nullptr);

            Ui::ConnexionMenu *_uiConnexionMenu;
        };
    }
}