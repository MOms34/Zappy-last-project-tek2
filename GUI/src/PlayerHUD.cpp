/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** PlayerHUD
*/

#include "PlayerHUD.hpp"

Zappy::GUI::PlayerHUD::PlayerHUD(QWidget *parent) : QWidget(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255, 127));
    this->setPalette(palette);
    this->setAutoFillBackground(false);

    int hudWidth = 300;
    int hudHeight = 350;

    int hudX = 1920 - hudWidth;
    int hudY = 0;

    this->setGeometry(hudX, hudY, hudWidth, hudHeight);

    _layout = new QVBoxLayout(this);
    _playerLabel = new QLabel(this);
    _playerLabel->setAlignment(Qt::AlignTop);
    QFont font = _playerLabel->font();
    font.setPointSize(14);
    _playerLabel->setFont(font);
    _layout->addWidget(_playerLabel);
}

void Zappy::GUI::PlayerHUD::clear()
{
    this->setAutoFillBackground(false);
    _playerLabel->clear();
}

void Zappy::GUI::PlayerHUD::updatePlayerInfo(PlayerData playerData)
{
    this->setAutoFillBackground(true);
    _playerLabel->clear();
    _playerLabel->setText(_playerLabel->text() + "<font color='black'>Player: " + QString::number(playerData._id) + " | Team:  " + QString::fromStdString(playerData._teamName) + "</font><br>");
    _playerLabel->setText(_playerLabel->text() + "-----------------------------------------------<br>");
    _playerLabel->setText(_playerLabel->text() + "<font color='black'>Position: " + QString::number(playerData._x) + " | " + QString::number(playerData._y) + "</font><br>");
    _playerLabel->setText(_playerLabel->text() + "<font color='black'>Level: " + QString::number(playerData._level) + "</font><br>");
    _playerLabel->setText(_playerLabel->text() + "Inventory: <br>");
    _playerLabel->setText(_playerLabel->text() + "<br>" + "Food: " + QString::number(playerData._inventory._food));
    _playerLabel->setText(_playerLabel->text() + "<br><font color='blue'>" + "Linemate<font color='black'>: " + QString::number(playerData._inventory._linemate));
    _playerLabel->setText(_playerLabel->text() + "<br><font color='green'>" + "Deraumere<font color='black'>: " + QString::number(playerData._inventory._deraumere));
    _playerLabel->setText(_playerLabel->text() + "<br><font color='red'>" + "Sibur<font color='black'>: " + QString::number(playerData._inventory._sibur));
    _playerLabel->setText(_playerLabel->text() + "<br><font color='purple'>" + "Mendiane<font color='black'>: " + QString::number(playerData._inventory._mendiane));
    _playerLabel->setText(_playerLabel->text() + "<br><font color='white'>" + "Phiras<font color='black'>: " + QString::number(playerData._inventory._phiras));
    _playerLabel->setText(_playerLabel->text() + "<br><font color='yellow'>" + "Thystame<font color='black'>: " + QString::number(playerData._inventory._thystame));
}

