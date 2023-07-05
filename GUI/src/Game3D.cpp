/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game3D
*/

#include "Game3D.hpp"
#include "PlayerEntity.hpp"
#include <Qt3DRender/QBuffer>
#include "Client.hpp"
#include <QPropertyAnimation>
#include <QPropertyAnimation>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DRender/QTexture>

Zappy::GUI::Game3D::Game3D(Client *client, QWidget *parent) : QWidget(parent), _view(new Qt3DWidget(this)), _client(client)
{
    _view->defaultFrameGraph()->setClearColor(QColor("#000000"));
    _rootEntity = new Qt3DCore::QEntity();

    Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D(_rootEntity);
    Qt3DRender::QTextureImage *textureImage = new Qt3DRender::QTextureImage();
    textureImage->setSource(QUrl::fromLocalFile("GUI/assets/3D/sky.png")); // Mettez ici le chemin vers l'image que vous voulez utiliser comme texture
    texture->addTextureImage(textureImage);

    Qt3DExtras::QTextureMaterial *material = new Qt3DExtras::QTextureMaterial();
    material->setTexture(texture);

    Qt3DExtras::QPlaneMesh *planeMesh = new Qt3DExtras::QPlaneMesh();
    planeMesh->setWidth(1000); // Ajustez ces valeurs en fonction de la taille que vous voulez pour le fond
    planeMesh->setHeight(1000);

    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
    transform->setRotationX(90.0f); // Orienter le plan pour qu'il serve de fond
    transform->setTranslation(QVector3D(0, 0, -50));
    Qt3DCore::QEntity *background = new Qt3DCore::QEntity(_rootEntity);
    background->addComponent(planeMesh);
    background->addComponent(material);
    background->addComponent(transform);


    setLight(QVector3D(0, 0, 100.0f));
    setLight(QVector3D(0, 100.0f, 0));
    setLight(QVector3D(100.0f, 0, 0));
    setLight(QVector3D(0, 0, -100.0f));
    setLight(QVector3D(0, -100.0f, 0));
    setLight(QVector3D(-100.0f, 0, 0));

    setCamera();
    _view->setRootEntity(_rootEntity);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(_view);

    _resourceHUD = new Zappy::GUI::ResourceHUD(_view);
    _playerHUD = new Zappy::GUI::PlayerHUD(_view);
    _teamHUD = new Zappy::GUI::TeamHUD(_view);
    // Dans le constructeur de Game3D :
    _leftShortcut = new QShortcut(QKeySequence(Qt::Key_Left), this);
    connect(_leftShortcut, &QShortcut::activated, this, &Game3D::moveCameraLeft);

    _rightShortcut = new QShortcut(QKeySequence(Qt::Key_Right), this);
    connect(_rightShortcut, &QShortcut::activated, this, &Game3D::moveCameraRight);

    _upShortcut = new QShortcut(QKeySequence(Qt::Key_Up), this);
    connect(_upShortcut, &QShortcut::activated, this, &Game3D::moveCameraUp);

    _downShortcut = new QShortcut(QKeySequence(Qt::Key_Down), this);
    connect(_downShortcut, &QShortcut::activated, this, &Game3D::moveCameraDown);
    QObject::connect(_client, &Client::teamAdded, this, &Game3D::addTeam);
    QObject::connect(_client, &Client::initializationReceived, this, &Game3D::handleInitialization);
}

Zappy::GUI::Game3D::~Game3D()
{
    delete _client;
    delete _gameMap;
}

std::pair<float, float> Zappy::GUI::Game3D::getCellCoordinates(float x, float y)
{
    CellEntity *cell = _gameMap->getCells()[std::make_pair(x, y)];
    if (cell) {
        Qt3DCore::QTransform *transform = cell->findChild<Qt3DCore::QTransform*>();
        if (transform) {
            QVector3D position = transform->translation();
            return std::make_pair(position.x(), position.y());
        }
    }
    return std::make_pair(0, 0);
}

void Zappy::GUI::Game3D::setPlayerRotation(PlayerEntity *player, int orientation)
{
    Qt3DCore::QTransform *transform = player->findChild<Qt3DCore::QTransform *>();

    float rotationAngle = 0.0f;
    switch (orientation) {
        case 1: //nord
            rotationAngle = 180.0f;
            break;
        case 2: //est
            rotationAngle = 90.0f;
            break;
        case 3: //sud
            rotationAngle = 0.0f;
            break;
        case 4: //ouest
            rotationAngle = 270.0f;
            break;
    }

    QQuaternion rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), rotationAngle);
    transform->setRotation(rotation);
}

