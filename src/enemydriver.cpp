#include "enemydriver.h"

EnemyDriver::EnemyDriver(ShootableItem *tank, QObject *parent)
    : QObject(parent),
      tank_(tank)
{
    connect(tank_, SIGNAL(destroyed(QObject*)), this, SIGNAL(wannaDie()));
}
