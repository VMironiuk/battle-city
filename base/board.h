#ifndef BOARD_H
#define BOARD_H

#include <QQmlListProperty>

#include "baseitem.h"
#include "global.h"
#include "movableitem.h"
#include "shootableitem.h"
#include "tile.h"

namespace Base {

class Board : public BaseItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Base::Tile> tilesProperty READ tilesProperty CONSTANT)
    Q_PROPERTY(QQmlListProperty<Base::ShootableItem> playerTanksProperty READ playerTanksProperty NOTIFY playerTanksPropertyChanged)
    Q_PROPERTY(QQmlListProperty<Base::ShootableItem> enemyTanksProperty READ enemyTanksProperty NOTIFY enemyTanksPropertyChanged)
    Q_PROPERTY(QQmlListProperty<Base::MovableItem> projectilesProperty READ projectilesProperty NOTIFY projectilesPropertyChanged)
    Q_PROPERTY(QQmlListProperty<Base::BaseItem> explosionsProperty READ explosionsProperty NOTIFY explosionsPropertyChanged)
    Q_PROPERTY(QQmlListProperty<Base::BaseItem> bonusesProperty READ bonusesProperty NOTIFY bonusesPropertyChanged)
    Q_PROPERTY(BaseItem* eagle READ eagle CONSTANT)
public:
    Board(int rows, int cols, int tileSize, QObject *parent = nullptr);
    ~Board();

    QQmlListProperty<Tile> tilesProperty();
    QQmlListProperty<ShootableItem> playerTanksProperty();
    QQmlListProperty<ShootableItem> enemyTanksProperty();
    QQmlListProperty<MovableItem> projectilesProperty();
    QQmlListProperty<BaseItem> explosionsProperty();
    QQmlListProperty<BaseItem> bonusesProperty();
    BaseItem *eagle() { return &eagle_; }

    QList<Tile *> tiles() const { return tiles_; }
    QList<ShootableItem *> playerTanks() const { return playerTanks_; }
    QList<ShootableItem *> enemyTanks() const { return enemyTanks_; }
    QList<MovableItem *> projectiles() const { return projectiles_; }
    QList<BaseItem *> bonuses() const { return bonuses_; }

    void clear();
    void clearMap();
    void removePlayerTank(ShootableItem *playerTank);
    void removeEnemyTank(ShootableItem *enemyTank);
    void removeAllEnemyTanks();
    void removeProjectile(MovableItem *projectile);
    void removeProjectileQuietly(MovableItem *projectile);
    void removeAllProjectiles();
    void removeExplosion(BaseItem *explosion);
    void removeAllExplosions();
    void removeBonus(BaseItem *bonus);
    void removeAllBonuses();
    void removeFirstBonus();
    void destroyEagle(BaseItem *eagle);

    bool setupTile(int row, int column, Tile::Material material);
    void addPlayerTank(int row, int column, ShootableItem *tank);
    void addEnemyTank(int row, int column, ShootableItem *tank);
    void addBonus(int row, int column, BaseItem *bonus);

    void onBonusReached(ShootableItem *playerTank, BaseItem *bonus);

    void updatePlayerTankPos(int row, int column);

public slots:
    void update();

signals:
    void playerTanksPropertyChanged(QQmlListProperty<ShootableItem>);
    void enemyTanksPropertyChanged(QQmlListProperty<ShootableItem>);
    void projectilesPropertyChanged(QQmlListProperty<MovableItem>);
    void explosionsPropertyChanged(QQmlListProperty<BaseItem>);
    void bonusesPropertyChanged(QQmlListProperty<BaseItem>);
    void eagleDestroyed();
    void playerTankDestroyed();
    void enemyTankDestroyed(int tankValue);
    void bonusReached(Base::ShootableItem *playerTank,
                      Base::Constants::Bonus::BonusType bonusType);

private slots:
    void addProjectile(MovableItem *projectile);
    void onExplosionTimeout();

private:
    void initialize();
    bool makeTiles();
    void makeBase();
    void makeExplosion(int x, int y, int w, int h, const QString &image);
    Tile *tile(int row, int column) const;

    QList<Tile *> tiles_;
    QList<ShootableItem *> playerTanks_;
    QList<ShootableItem *> enemyTanks_;
    QList<MovableItem *> projectiles_;
    QList<BaseItem *> explosions_;
    QList<BaseItem *> bonuses_;
    BaseItem eagle_;

    int rowCount_;
    int colCount_;
    int tileSize_;
};

}  // namespace Base

#endif // BOARD_H
