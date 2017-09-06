#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QSharedPointer>
#include <QColor>
#include <QQmlListProperty>

#include "tile.h"

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QQmlListProperty<Tile> tiles READ tiles CONSTANT)
public:
    explicit Board(QObject *parent = nullptr);
    ~Board();

    int width() const { return width_; }
    void setWidth(int width);

    int height() const { return height_; }
    void setHeight(int height);

    Tile *tile(int row, int column) const;
    QQmlListProperty<Tile> tiles();

signals:
    void widthChanged(int width);
    void heightChanged(int height);

private slots:
    void updateTiles();
    void makeMaze();

private:
    void initialize();
    void fillTiles();

    int width_ = 0;
    int height_ = 0;
    QList<Tile *> tiles_;

    static const int SIZE;
};

#endif // BOARD_H
