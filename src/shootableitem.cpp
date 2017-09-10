#include "shootableitem.h"

#include <QDebug>

ShootableItem::ShootableItem(QObject *parent)
    : MovableItem(parent)
{
}

void ShootableItem::shoot() const
{
    qDebug() << Q_FUNC_INFO;
}
