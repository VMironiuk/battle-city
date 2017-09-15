#include "shootableitem.h"

#include <QVariant>

ShootableItem::ShootableItem(QObject *parent)
    : MovableItem(parent)
{
    chargingTime_.start();
}

void ShootableItem::shoot()
{
    if (!shooting_)
        return;

    if (!charged())
        return;

    MovableItem *projectile = new MovableItem;
    projectile->setWidth(14);
    projectile->setHeight(14);
    adjustProjectilePosition(projectile);
    projectile->setDirection(direction());
    projectile->setRotation(rotation());
    projectile->setImageSource("qrc:/images/projectiles/projectile.png");
    projectile->setMovement(true);
    projectile->setProperty("battleCitySide", property("battleCitySide").toString());
    projectile->setSpeed(10);
    emit shootEmitted(projectile);

    uncharge();
    connect(projectile, SIGNAL(destroyed(QObject*)), this, SLOT(charge()));
}

void ShootableItem::setShooting(bool shooting)
{
    if (shooting_ == shooting)
        return;
    shooting_ = shooting;
    emit shootingChanged(shooting_);
}

void ShootableItem::setChargingInterval(int chargingInterval)
{
    if (chargingInterval_ == chargingInterval)
        return;
    chargingInterval_ = chargingInterval;
    emit chargingIntervalChanged(chargingInterval_);
}

void ShootableItem::charge()
{
    charge_ = true;
}

void ShootableItem::uncharge()
{
    charge_ = false;
    chargingTime_.restart();
}

void ShootableItem::adjustProjectilePosition(MovableItem *projectile) const
{
    switch (direction()) {
    case MovableItem::North:
        projectile->setX(left()  + width() / 2 - projectile->width() / 2);
        projectile->setY(top());
        break;
    case MovableItem::South:
        projectile->setX(left()  + width() / 2 - projectile->width() / 2);
        projectile->setY(bottom());
        break;
    case MovableItem::West:
        projectile->setX(left());
        projectile->setY(top() + width() / 2 - projectile->height() / 2);
        break;
    case MovableItem::East:
        projectile->setX(right());
        projectile->setY(top() + width() / 2 - projectile->height() / 2);
        break;
    default:
        break;
    }
}

bool ShootableItem::charged() const
{
    return charge_ && chargingTime_.elapsed() > chargingInterval_;
}