void Zappy::GUI::Game3D::setPlayerRotation(int id, int orientation)
{
    setPlayerRotation(_players[id], orientation);
}

void Zappy::GUI::Game3D::startPlayerAnimation(int id)
{
    _players[id]->startBounceAnimation();
}

void Zappy::GUI::Game3D::addPlayer(int playerId)
{
    if (_client->_clientData.getPlayers().find(playerId) == _client->_clientData.getPlayers().end()) {
        std::cerr << "Player added before start GUI" << std::endl;
        emit endOfGame();
        return;
    }
    PlayerData playerData = _client->_clientData.getPlayer(playerId);
    PlayerEntity* player = new PlayerEntity(playerId, _teams[playerData._teamName], _rootEntity);
    Qt3DRender::QObjectPicker *picker = new Qt3DRender::QObjectPicker(player);
    connect(picker, &Qt3DRender::QObjectPicker::clicked, this, &Game3D::playerPick);
    player->addComponent(picker);

    Qt3DCore::QTransform *transform = player->findChild<Qt3DCore::QTransform *>();
    std::pair<float, float> cellPosition = getCellCoordinates(playerData._x, playerData._y);
    transform->setTranslation(QVector3D(cellPosition.first, cellPosition.second, 0.5));
    setPlayerRotation(player, playerData._orientation);
    player->initBounceAnimation();
    player->startBounceAnimation();
    _players[playerData._id] = player;
}

void Zappy::GUI::Game3D::addEgg(int eggId, int playerId)
{
    PlayerData playerData = _client->_clientData.getPlayer(playerId);
    EggData eggData = _client->_clientData.getEgg(eggId);
    EggEntity* egg = new EggEntity(eggId, _teams[playerData._teamName], _rootEntity);
    Qt3DRender::QObjectPicker *picker = new Qt3DRender::QObjectPicker(egg);
    connect(picker, &Qt3DRender::QObjectPicker::clicked, this, &Game3D::playerPick);
    egg->addComponent(picker);

    Qt3DCore::QTransform *transform = egg->findChild<Qt3DCore::QTransform *>();
    std::pair<float, float> cellPosition = getCellCoordinates(eggData._x, eggData._y);
    transform->setTranslation(QVector3D(cellPosition.first, cellPosition.second, 0.5));
    _eggs[eggData._id] = egg;
}

void Zappy::GUI::Game3D::eggReady(int eggId)
{
    _eggs[eggId]->changeEggTexture(true);
}

void Zappy::GUI::Game3D::eggKill(int eggId)
{
    delete _eggs[eggId];
    _players.erase(eggId);
}


void Zappy::GUI::Game3D::changePlayerPosition(int playerId)
{
    PlayerEntity* player = _players[playerId];
    PlayerData playerData = _client->_clientData.getPlayer(playerId);
    Qt3DCore::QTransform *transform = player->findChild<Qt3DCore::QTransform *>();
    std::pair<float, float> cellPosition = getCellCoordinates(playerData._x, playerData._y);

    if (player == _playerClicked) {
        _playerHUD->updatePlayerInfo(playerData);
        _client->sendMessage("pin " + QString::number(playerId) + "\n");
    }

    if (transform->translation().x() == cellPosition.first && transform->translation().y() == cellPosition.second) {
        player->animRotation(playerData._orientation);
        setPlayerRotation(player, playerData._orientation);
    } else {
        player->move(cellPosition.first, cellPosition.second);
    }
}

void Zappy::GUI::Game3D::playerStartIncantation(int playerId)
{
    PlayerEntity* player = _players[playerId];
    if (player)
        player->animIncantation();
    else {
        std::cerr << "Player " << playerId << " does not exist" << std::endl;
    }
}

void Zappy::GUI::Game3D::moveCameraLeft()
{
    Qt3DRender::QCamera *camera = _view->camera();
    QVector3D position = camera->position();
    position.setX(position.x() - 1);
    camera->setPosition(position);
    camera->setViewCenter(QVector3D(0, 0, 0));
}

