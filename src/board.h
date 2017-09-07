#ifndef BOARD_H
#define BOARD_H

#include <QQmlListProperty>

#include "baseitem.h"
#include "movableitem.h"
#include "tile.h"

class Board : public BaseItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Tile> tiles READ tiles CONSTANT)
    Q_PROPERTY(QQmlListProperty<MovableItem> tanks READ tanks CONSTANT)
public:
    explicit Board(QObject *parent = nullptr);
    ~Board();

    QQmlListProperty<Tile> tiles();
    QQmlListProperty<MovableItem> tanks();

private slots:
    void updateGeometry();

private:
    void initialize();
    void makeTiles();
    void makeMaze();
    void makeTanks();
    Tile *tile(int row, int column) const;

    QList<Tile *> tiles_;
    QList<MovableItem *> tanks_;
};

#endif // BOARD_H
