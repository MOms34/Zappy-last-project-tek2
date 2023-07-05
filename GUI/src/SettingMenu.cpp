/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** SettingMenu
*/

#include "SettingMenu.hpp"

Zappy::GUI::SettingMenu::SettingMenu(QWidget *parent) : QWidget(parent)
{
    _uiSettingMenu = new Ui::SettingMenu();
    _uiSettingMenu->setupUi(this);
    parent->setObjectName(QString::fromUtf8("SettingMenu"));
    parent->setStyleSheet(QString::fromUtf8("#SettingMenu {\n"
    "    border-image: url(\"/home/omay/delivery/Tech2/Semestre_1/Zappy/B-YEP-400-MPL-4-1-zappy-gaetan.darrort/GUI/assets/menu/background.png\") 0 0 0 0 stretch stretch;\n"
    "}\n"
    ""));
};