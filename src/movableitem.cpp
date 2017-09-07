#include "movableitem.h"

MovableItem::MovableItem(QObject *parent)
    : BaseItem(parent)
{

}

void MovableItem::moveNorth()
{
    // TODO: check some obstacles before moving
    setY(y() - speed_);
    setRotation(.0);
}

void MovableItem::moveSouth()
{
    // TODO: check some obstacles before moving
    setY(y() + speed_);
    setRotation(180.0);
}

void MovableItem::moveWest()
{
    // TODO: check some obstacles before moving
    setX(x() - speed_);
    setRotation(270.0);
}

void MovableItem::moveEast()
{
    // TODO: check some obstacles before moving
    setX(x() + speed_);
    setRotation(90.0);
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
