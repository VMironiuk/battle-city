#include "enemydriver.h"

#include <QDebug>

EnemyDriver::EnemyDriver(ShootableItem *tank, QObject *parent)
    : QObject(parent),
      tank_(tank)
{
    tank_->setMovement(true);
    tank->setShooting(true);
    tank_->setDirection(MovableItem::South);

    previousTankPositionX_ = tank_->x();
    previousTankPositionY_ = tank->y();

    connect(tank_, SIGNAL(destroyed(QObject*)), this, SIGNAL(wannaDie()));
}

void EnemyDriver::update()
{
    // TODO: just for testing, find better solution
    switch (tank_->direction()) {
    case MovableItem::North:
        if (previousTankPositionY_ == tank_->y())
            tank_->setDirection(MovableItem::South);
        break;
    case MovableItem::South:
        if (previousTankPositionY_ == tank_->y())
            tank_->setDirection(MovableItem::North);
        break;
    case MovableItem::West:
        break;
    case MovableItem::East:
        break;
    default:
        break;
    }

    previousTankPositionX_ = tank_->x();
    previousTankPositionY_ = tank_->y();
}
