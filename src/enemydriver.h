#ifndef ENEMYDRIVER_H
#define ENEMYDRIVER_H

#include <QObject>

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

    ShootableItem *tank_;
};

#endif // ENEMYDRIVER_H
