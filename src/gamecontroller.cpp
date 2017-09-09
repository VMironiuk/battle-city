#include "gamecontroller.h"

#include "collider.h"

static const int TIMEOUT = 25;

GameController &GameController::instance()
{
    static GameController gc;
    return gc;
}

GameController::GameController(QObject *parent)
    : QObject(parent)
{
    Collider::instance().setBoard(&board_);

    connect(&timer_, SIGNAL(timeout()), &board_, SLOT(update()));
    timer_.start(TIMEOUT);
}

GameController::~GameController()
{
}
