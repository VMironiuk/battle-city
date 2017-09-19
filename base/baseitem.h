#ifndef BASEITEM_H
#define BASEITEM_H

#include "bcobject.h"

namespace Base {

class BaseItem : public BCObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int z READ z WRITE setZ NOTIFY zChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(int rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)
public:
    explicit BaseItem(QObject *parent = nullptr);

    int x() const { return x_; }
    void setX(int x);

    int y() const { return y_; }
    void setY(int y);

    int z() const { return z_; }
    void setZ(int z);

    int width() const { return width_; }
    void setWidth(int width);

    int height() const { return height_; }
    void setHeight(int height);

    int rotation() const { return rotation_; }
    void setRotation(int rotation);

    QString imageSource() const { return imageSource_; }
    void setImageSource(const QString &imageSource);

    int top() const { return y_; }
    int bottom() const { return y_ + height_; }
    int left() const { return x_; }
    int right() const { return x_ + width_; }

signals:
    void xChanged(int x);
    void yChanged(int y);
    void zChanged(int z);
    void widthChanged(int width);
    void heightChanged(int height);
    void rotationChanged(int rotation);
    void imageSourceChanged(const QString &imageSource);

private:
    int x_ = 0;
    int y_ = 0;
    int z_ = 0;
    int width_ = 0;
    int height_ = 0;
    int rotation_ = 0;
    QString imageSource_;
};

}  // namespace Base

#endif // BASEITEM_H
