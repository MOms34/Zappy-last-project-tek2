/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** ConnexionMenu
*/

#include "ConnexionMenu.hpp"

Zappy::GUI::ConnexionMenu::ConnexionMenu(QWidget *parent) : QWidget(parent)
{
    _uiConnexionMenu = new Ui::ConnexionMenu();
    _uiConnexionMenu->setupUi(this);
    parent->setObjectName(QString::fromUtf8("ConnexionMenu"));
    parent->setStyleSheet(QString::fromUtf8("#ConnexionMenu {\n"
    "    border-image: url(\"/home/omay/delivery/Tech2/Semestre_1/Zappy/B-YEP-400-MPL-4-1-zappy-gaetan.darrort/GUI/assets/menu/background.png\") 0 0 0 0 stretch stretch;\n"
    "}\n"
    ""));
};