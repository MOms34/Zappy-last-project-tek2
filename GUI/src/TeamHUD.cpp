/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort
** File description:
** TeamHUD
*/

#include "TeamHUD.hpp"


Zappy::GUI::TeamHUD::TeamHUD(QWidget *parent) : QWidget(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255, 127));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
    _mapColor;
    _mapColor[1] = "<font color='red'>";
    _mapColor[2] = "<font color='yellow'>";
    _mapColor[3] = "<font color='blue'>";
    _mapColor[4] = "<font color='green'>";

    int hudWidth = 170;
    int hudHeight = 120;

    int hudX = 1920 / 2 - 60;
    int hudY = 0;

    this->setGeometry(hudX, hudY, hudWidth, hudHeight);

    _layout = new QVBoxLayout(this);
    _playerLabel = new QLabel(this);
    _playerLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    QFont font = _playerLabel->font();
    font.setPointSize(14);
    _playerLabel->setFont(font);
    _layout->addWidget(_playerLabel);
}

void Zappy::GUI::TeamHUD::updateTeamsInfo(std::map<std::string, int> teams)
{
    this->setAutoFillBackground(true);
    _playerLabel->clear();
    for (auto &team : teams) {
        int colorIndex = team.second;
        if (colorIndex < 1 || colorIndex > 4) {
            colorIndex = 1;
        }
        _playerLabel->setText(_playerLabel->text() + _mapColor[colorIndex] + QString::fromStdString(team.first) + "</font><br>");
    }
}
