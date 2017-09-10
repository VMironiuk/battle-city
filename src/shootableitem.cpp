#include "shootableitem.h"

#include <QDebug>

ShootableItem::ShootableItem(QObject *parent)
    : MovableItem(parent)
{
}

void ShootableItem::shoot()
{
    // TODO: just for testing, update later !!!
    qDebug() << Q_FUNC_INFO;
    MovableItem *projectile = new MovableItem;
    projectile->setWidth(12);
    projectile->setHeight(12);
    projectile->setX(x());
    projectile->setY(y());
    projectile->setDirection(MovableItem::North);
    projectile->setRotation(rotation());
    projectile->setImageSource("qrc:/images/projectiles/projectile.png");
    emit shootEmitted(projectile);
}
