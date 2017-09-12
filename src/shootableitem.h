#ifndef SHOOTABLEITEM_H
#define SHOOTABLEITEM_H

#include "movableitem.h"
#include "delay.h"

class ShootableItem : public MovableItem
{
    Q_OBJECT
public:
    ShootableItem(QObject *parent = nullptr);

    Q_INVOKABLE virtual void shoot();

    void setShootDelayInterval(int interval);

signals:
    void shootEmitted(MovableItem *projectile);

private:
    void adjustProjectilePosition(MovableItem *projectile) const;

    Delay shootDelay_;
};

#endif // SHOOTABLEITEM_H
