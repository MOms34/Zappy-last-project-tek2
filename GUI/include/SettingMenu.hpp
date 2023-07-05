/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** SettingMenu
*/

#pragma once

#include <QWidget>
#include "ui_setting_menu.h"
#include <QObject>

namespace Zappy {
    namespace GUI {
        class SettingMenu : public QWidget
        {
            Q_OBJECT
        public:

            SettingMenu(QWidget *parent = nullptr);

            Ui::SettingMenu *_uiSettingMenu;
        };
    }
}