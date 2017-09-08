#ifndef BOARD_H
#define BOARD_H

#include <QQmlListProperty>

#include "baseitem.h"
#include "movableitem.h"
#include "tile.h"

class Board : public BaseItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Tile> tilesProperty READ tilesProperty CONSTANT)
    Q_PROPERTY(QQmlListProperty<MovableItem> tanksProperty READ tanksProperty CONSTANT)
public:
    explicit Board(QObject *parent = nullptr);
    ~Board();

    QQmlListProperty<Tile> tilesProperty();
    QQmlListProperty<MovableItem> tanksProperty();

    QList<Tile *> tiles() const { return tiles_; }
    QList<MovableItem *> tanks() const { return tanks_; }

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
