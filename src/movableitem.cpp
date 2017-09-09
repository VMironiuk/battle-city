#include "movableitem.h"

MovableItem::MovableItem(QObject *parent)
    : BaseItem(parent)
{
}

void MovableItem::move()
{
    switch (direction_) {
    case North:
        moveNorth();
        break;
    case South:
        moveSouth();
        break;
    case West:
        moveWest();
        break;
    case East:
        moveEast();
        break;
    case None: // fall down
    default:
        break;
    }
}

void MovableItem::setSpeed(int speed)
{
    if (speed_ == speed)
        return;
    speed_ = speed;
    emit speedChanged(speed_);
}

void MovableItem::setDirection(MovableItem::Direction direction)
{
    if (direction_ == direction)
        return;
    direction_ = direction;
    emit directionChanged(direction_);
}

void MovableItem::moveNorth()
{
    setDirection(North);
    setRotation(0);
    setY(y() - speed_);
}

void MovableItem::moveSouth()
{
    setDirection(South);
    setRotation(180);
    setY(y() + speed_);
}

void MovableItem::moveWest()
{
    setDirection(West);
    setRotation(270);
    setX(x() - speed_);
}

void MovableItem::moveEast()
{
    setDirection(East);
    setRotation(90);
    setX(x() + speed_);
}