void Zappy::GUI::Game3D::moveCameraRight()
{
    Qt3DRender::QCamera *camera = _view->camera();
    QVector3D position = camera->position();
    position.setX(position.x() + 1);
    camera->setPosition(position);
    camera->setViewCenter(QVector3D(0, 0, 0));
}

void Zappy::GUI::Game3D::moveCameraUp()
{
    Qt3DRender::QCamera *camera = _view->camera();
    QVector3D position = camera->position();
    position.setZ(position.z() + 1);
    camera->setPosition(position);
}

void Zappy::GUI::Game3D::moveCameraDown()
{
    Qt3DRender::QCamera *camera = _view->camera();
    QVector3D position = camera->position();
    position.setZ(position.z() - 1);
    camera->setPosition(position);
}

void Zappy::GUI::Game3D::playerStopIncantation(int x, int y)
{
    std::map<int, PlayerData> players = _client->_clientData.getPlayers();
    for (auto &player : players) {
        if (player.second._x == x && player.second._y == y)
            _players[player.first]->stopIncantation();
    }
}

void Zappy::GUI::Game3D::playerKill(int playerId)
{
    if (_players[playerId] == _playerClicked) {
        _playerHUD->clear();
    }
    delete _players[playerId];
    _players.erase(playerId);
}

void Zappy::GUI::Game3D::updatePlayerInventory(int playerId)
{
    PlayerEntity* player = _players[playerId];
    PlayerData playerData = _client->_clientData.getPlayer(playerId);

    if (player == _playerClicked) {
        _playerHUD->updatePlayerInfo(playerData);
    }
}

void Zappy::GUI::Game3D::playerPick(Qt3DRender::QPickEvent *event)
{
    if (_playerClicked) {
        _playerClicked->changePlayerTexture(false);
    }
    Qt3DCore::QEntity *entity = qobject_cast<Qt3DCore::QEntity *>(event->entity());
    PlayerEntity *newClickedEntity = qobject_cast<PlayerEntity*>(entity);
    if (newClickedEntity) {
        if (_playerClicked == newClickedEntity) {
            _playerClicked->changePlayerTexture(false);
            _playerClicked = nullptr;
            _playerHUD->clear();
        } else {
            newClickedEntity->changePlayerTexture(true);
            _playerClicked = newClickedEntity;
            _client->sendMessage("pin " + QString::number(newClickedEntity->getId()) + "\n");
        }
    }
}

void Zappy::GUI::Game3D::setCamera()
{
    Qt3DRender::QCamera *camera = _view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0.0f, -14.0f, 7.5f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(_rootEntity);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 200.0f );
    camController->setCamera(camera);
}

void Zappy::GUI::Game3D::setLight(QVector3D position)
{
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(_rootEntity);
    Qt3DRender::QSpotLight *light = new Qt3DRender::QSpotLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    light->setCutOffAngle(180.0f);

    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(position);
    lightTransform->setRotationX(90);

    lightEntity->addComponent(light);
    lightEntity->addComponent(lightTransform);
}

void Zappy::GUI::Game3D::addTeam(std::string teamName)
{
    _teams[teamName] = _teams.size() + 1;
    _teamHUD->updateTeamsInfo(_teams);
}

void Zappy::GUI::Game3D::handleInitialization()
{
    std::pair<int, int> mapSize = _client->getMapSize();
    _gameMap = new Zappy::GUI::GameMap(mapSize.first, mapSize.second, _resourceHUD, _client, _rootEntity);
    QObject::connect(_client, &Client::newPlayerAdded, this, &Game3D::addPlayer);
    QObject::connect(_client, &Client::playerPositionChanged, this, &Game3D::changePlayerPosition);
    QObject::connect(_client, &Client::playerInventoryReceived, this, &Game3D::updatePlayerInventory);
    QObject::connect(_client, &Client::playerKilled, this, &Game3D::playerKill);
    QObject::connect(_client, &Client::playerIncantationStarted, this, &Game3D::playerStartIncantation);
    QObject::connect(_client, &Client::playerIncantationStoped, this, &Game3D::playerStopIncantation);
    QObject::connect(_client, &Client::newEggAdded, this, &Game3D::addEgg);
    QObject::connect(_client, &Client::eggIsReady, this, &Game3D::eggReady);
    QObject::connect(_client, &Client::eggKilled, this, &Game3D::eggKill);
}
