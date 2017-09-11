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
    Q_PROPERTY(QQmlListProperty<MovableItem> projectilesProperty READ projectilesProperty NOTIFY projectilesPropertyChanged)
public:
    explicit Board(QObject *parent = nullptr);
    ~Board();

    QQmlListProperty<Tile> tilesProperty();
    QQmlListProperty<ShootableItem> playerTanksProperty();
    QQmlListProperty<MovableItem> projectilesProperty();

    QList<Tile *> tiles() const { return tiles_; }
    QList<ShootableItem *> playerTanks() const { return playerTanks_; }
    QList<MovableItem *> projectiles() const { return projectiles_; }

    void removeProjectile(MovableItem *projectile);

public slots:
    void update();

signals:
    void projectilesPropertyChanged(QQmlListProperty<MovableItem>);

private slots:
    void addProjectile(MovableItem *projectile);

private:
    void initialize();
    void makeTiles();
    void makeMaze();
    void makeTanks();
    Tile *tile(int row, int column) const;

    QList<Tile *> tiles_;
    QList<ShootableItem *> playerTanks_;
    QList<MovableItem *> projectiles_;
};

#endif // BOARD_H
