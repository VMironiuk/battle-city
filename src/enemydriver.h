#ifndef ENEMYDRIVER_H
#define ENEMYDRIVER_H

#include <QObject>
#include <QTime>

#include "shootableitem.h"

class EnemyDriver : public QObject
{
    friend class GameController;

    Q_OBJECT
public:
    EnemyDriver(ShootableItem *tank, QObject *parent = nullptr);

signals:
    void wannaDie();

private:
    void update();
    void moveRandomly();
    void moveToPlayer();
    void moveToEagle();

    ShootableItem *tank_;
    int previousTankPositionX_;
    int previousTankPositionY_;
    QTime movementPeriodTime_;
};

#endif // ENEMYDRIVER_H
