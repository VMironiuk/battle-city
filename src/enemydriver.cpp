#include "enemydriver.h"

#include <QDebug>

#include "global.h"

static const int RANDOM_MOVEMENT_PERIOD = 30000;
static const int TO_PLAYER_MOVEMENT_PERIOD = RANDOM_MOVEMENT_PERIOD * 2;
static const int TO_EAGLE_MOVEMENT_PERIOD = RANDOM_MOVEMENT_PERIOD * 3;

EnemyDriver::EnemyDriver(ShootableItem *tank, QObject *parent)
    : QObject(parent),
      tank_(tank)
{
    tank_->setMovement(true);
    tank_->setShooting(true);
    tank_->setDirection(MovableItem::South);

    previousTankPositionX_ = tank_->x();
    previousTankPositionY_ = tank_->y();

    connect(tank_, SIGNAL(destroyed(QObject*)), this, SIGNAL(wannaDie()));

    movementPeriodTime_.start();
}

void EnemyDriver::update()
{
    if (movementPeriodTime_.elapsed() < RANDOM_MOVEMENT_PERIOD) {
        moveRandomly();
    } else if (movementPeriodTime_.elapsed() > RANDOM_MOVEMENT_PERIOD
               && movementPeriodTime_.elapsed() < TO_PLAYER_MOVEMENT_PERIOD) {
        moveToPlayer();
    } else {
        moveToEagle();
        movementPeriodTime_.restart();
    }

    switch (tank_->direction()) {
    case MovableItem::North:
        if (previousTankPositionY_ == tank_->y()) {
            int direction = randomNumber(1, 4);
            if (static_cast<int>(MovableItem::North != direction))
                tank_->setDirection(static_cast<MovableItem::Direction>(direction));
            else
                tank_->setDirection(MovableItem::South);
        }
        break;
    case MovableItem::South:
        if (previousTankPositionY_ == tank_->y()) {
            int direction = randomNumber(1, 4);
            if (static_cast<int>(MovableItem::South != direction))
                tank_->setDirection(static_cast<MovableItem::Direction>(direction));
            else
                tank_->setDirection(MovableItem::North);
        }
        break;
    case MovableItem::West:
        if (previousTankPositionX_ == tank_->x()) {
            int direction = randomNumber(1, 4);
            if (static_cast<int>(MovableItem::West != direction))
                tank_->setDirection(static_cast<MovableItem::Direction>(direction));
            else
                tank_->setDirection(MovableItem::East);
        }
        break;
    case MovableItem::East:
        if (previousTankPositionX_ == tank_->x()) {
            int direction = randomNumber(1, 4);
            if (static_cast<int>(MovableItem::East != direction))
                tank_->setDirection(static_cast<MovableItem::Direction>(direction));
            else
                tank_->setDirection(MovableItem::West);
        }
        break;
    default:
        break;
    }

    previousTankPositionX_ = tank_->x();
    previousTankPositionY_ = tank_->y();
}

void EnemyDriver::moveRandomly()
{
    int direction = randomNumber(1, 100);
    if (direction <= 4)
        tank_->setDirection(static_cast<MovableItem::Direction>(direction));
}

void EnemyDriver::moveToPlayer()
{
    // TODO: add implementation
    qDebug() << Q_FUNC_INFO;
}

void EnemyDriver::moveToEagle()
{
    // TODO: add implementation
    qDebug() << Q_FUNC_INFO;
}
