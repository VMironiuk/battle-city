#ifndef BOARD_H
#define BOARD_H

#include <QQmlListProperty>

#include "baseitem.h"
#include "movableitem.h"
#include "shootableitem.h"
#include "tile.h"

class Board : public BaseItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Tile> tilesProperty READ tilesProperty CONSTANT)
    Q_PROPERTY(QQmlListProperty<ShootableItem> playerTanksProperty READ playerTanksProperty CONSTANT)
public:
    explicit Board(QObject *parent = nullptr);
    ~Board();

    QQmlListProperty<Tile> tilesProperty();
    QQmlListProperty<ShootableItem> playerTanksProperty();

    QList<Tile *> tiles() const { return tiles_; }
    QList<ShootableItem *> playerTanks() const { return playerTanks_; }

public slots:
    void update();

private:
    void initialize();
    void makeTiles();
    void makeMaze();
    void makeTanks();
    Tile *tile(int row, int column) const;

    QList<Tile *> tiles_;
    QList<ShootableItem *> playerTanks_;
};

#endif // BOARD_H
