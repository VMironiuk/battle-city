#include "movableitem.h"

namespace Base {

MovableItem::MovableItem(QObject *parent)
    : BaseItem(parent)
{
}

void MovableItem::move()
{
    if (!movement_)
        return;

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

void MovableItem::setMovement(bool movement)
{
    if (movement_ == movement)
        return;
    movement_ = movement;
    emit movementChanged(movement_);
}

void MovableItem::moveNorth()
{
    setRotation(0);
    setY(y() - speed_);
}

void MovableItem::moveSouth()
{
    setRotation(180);
    setY(y() + speed_);
}

void MovableItem::moveWest()
{
    setRotation(270);
    setX(x() - speed_);
}

void MovableItem::moveEast()
{
    setRotation(90);
    setX(x() + speed_);
}

}  // namespace Base
