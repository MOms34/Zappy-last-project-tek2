/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameMenu
*/

#pragma once

#include "Game3D.hpp"
#include "ui_main_menu.h"
#include "ConnexionMenu.hpp"
#include "SettingMenu.hpp"
#include <QMainWindow>
#include <QStackedWidget>
#include <QShortcut>
#include <QMediaPlayer>

namespace Zappy {
    namespace GUI {
        class GameMenu : public QMainWindow
        {
            Q_OBJECT

            public:
                GameMenu(QWidget *parent = nullptr);
                ~GameMenu();

            private slots:
                void exitClicked();
                void startClicked();
                void settingClicked();
                void changeVolume(int value);
                void escapeClicked();
                void startGameClicked();

            private:
                Ui::MainMenu *_ui;
                Zappy::GUI::ConnexionMenu *_connexionMenu;
                Zappy::GUI::SettingMenu *_settingMenu;
                QStackedWidget *_stackedWidget;
                Game3D *_gameUI;
                QShortcut *_escapeKey = new QShortcut(QKeySequence(Qt::Key_Escape), this);
                QMediaPlayer* _backgroundMusic;
        };
    }
}