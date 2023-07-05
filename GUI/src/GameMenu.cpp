/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameMenu
*/

#include "GameMenu.hpp"
#include <QMessageBox>
#include "Client.hpp"
#include <QDir>
#include <QMediaPlaylist>

Zappy::GUI::GameMenu::GameMenu(QWidget *parent): QMainWindow(parent)
{
    _ui = new Ui::MainMenu();
    _ui->setupUi(this);

    QObject::connect(_ui->exit, &QPushButton::clicked, this, &GameMenu::exitClicked);
    QObject::connect(_ui->start, &QPushButton::clicked, this, &GameMenu::startClicked);
    QObject::connect(_ui->settings, &QPushButton::clicked, this, &GameMenu::settingClicked);
    QObject::connect(_escapeKey, &QShortcut::activated, this, &GameMenu::escapeClicked);

    _stackedWidget = new QStackedWidget(this);
    _stackedWidget->addWidget(_ui->centralWidget);
    _stackedWidget->setCurrentWidget(_ui->centralWidget);

    _connexionMenu = new Zappy::GUI::ConnexionMenu(this);
    QObject::connect(_connexionMenu->_uiConnexionMenu->start, &QPushButton::clicked, this, &GameMenu::startGameClicked);
    _stackedWidget->addWidget(_connexionMenu);

    _settingMenu = new Zappy::GUI::SettingMenu(this);
    QPoint pos = _settingMenu->_uiSettingMenu->dial->pos();
    _settingMenu->_uiSettingMenu->dial->setValue(100);
    QObject::connect(_settingMenu->_uiSettingMenu->dial, &QDial::valueChanged, this, &GameMenu::changeVolume);
    _stackedWidget->addWidget(_settingMenu);


    setCentralWidget(_stackedWidget);

    _backgroundMusic = new QMediaPlayer(this);
    QDir dir = QDir::current();
    QString absolutePath = dir.absoluteFilePath("GUI/assets/music/violin.mp3");
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(absolutePath));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    _backgroundMusic->setPlaylist(playlist);
    _backgroundMusic->setVolume(100);
    _backgroundMusic->play();
}

Zappy::GUI::GameMenu::~GameMenu()
{
    delete _ui;
    delete _stackedWidget;
    delete _escapeKey;
}

void Zappy::GUI::GameMenu::exitClicked()
{
    QApplication::quit();
}

void Zappy::GUI::GameMenu::startClicked()
{
    _stackedWidget->setCurrentWidget(_connexionMenu);
}

void Zappy::GUI::GameMenu::settingClicked()
{
    _stackedWidget->setCurrentWidget(_settingMenu);
}

void Zappy::GUI::GameMenu::changeVolume(int value)
{
    _backgroundMusic->setVolume(value);
}

void Zappy::GUI::GameMenu::startGameClicked()
{
    QRegExp ipRegex("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$");
    QRegExp portRegex("^[0-9]+$");

    bool ok;
    int portNumber = _connexionMenu->_uiConnexionMenu->Port_edit->text().toInt(&ok);
    if (_connexionMenu->_uiConnexionMenu->IP_edit->text().isEmpty() || _connexionMenu->_uiConnexionMenu->Port_edit->text().isEmpty() ||
        !ipRegex.exactMatch(_connexionMenu->_uiConnexionMenu->IP_edit->text()) || !portRegex.exactMatch(_connexionMenu->_uiConnexionMenu->Port_edit->text()) ||
        !ok || portNumber < 0 || portNumber > 65535) {
        return;
    }
    if (_gameUI) {
        delete _gameUI;
        _gameUI = nullptr;
    }
    try {
        Client *client = new Client(_connexionMenu->_uiConnexionMenu->IP_edit->text(), portNumber);
        _gameUI = new Game3D(client, this);
        QObject::connect(_gameUI->_client, &Client::endOfGame, this, &GameMenu::escapeClicked);
        QObject::connect(_gameUI, &Game3D::endOfGame, this, &GameMenu::escapeClicked);
        _stackedWidget->addWidget(_gameUI);
        _stackedWidget->setCurrentWidget(_gameUI);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Connexion failed", "Connexion Failed\nPort: " + QString::number(portNumber) + ", IP: " + _connexionMenu->_uiConnexionMenu->IP_edit->text());
        _stackedWidget->setCurrentWidget(_ui->centralWidget);
    }
}


void Zappy::GUI::GameMenu::escapeClicked()
{
    if (_gameUI) {
        _stackedWidget->setCurrentWidget(_ui->centralWidget);
        _stackedWidget->removeWidget(_gameUI);
    }
    if (_connexionMenu) {
        _stackedWidget->setCurrentWidget(_ui->centralWidget);
    }
}
