#include "enemydriver.h"

#include <QDebug>

#include "functions.h"

static const int RANDOM_MOVEMENT_PERIOD = 30000;
static const int TO_PLAYER_MOVEMENT_PERIOD = RANDOM_MOVEMENT_PERIOD * 2;
static const int TO_EAGLE_MOVEMENT_PERIOD = RANDOM_MOVEMENT_PERIOD * 3;

namespace Controller {

EnemyDriver::EnemyDriver(Base::ShootableItem *tank, QObject *parent)
    : QObject(parent),
      tank_(tank)
{
    if (tank_ == nullptr)
        return;

    tank_->setMovement(true);
    tank_->setShooting(true);
    tank_->setDirection(Base::MovableItem::South);

    previousTankPositionX_ = tank_->x();
    previousTankPositionY_ = tank_->y();

    connect(tank_, SIGNAL(destroyed(QObject*)), this, SIGNAL(wannaDie()));

    movementPeriodTime_.start();
}

void EnemyDriver::update()
{
    if (tank_ == nullptr)
        return;

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
    case Base::MovableItem::North:
        if (previousTankPositionY_ == tank_->y()) {
            int direction = Utils::Functions::randomNumber(1, 4);
            if (static_cast<int>(Base::MovableItem::North != direction))
                tank_->setDirection(static_cast<Base::MovableItem::Direction>(direction));
            else
                tank_->setDirection(Base::MovableItem::South);
        }
        break;
    case Base::MovableItem::South:
        if (previousTankPositionY_ == tank_->y()) {
            int direction = Utils::Functions::randomNumber(1, 4);
            if (static_cast<int>(Base::MovableItem::South != direction))
                tank_->setDirection(static_cast<Base::MovableItem::Direction>(direction));
            else
                tank_->setDirection(Base::MovableItem::North);
        }
        break;
    case Base::MovableItem::West:
        if (previousTankPositionX_ == tank_->x()) {
            int direction = Utils::Functions::randomNumber(1, 4);
            if (static_cast<int>(Base::MovableItem::West != direction))
                tank_->setDirection(static_cast<Base::MovableItem::Direction>(direction));
            else
                tank_->setDirection(Base::MovableItem::East);
        }
        break;
    case Base::MovableItem::East:
        if (previousTankPositionX_ == tank_->x()) {
            int direction = Utils::Functions::randomNumber(1, 4);
            if (static_cast<int>(Base::MovableItem::East != direction))
                tank_->setDirection(static_cast<Base::MovableItem::Direction>(direction));
            else
                tank_->setDirection(Base::MovableItem::West);
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
    if (tank_ == nullptr)
        return;

    int direction = Utils::Functions::randomNumber(1, 100);
    if (direction <= 4)
        tank_->setDirection(static_cast<Base::MovableItem::Direction>(direction));
}

void EnemyDriver::moveToPlayer()
{
    if (tank_ == nullptr)
        return;
    // TODO: add implementation
}

void EnemyDriver::moveToEagle()
{
    if (tank_ == nullptr)
        return;
    // TODO: add implementation
}

}  // namespace Controller
