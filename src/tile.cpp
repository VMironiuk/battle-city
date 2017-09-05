#include "tile.h"

#include <QDebug>

Tile::Tile(QObject *parent) : QObject(parent)
{

}

void Tile::setWidth(int width)
{
//    qDebug() << Q_FUNC_INFO << width;

    width_ = width;
}

void Tile::setHeight(int height)
{
//    qDebug() << Q_FUNC_INFO << height;

    height_ = height;
}

void Tile::setX(int x)
{
//    qDebug() << Q_FUNC_INFO << x;

    x_ = x;
}

void Tile::setY(int y)
{
//    qDebug() << Q_FUNC_INFO << y;

    y_ = y;
}
