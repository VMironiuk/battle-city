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
    Q_PROPERTY(QQmlListProperty<ShootableItem> playerTanksProperty READ playerTanksProperty NOTIFY playerTanksPropertyChanged)
    Q_PROPERTY(QQmlListProperty<ShootableItem> enemyTanksProperty READ enemyTanksProperty NOTIFY enemyTanksPropertyChanged)
    Q_PROPERTY(QQmlListProperty<MovableItem> projectilesProperty READ projectilesProperty NOTIFY projectilesPropertyChanged)
    Q_PROPERTY(QQmlListProperty<BaseItem> explosionsProperty READ explosionsProperty NOTIFY explosionsPropertyChanged)
    Q_PROPERTY(BaseItem* eagle READ eagle CONSTANT)
public:
    explicit Board(int rows, int cols, int tileSize, QObject *parent = nullptr);
    ~Board();

    QQmlListProperty<Tile> tilesProperty();
    QQmlListProperty<ShootableItem> playerTanksProperty();
    QQmlListProperty<ShootableItem> enemyTanksProperty();
    QQmlListProperty<MovableItem> projectilesProperty();
    QQmlListProperty<BaseItem> explosionsProperty();
    BaseItem *eagle() { return &eagle_; }

    QList<Tile *> tiles() const { return tiles_; }
    QList<ShootableItem *> playerTanks() const { return playerTanks_; }
    QList<ShootableItem *> enemyTanks() const { return enemyTanks_; }
    QList<MovableItem *> projectiles() const { return projectiles_; }

    void removePlayerTank(ShootableItem *playerTank);
    void removeEnemyTank(ShootableItem *enemyTank);
    void removeProjectile(MovableItem *projectile);
    void removeExplosion(BaseItem *explosion);
    void destroyEagle(BaseItem *eagle);

    void setupTile(int row, int column, Tile::Material material);
    void addPlayerTank(int row, int column, ShootableItem *tank);
    void addEnemyTank(int row, int column, ShootableItem *tank);

public slots:
    void update();

signals:
    void playerTanksPropertyChanged(QQmlListProperty<ShootableItem>);
    void enemyTanksPropertyChanged(QQmlListProperty<ShootableItem>);
    void projectilesPropertyChanged(QQmlListProperty<MovableItem>);
    void explosionsPropertyChanged(QQmlListProperty<BaseItem>);

private slots:
    void addProjectile(MovableItem *projectile);
    void onExplosionTimeout();

private:
    void initialize();
    void makeTiles();
    void makeBase();
    void makeExplosion(int x, int y, int w, int h, const QString &image);
    Tile *tile(int row, int column) const;

    QList<Tile *> tiles_;
    QList<ShootableItem *> playerTanks_;
    QList<ShootableItem *> enemyTanks_;
    QList<MovableItem *> projectiles_;
    QList<BaseItem *> explosions_;
    BaseItem eagle_;

    int rowCount_;
    int colCount_;
    int tileSize_;
};

#endif // BOARD_H
