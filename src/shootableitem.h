#ifndef SHOOTABLEITEM_H
#define SHOOTABLEITEM_H

#include <QTime>

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

    int chargingInterval() const { return chargingInterval_; }
    void setChargingInterval(int chargingInterval);

signals:
    void shootEmitted(MovableItem *projectile);
    void shootingChanged(bool shooting);
    void chargingIntervalChanged(int chargingInterval);

private slots:
    void charge();
    void uncharge();

private:
    void adjustProjectilePosition(MovableItem *projectile) const;
    bool charged() const;

    bool shooting_ = true;
    bool charge_ = true;
    int chargingInterval_ = 1000;
    QTime chargingTime_;
};

#endif // SHOOTABLEITEM_H
