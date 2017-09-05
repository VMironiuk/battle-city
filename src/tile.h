#ifndef TILE_H
#define TILE_H

#include <QObject>

class Tile : public QObject
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = nullptr);

public slots:
    void setWidth(int width);
    void setHeight(int height);
    void setX(int x);
    void setY(int y);

private:
    int width_ = 0;
    int height_ = 0;
    int x_ = 0;
    int y_ = 0;
};

#endif // TILE_H
