#include "gamecontroller.h"

static const int TIMEOUT = 25;

GameController &GameController::instance()
{
    static GameController gc;
    return gc;
}

void GameController::checkCollisions()
{
    collider_.checkCollisions(&board_);
}

GameController::GameController(QObject *parent)
    : QObject(parent)
{
    connect(&timer_, SIGNAL(timeout()), &board_, SLOT(update()));
    connect(&timer_, SIGNAL(timeout()), this, SLOT(checkCollisions()));
    timer_.start(TIMEOUT);
}

GameController::~GameController()
{
}
