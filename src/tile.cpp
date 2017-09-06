#include "tile.h"

#include <QDebug>

Tile::Tile(QObject *parent) : QObject(parent)
{

}

void Tile::setImagePath(const QString &imagePath)
{
    if (imagePath_ != imagePath) {
        imagePath_ = imagePath;
        emit imagePathChanged(imagePath);
    }
}

void Tile::setWidth(qreal width)
{
//    qDebug() << Q_FUNC_INFO << width;

    if (width_ != width) {
        width_ = width;
        emit widthChanged(width);
    }
}

void Tile::setHeight(qreal height)
{
//    qDebug() << Q_FUNC_INFO << height;

    if (height_ != height) {
        height_ = height;
        emit heightChanged(height);
    }
}

void Tile::setX(qreal x)
{
//    qDebug() << Q_FUNC_INFO << x;

    if (x_ != x) {
        x_ = x;
        emit xChanged(x);
    }
}

void Tile::setY(qreal y)
{
//    qDebug() << Q_FUNC_INFO << y;

    if (y_ != y) {
        y_ = y;
        emit yChanged(y);
    }
}
