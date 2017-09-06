#ifndef TILE_H
#define TILE_H

#include <QObject>

class Tile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
public:
    explicit Tile(QObject *parent = nullptr);

public slots:
    QString imagePath() const { return imagePath_; }
    void setImagePath(const QString &imagePath);

    int width() const { return width_; }
    void setWidth(int width);

    int height() const { return height_; }
    void setHeight(int height);

    int x() const { return x_; }
    void setX(int x);

    int y() const { return y_; }
    void setY(int y);

signals:
    void imagePathChanged(const QString imagePath);
    void widthChanged(int width);
    void heightChanged(int height);
    void xChanged(int x);
    void yChanged(int y);

private:
    QString imagePath_;
    int width_ = 0;
    int height_ = 0;
    int x_ = 0;
    int y_ = 0;
};

#endif // TILE_H
