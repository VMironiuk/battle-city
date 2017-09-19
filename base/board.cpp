#include "board.h"

namespace Base {

Board::Board(int rows, int cols, int tileSize, QObject *parent)
    : BaseItem(parent),
      rowCount_(rows),
      colCount_(cols),
      tileSize_(tileSize)
{
    initialize();
}

Board::~Board()
{
    qDeleteAll(tiles_);
    qDeleteAll(playerTanks_);
    qDeleteAll(enemyTanks_);
    qDeleteAll(projectiles_);
    qDeleteAll(explosions_);
    qDeleteAll(bonuses_);
}

QQmlListProperty<Tile> Board::tilesProperty()
{
    return QQmlListProperty<Tile>(this, tiles_);
}

QQmlListProperty<ShootableItem> Board::playerTanksProperty()
{
    return QQmlListProperty<ShootableItem>(this, playerTanks_);
}

QQmlListProperty<ShootableItem> Board::enemyTanksProperty()
{
    return QQmlListProperty<ShootableItem>(this, enemyTanks_);
}

QQmlListProperty<MovableItem> Board::projectilesProperty()
{
    return QQmlListProperty<MovableItem>(this, projectiles_);
}

QQmlListProperty<BaseItem> Board::explosionsProperty()
{
    return QQmlListProperty<BaseItem>(this, explosions_);
}

QQmlListProperty<BaseItem> Board::bonusesProperty()
{
    return QQmlListProperty<BaseItem>(this, bonuses_);
}

void Board::clear()
{
    removeAllEnemyTanks();
    removeAllProjectiles();
    removeAllExplosions();
    removeAllBonuses();
    clearMap();
}

void Board::clearMap()
{
    for (auto tile : tiles_) {
        if (tile != nullptr)
            tile->setMaterial(Tile::Free);
    }
    makeBase();
}

void Board::removePlayerTank(ShootableItem *playerTank)
{
    if (playerTank == nullptr)
        return;

    int x = playerTank->x() - playerTank->width() / 6;
    int y = playerTank->y() - playerTank->height() / 6;
    makeExplosion(x, y, 76, 76, "qrc:/images/explosions/tank_explosion.gif");

    playerTanks_.removeOne(playerTank);
    emit playerTanksPropertyChanged(playerTanksProperty());
    delete playerTank;
    emit playerTankDestroyed();
}

void Board::removeEnemyTank(ShootableItem *enemyTank)
{
    if (enemyTank == nullptr)
        return;

    int x = enemyTank->x() - enemyTank->width() / 6;
    int y = enemyTank->y() - enemyTank->height() / 6;
    makeExplosion(x, y, 76, 76, "qrc:/images/explosions/tank_explosion.gif");

    enemyTanks_.removeOne(enemyTank);
    emit enemyTanksPropertyChanged(enemyTanksProperty());
    emit enemyTankDestroyed(enemyTank->property(Constants::EnemyTank::Property::Value).toInt());
    delete enemyTank;
}

void Board::removeAllEnemyTanks()
{
    while (!enemyTanks_.isEmpty()) {
        auto tank = enemyTanks_.last();
        if (tank == nullptr) {
            enemyTanks_.removeLast();
            continue;
        }
        tank->setProperty(Constants::EnemyTank::Property::Value, 0);
        removeEnemyTank(tank);
    }
}

void Board::removeProjectile(MovableItem *projectile)
{
    if (projectile == nullptr)
        return;

    int x = projectile->x() - projectile->width();
    int y = projectile->y() - projectile->height();
    makeExplosion(x, y, 44, 44, "qrc:/images/explosions/projectile_explosion.gif");

    projectiles_.removeOne(projectile);
    emit projectilesPropertyChanged(projectilesProperty());
    delete projectile;
}

void Board::removeProjectileQuietly(MovableItem *projectile)
{
    if (projectile == nullptr)
        return;

    projectiles_.removeOne(projectile);
    emit projectilesPropertyChanged(projectilesProperty());
    delete projectile;
}

void Board::removeAllProjectiles()
{
    while (!projectiles_.isEmpty()) {
        auto projectile = projectiles_.last();
        if (projectile == nullptr) {
            projectiles_.removeLast();
            continue;
        }
        removeProjectileQuietly(projectile);
    }
}

void Board::removeExplosion(BaseItem *explosion)
{
    if (explosion == nullptr)
        return;

    explosions_.removeOne(explosion);
    emit explosionsPropertyChanged(explosionsProperty());
    delete explosion;
}

void Board::removeAllExplosions()
{
    while (!explosions_.isEmpty()) {
        auto explosion = explosions_.last();
        if (explosion == nullptr) {
            explosions_.removeLast();
            continue;
        }
        removeExplosion(explosion);
    }
}

void Board::removeBonus(BaseItem *bonus)
{
    if (bonus == nullptr)
        return;

    bonuses_.removeOne(bonus);
    emit bonusesPropertyChanged(bonusesProperty());
    delete bonus;
}

void Board::removeAllBonuses()
{
    while (!bonuses_.isEmpty()) {
        auto bonus = bonuses_.last();
        if (bonus == nullptr) {
            bonuses_.removeLast();
            continue;
        }
        removeBonus(bonus);
    }
}

void Board::removeFirstBonus()
{
    if (bonuses_.isEmpty())
        return;
    auto bonus = bonuses_.first();
    bonuses_.removeFirst();
    emit bonusesPropertyChanged(bonusesProperty());
    delete bonus;
}

void Board::destroyEagle(BaseItem *eagle)
{
    if (eagle == nullptr)
        return;

    int x = eagle->x() - eagle->width() / 6;
    int y = eagle->y() - eagle->height() / 6;
    makeExplosion(x, y, 76, 76, "qrc:/images/explosions/tank_explosion.gif");
    eagle->setImageSource("qrc:/images/eagles/destroyed_eagle.png");
    emit eagleDestroyed();

    if (!playerTanks_.isEmpty()) {
        auto tank = playerTanks_.first();
        if (tank == nullptr) {
            playerTanks_.removeFirst();
            return;
        }
        removePlayerTank(tank);
    }
}

bool Board::setupTile(int row, int column, Tile::Material material)
{
    if (row < 0 || row >= rowCount_ || column < 0 || column >= colCount_)
        return false;

    Tile *tile = this->tile(row, column);
    tile->setMaterial(material);
    if (material == Tile::Bush)
        tile->setZ(1);

    return true;
}

void Board::addPlayerTank(int row, int column, ShootableItem *tank)
{
    if (tank == nullptr)
        return;

    Tile *tile = this->tile(row, column);
    if (tile == nullptr)
        return;

    tank->setX(tile->x());
    tank->setY(tile->y());
    playerTanks_ << tank;

    connect(tank, SIGNAL(shootEmitted(MovableItem*)), this, SLOT(addProjectile(MovableItem*)));

    emit playerTanksPropertyChanged(playerTanksProperty());
}

void Board::addEnemyTank(int row, int column, ShootableItem *tank)
{
    if (tank == nullptr)
        return;

    Tile *tile = this->tile(row, column);
    if (tile == nullptr)
        return;

    tank->setX(tile->x());
    tank->setY(tile->y());
    enemyTanks_ << tank;

    connect(tank, SIGNAL(shootEmitted(MovableItem*)), this, SLOT(addProjectile(MovableItem*)));

    emit enemyTanksPropertyChanged(enemyTanksProperty());
}

void Board::addBonus(int row, int column, BaseItem *bonus)
{
    if (bonus == nullptr)
        return;

    Tile *tile = this->tile(row, column);
    if (tile == nullptr)
        return;

    bonus->setX(tile->x());
    bonus->setY(tile->y());
    bonus->setWidth(tileSize_ * 2);
    bonus->setHeight(tileSize_ * 2);
    bonuses_ << bonus;

    emit bonusesPropertyChanged(bonusesProperty());
}

void Board::onBonusReached(ShootableItem *playerTank, BaseItem *bonus)
{
    if (playerTank == nullptr || bonus == nullptr)
        return;

    Constants::Bonus::BonusType bonusType
            = static_cast<Constants::Bonus::BonusType>(
                bonus->property(Constants::Bonus::Property::Type).toInt());

    emit bonusReached(playerTank, bonusType);
    removeBonus(bonus);
}

void Board::updatePlayerTankPos(int row, int column)
{
    auto tank = playerTanks_.first();
    if (tank == nullptr)
        return;

    auto tile = this->tile(row, column);
    if (tile == nullptr)
        return;

    tank->setX(tile->x());
    tank->setY(tile->y());
    tank->setMovement(false);
    tank->setShooting(false);
    tank->setDirection(MovableItem::North);
    tank->setRotation(0);
}

void Board::update()
{
    for (auto tank : playerTanks_) {
        if (tank != nullptr) {
            tank->move();
            tank->shoot();
        }
    }
    for (auto tank : enemyTanks_) {
        if (tank != nullptr) {
            tank->move();
            tank->shoot();
        }
    }
    for (auto projectile : projectiles_) {
        if (projectile != nullptr)
            projectile->move();
    }
}

void Board::addProjectile(MovableItem *projectile)
{
    if (projectile == nullptr)
        return;

    projectiles_ << projectile;
    emit projectilesPropertyChanged(projectilesProperty());
}

void Board::onExplosionTimeout()
{
    BaseItem *explosion = qobject_cast<BaseItem *>(sender());
    if (explosion != nullptr)
        removeExplosion(explosion);
}

void Board::initialize()
{
    setWidth(tileSize_ * colCount_);
    setHeight(tileSize_ * rowCount_);

    if (makeTiles())
        makeBase();
}

bool Board::makeTiles()
{
    for (int row = 0, currentY = 0; row != rowCount_;
         ++row, currentY += tileSize_) {
        for (int column =0, currentX = 0; column != colCount_;
             ++column, currentX += tileSize_) {
            Tile *tile = new Tile;

            if (tile == nullptr) {
                setHasError(true);
                setErrorString("Board: cannot create tiles objects");
                qDeleteAll(tiles_);
                tiles_.clear();
                return false;
            }

            tile->setWidth(tileSize_);
            tile->setHeight(tileSize_);
            tile->setX(currentX);
            tile->setY(currentY);

            tiles_.push_back(tile);
        }
    }
    return true;
}

void Board::makeBase()
{
    Tile *currentTile;

    currentTile = tile(25, 11);
    currentTile->setMaterial(Tile::Bricks);
    currentTile = tile(25, 14);
    currentTile->setMaterial(Tile::Bricks);
    currentTile = tile(24, 11);
    currentTile->setMaterial(Tile::Bricks);
    currentTile = tile(24, 14);
    currentTile->setMaterial(Tile::Bricks);
    currentTile = tile(23, 11);
    currentTile->setMaterial(Tile::Bricks);
    currentTile = tile(23, 14);
    currentTile->setMaterial(Tile::Bricks);
    currentTile = tile(23, 12);
    currentTile->setMaterial(Tile::Bricks);
    currentTile = tile(23, 13);
    currentTile->setMaterial(Tile::Bricks);

    eagle_.setWidth(tileSize_ * 2);
    eagle_.setHeight(tileSize_ * 2);
    eagle_.setX(tile(24, 12)->x());
    eagle_.setY(tile(24, 12)->y());
    eagle_.setImageSource("qrc:/images/eagles/normal_eagle.png");
}

void Board::makeExplosion(int x, int y, int w, int h, const QString &image)
{
    BaseItem *explosion = new BaseItem;
    if (explosion == nullptr)
        return;

    explosion->setX(x);
    explosion->setY(y);
    explosion->setWidth(w);
    explosion->setHeight(h);
    explosion->setImageSource(image);
    explosions_ << explosion;
    emit explosionsPropertyChanged(explosionsProperty());
    connect(explosion, SIGNAL(imageSourceChanged(QString)), this, SLOT(onExplosionTimeout()));
}

Tile *Board::tile(int row, int column) const
{
    int index = column + row * colCount_;
    if (index < 0 || index >= tiles_.size())
        return nullptr;
    return tiles_.at(index);
}

}  // namespace Base
