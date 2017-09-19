#ifndef ENEMYDRIVER_H
#define ENEMYDRIVER_H

#include <QObject>
#include <QTime>

#include "shootableitem.h"

namespace Controller {

class EnemyDriver : public QObject
{

    Q_OBJECT
public:
    EnemyDriver(Base::ShootableItem *tank, QObject *parent = nullptr);

    void update();

signals:
    void wannaDie();

private:
    void moveRandomly();
    void moveToPlayer();
    void moveToEagle();

    Base::ShootableItem *tank_;
    int previousTankPositionX_;
    int previousTankPositionY_;
    QTime movementPeriodTime_;
};

}  // namespace Controller

#endif // ENEMYDRIVER_H
