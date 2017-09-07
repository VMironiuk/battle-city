#include "baseitem.h"

BaseItem::BaseItem(QObject *parent)
    : QObject(parent)
{

}

void BaseItem::setX(qreal x)
{
    if (x_ == x)
        return;
    x_ = x;
    emit xChanged(x_);
}

void BaseItem::setY(qreal y)
{
    if (y_ == y)
        return;
    y_ = y;
    emit yChanged(y_);
}

void BaseItem::setWidth(qreal width)
{
    if (width_ == width)
        return;
    width_ = width;
    emit widthChanged(width_);
}

void BaseItem::setHeight(qreal height)
{
    if (height_ == height)
        return;
    height_ = height;
    emit heightChanged(height_);
}

void BaseItem::setRotation(qreal rotation)
{
    if (rotation_ == rotation)
        return;
    rotation_ = rotation;
    emit rotationChanged(rotation_);
}

void BaseItem::setImageSource(const QString &imageSource)
{
    if (imageSource_ == imageSource)
        return;
    imageSource_ = imageSource;
    emit imageSourceChanged(imageSource_);
}
