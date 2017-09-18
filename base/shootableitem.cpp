#include "shootableitem.h"

#include <QVariant>

#include "global.h"

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
    projectile->setProperty(Constants::Property::Belligerent,
                            property(Constants::Property::Belligerent).toString());

    switch (shotMode_) {
    case SlowShot:
        projectile->setSpeed(10);
        break;
    case FastShot:
        projectile->setSpeed(20);
        break;
    case BurstShot:
        projectile->setSpeed(20);
        break;
    case PowerfulShot:
        projectile->setSpeed(20);
        projectile->setProperty(Constants::Projectile::Property::Powerful, true);
        break;
    default:
        break;
    }

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

void ShootableItem::setShotMode(ShootableItem::ShotMode shotMode)
{
    if (shotMode_ == shotMode)
        return;
    shotMode_ = shotMode;
    emit shotModeChanged(shotMode_);
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
        projectile->setY(top() + projectile->height());
        break;
    case MovableItem::South:
        projectile->setX(left()  + width() / 2 - projectile->width() / 2);
        projectile->setY(bottom() - projectile->height());
        break;
    case MovableItem::West:
        projectile->setX(left() + projectile->width());
        projectile->setY(top() + width() / 2 - projectile->height() / 2);
        break;
    case MovableItem::East:
        projectile->setX(right() - projectile->width());
        projectile->setY(top() + width() / 2 - projectile->height() / 2);
        break;
    default:
        break;
    }
}

bool ShootableItem::charged() const
{
    if (shotMode_ == BurstShot)
        return chargingTime_.elapsed() > 250;
    return charge_ && chargingTime_.elapsed() > chargingInterval_;
}
