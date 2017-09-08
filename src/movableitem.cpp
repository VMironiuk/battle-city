#include "movableitem.h"

#include "collider.h"

#include <QDebug>

MovableItem::MovableItem(QObject *parent)
    : BaseItem(parent)
{

}

void MovableItem::moveNorth()
{
    // TODO: check some obstacles before moving
    setDirection(North);
    setRotation(0);
    if (Collider::instance().isCollided(this))
        return;

    setY(y() - speed_);
}

void MovableItem::moveSouth()
{
    // TODO: check some obstacles before moving
    setDirection(South);
    setRotation(180);
    if (Collider::instance().isCollided(this))
        return;

    setY(y() + speed_);
}

void MovableItem::moveWest()
{
    // TODO: check some obstacles before moving
    setDirection(West);
    setRotation(270);
    if (Collider::instance().isCollided(this))
        return;

    setX(x() - speed_);
}

void MovableItem::moveEast()
{
    // TODO: check some obstacles before moving
    setDirection(East);
    setRotation(90);
    if (Collider::instance().isCollided(this))
        return;

    setX(x() + speed_);
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
