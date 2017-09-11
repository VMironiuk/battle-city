#ifndef SHOOTABLEITEM_H
#define SHOOTABLEITEM_H

#include "movableitem.h"

class ShootableItem : public MovableItem
{
    Q_OBJECT
public:
    ShootableItem(QObject *parent = nullptr);

    Q_INVOKABLE virtual void shoot();

signals:
    void shootEmitted(MovableItem *projectile);

private:
    void adjustProjectilePosition(MovableItem *projectile) const;
};

#endif // SHOOTABLEITEM_H
