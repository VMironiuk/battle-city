#ifndef MOVABLEITEM_H
#define MOVABLEITEM_H

#include "baseitem.h"

class MovableItem : public BaseItem
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(Direction direction READ direction WRITE setDirection NOTIFY directionChanged)
public:
    enum Direction {
        None,
        North,
        South,
        West,
        East
    };
    Q_ENUMS(Direction)

    MovableItem(QObject *parent = nullptr);

    Q_INVOKABLE void moveNorth();
    Q_INVOKABLE void moveSouth();
    Q_INVOKABLE void moveWest();
    Q_INVOKABLE void moveEast();

    int speed() const { return speed_; }
    void setSpeed(int speed);

    Direction direction() const { return direction_; }
    void setDirection(Direction direction);

signals:
    void speedChanged(int speed);
    void directionChanged(Direction direction);

private:
    int speed_ = 1;
    Direction direction_ = None;
};

#endif // MOVABLEITEM_H
