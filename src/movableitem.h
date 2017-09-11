#ifndef MOVABLEITEM_H
#define MOVABLEITEM_H

#include "baseitem.h"

class MovableItem : public BaseItem
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(Direction direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(bool movement READ movement WRITE setMovement NOTIFY movementChanged)
public:
    enum Direction {
        North = 1,
        South,
        West,
        East
    };
    Q_ENUMS(Direction)

    MovableItem(QObject *parent = nullptr);

    virtual void move();

    int speed() const { return speed_; }
    void setSpeed(int speed);

    Direction direction() const { return direction_; }
    void setDirection(Direction direction);

    bool movement() const { return movement_; }
    void setMovement(bool movement);

signals:
    void speedChanged(int speed);
    void directionChanged(Direction direction);
    void movementChanged(bool movement);

private:
    void moveNorth();
    void moveSouth();
    void moveWest();
    void moveEast();

    int speed_ = 4;
    Direction direction_ = South;
    bool movement_ = true;
};

#endif // MOVABLEITEM_H
