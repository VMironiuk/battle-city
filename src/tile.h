#ifndef TILE_H
#define TILE_H

#include <QObject>

class Tile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
public:
    explicit Tile(QObject *parent = nullptr);

public slots:
    QString imagePath() const { return imagePath_; }
    void setImagePath(const QString &imagePath);

    qreal width() const { return width_; }
    void setWidth(qreal width);

    qreal height() const { return height_; }
    void setHeight(qreal height);

    qreal x() const { return x_; }
    void setX(qreal x);

    qreal y() const { return y_; }
    void setY(qreal y);

signals:
    void imagePathChanged(const QString imagePath);
    void widthChanged(int width);
    void heightChanged(int height);
    void xChanged(int x);
    void yChanged(int y);

private:
    QString imagePath_;
    qreal width_ = 0;
    qreal height_ = 0;
    qreal x_ = .0;
    qreal y_ = .0;
};

#endif // TILE_H
