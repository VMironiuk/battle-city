#ifndef SHOOTABLEITEM_H
#define SHOOTABLEITEM_H

#include "movableitem.h"

class ShootableItem : public MovableItem
{
    Q_OBJECT
public:
    ShootableItem(QObject *parent = nullptr);

    Q_INVOKABLE void shoot() const;
};

#endif // SHOOTABLEITEM_H
