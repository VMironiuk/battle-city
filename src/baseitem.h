#ifndef BASEITEM_H
#define BASEITEM_H

#include <QMap>
#include <QObject>

class BaseItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)
public:
    explicit BaseItem(QObject *parent = nullptr);

    qreal x() const { return x_; }
    void setX(qreal x);

    qreal y() const { return y_; }
    void setY(qreal y);

    qreal width() const { return width_; }
    void setWidth(qreal width);

    qreal height() const { return height_; }
    void setHeight(qreal height);

    qreal rotation() const { return rotation_; }
    void setRotation(qreal rotation);

    QString imageSource() const { return imageSource_; }
    void setImageSource(const QString &imageSource);

signals:
    void xChanged(qreal x);
    void yChanged(qreal y);
    void widthChanged(qreal width);
    void heightChanged(qreal height);
    void rotationChanged(qreal rotation);
    void imageSourceChanged(const QString &imageSource);

private:
    qreal x_ = .0;
    qreal y_ = .0;
    qreal width_ = .0;
    qreal height_ = .0;
    qreal rotation_ = .0;
    QString imageSource_;
};

#endif // BASEITEM_H
