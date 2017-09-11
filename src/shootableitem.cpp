#include "shootableitem.h"

#include <QDebug>

ShootableItem::ShootableItem(QObject *parent)
    : MovableItem(parent)
{
}

void ShootableItem::shoot()
{
    MovableItem *projectile = new MovableItem;
    projectile->setWidth(12);
    projectile->setHeight(12);
    adjustProjectilePosition(projectile);
    projectile->setDirection(direction());
    projectile->setRotation(rotation());
    projectile->setImageSource("qrc:/images/projectiles/projectile.png");
    projectile->setMovement(true);
    projectile->setProperty("battleCitySide", property("battleCitySide").toString());
    emit shootEmitted(projectile);
}

void ShootableItem::adjustProjectilePosition(MovableItem *projectile) const
{
    switch (direction()) {
    case MovableItem::North:
        projectile->setX(left()  + width() / 2 - projectile->width() / 2);
        projectile->setY(top() - projectile->height());
        break;
    case MovableItem::South:
        projectile->setX(left()  + width() / 2 - projectile->width() / 2);
        projectile->setY(bottom() + projectile->height());
        break;
    case MovableItem::West:
        projectile->setX(left() - projectile->width());
        projectile->setY(top() + width() / 2 - projectile->height() / 2);
        break;
    case MovableItem::East:
        projectile->setX(right() + projectile->width());
        projectile->setY(top() + width() / 2 - projectile->height() / 2);
        break;
    default:
        break;
    }
}
