/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** main
*/

#include "GameMenu.hpp"
#include <QApplication>
#include <iostream>

int main(int ac, char **av)
{
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSamples(4);
    format.setVersion(3, 0);
    QSurfaceFormat::setDefaultFormat(format);
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QApplication app(ac, av);
    Zappy::GUI::GameMenu gameMenu;
    gameMenu.show();
    return app.exec();
}