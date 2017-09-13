#ifndef SHOOTABLEITEM_H
#define SHOOTABLEITEM_H

#include "movableitem.h"

class ShootableItem : public MovableItem
{
    Q_OBJECT
    Q_PROPERTY(bool shooting READ shooting WRITE setShooting NOTIFY shootingChanged)
public:
    ShootableItem(QObject *parent = nullptr);

    virtual void shoot();

    bool shooting() const { return shooting_; }
    void setShooting(bool shooting);

signals:
    void shootEmitted(MovableItem *projectile);
    void shootingChanged(bool shooting);

private slots:
    void charge();
    void uncharge();

private:
    void adjustProjectilePosition(MovableItem *projectile) const;

    bool shooting_ = true;
    bool charge_ = true;
};

#endif // SHOOTABLEITEM_H
