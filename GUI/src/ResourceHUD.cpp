/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ResourceHUD
*/

#include "HUDs.hpp"

Zappy::GUI::ResourceHUD::ResourceHUD(QWidget *parent) : QWidget(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255, 127));
    this->setPalette(palette);
    this->setAutoFillBackground(false);
    this->setGeometry(0, 0, 160, 160);

    _layout = new QVBoxLayout(this);
    _resourceLabel = new QLabel(this);
    _layout->addWidget(_resourceLabel);
}

void Zappy::GUI::ResourceHUD::clear()
{
    this->setAutoFillBackground(false);
    _resourceLabel->clear();
}

void Zappy::GUI::ResourceHUD::updateResources(const std::vector<Zappy::GUI::ResourceType>& resources, std::pair<int, int> cellIndex)
{
    this->setAutoFillBackground(true);
    _resourceLabel->clear();
    _resourceLabel->setText(_resourceLabel->text() + "<font color='black'>           CELL " + QString::number(cellIndex.first) + " | " + QString::number(cellIndex.second) + "</font>");
    _resourceLabel->setText(_resourceLabel->text() + "<br><font color='black'>" + resourceTypeToString(Zappy::GUI::ResourceType::Food) + "<font color='black'>: " + QString::number(resourceCount(resources, Zappy::GUI::ResourceType::Food)));
    _resourceLabel->setText(_resourceLabel->text() + "<br><font color='blue'>" + resourceTypeToString(Zappy::GUI::ResourceType::Linemate) + "<font color='black'>: " + QString::number(resourceCount(resources, Zappy::GUI::ResourceType::Linemate)));
    _resourceLabel->setText(_resourceLabel->text() + "<br><font color='green'>" + resourceTypeToString(Zappy::GUI::ResourceType::Deraumere) + "<font color='black'>: " + QString::number(resourceCount(resources, Zappy::GUI::ResourceType::Deraumere)));
    _resourceLabel->setText(_resourceLabel->text() + "<br><font color='red'>" + resourceTypeToString(Zappy::GUI::ResourceType::Sibur) + "<font color='black'>: " + QString::number(resourceCount(resources, Zappy::GUI::ResourceType::Sibur)));
    _resourceLabel->setText(_resourceLabel->text() + "<br><font color='purple'>" + resourceTypeToString(Zappy::GUI::ResourceType::Mendiane) + "<font color='black'>: " + QString::number(resourceCount(resources, Zappy::GUI::ResourceType::Mendiane)));
    _resourceLabel->setText(_resourceLabel->text() + "<br><font color='white'>" + resourceTypeToString(Zappy::GUI::ResourceType::Phiras) + "<font color='black'>: " + QString::number(resourceCount(resources, Zappy::GUI::ResourceType::Phiras)));
    _resourceLabel->setText(_resourceLabel->text() + "<br><font color='yellow'>" + resourceTypeToString(Zappy::GUI::ResourceType::Thystame) + "<font color='black'>: " + QString::number(resourceCount(resources, Zappy::GUI::ResourceType::Thystame)));
}


int Zappy::GUI::ResourceHUD::resourceCount(const std::vector<Zappy::GUI::ResourceType>& resources, Zappy::GUI::ResourceType type)
{
    int count = 0;
    for (Zappy::GUI::ResourceType resource : resources)
        if (resource == type)
            ++count;
    return count;
}

QString Zappy::GUI::ResourceHUD::resourceTypeToString(const Zappy::GUI::ResourceType& resourceType)
{
    switch (resourceType) {
        case Zappy::GUI::ResourceType::Food:
            return "Food";
        case Zappy::GUI::ResourceType::Linemate:
            return "Linemate";
        case Zappy::GUI::ResourceType::Deraumere:
            return "Deraumere";
        case Zappy::GUI::ResourceType::Sibur:
            return "Sibur";
        case Zappy::GUI::ResourceType::Mendiane:
            return "Mendiane";
        case Zappy::GUI::ResourceType::Phiras:
            return "Phiras";
        case Zappy::GUI::ResourceType::Thystame:
            return "Thystame";
        default:
            return "???";
    }
}