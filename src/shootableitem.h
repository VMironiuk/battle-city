#ifndef SHOOTABLEITEM_H
#define SHOOTABLEITEM_H

#include "movableitem.h"
#include "delay.h"

class ShootableItem : public MovableItem
{
    Q_OBJECT
    Q_PROPERTY(bool shooting READ shooting WRITE setShooting NOTIFY shootingChanged)
public:
    ShootableItem(QObject *parent = nullptr);

    virtual void shoot();

    void setShootDelayInterval(int interval);

    bool shooting() const { return shooting_; }
    void setShooting(bool shooting);

signals:
    void shootEmitted(MovableItem *projectile);
    void shootingChanged(bool shooting);

private:
    void adjustProjectilePosition(MovableItem *projectile) const;

    Delay shootDelay_;
    bool shooting_ = true;
};

#endif // SHOOTABLEITEM_H
