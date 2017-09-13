#include "board.h"

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

void Board::removePlayerTank(ShootableItem *playerTank)
{
    int x = playerTank->x() - playerTank->width() / 6;
    int y = playerTank->y() - playerTank->height() / 6;
    makeExplosion(x, y, 76, 76, "qrc:/images/explosions/tank_explosion.gif");

    playerTanks_.removeAll(playerTank);
    emit playerTanksPropertyChanged(playerTanksProperty());
    delete playerTank;
}

void Board::removeEnemyTank(ShootableItem *enemyTank)
{
    int x = enemyTank->x() - enemyTank->width() / 6;
    int y = enemyTank->y() - enemyTank->height() / 6;
    makeExplosion(x, y, 76, 76, "qrc:/images/explosions/tank_explosion.gif");

    enemyTanks_.removeAll(enemyTank);
    emit enemyTanksPropertyChanged(enemyTanksProperty());
    delete enemyTank;
}

void Board::removeProjectile(MovableItem *projectile)
{
    int x = projectile->x() - projectile->width();
    int y = projectile->y() - projectile->height();
    makeExplosion(x, y, 44, 44, "qrc:/images/explosions/projectile_explosion.gif");

    projectiles_.removeAll(projectile);
    emit projectilesPropertyChanged(projectilesProperty());
    delete projectile;
}

void Board::removeExplosion(BaseItem *explosion)
{
    explosions_.removeAll(explosion);
    emit explosionsPropertyChanged(explosionsProperty());
    delete explosion;
}

void Board::destroyEagle(BaseItem *eagle)
{
    int x = eagle->x() - eagle->width() / 6;
    int y = eagle->y() - eagle->height() / 6;
    makeExplosion(x, y, 76, 76, "qrc:/images/explosions/tank_explosion.gif");

    eagle->setImageSource("qrc:/images/eagles/destroyed_eagle.png");
}

void Board::setupTile(int row, int column, Tile::Material material)
{
    Q_ASSERT(row >= 0 && row < rowCount_);
    Q_ASSERT(column >= 0 && column < colCount_);

    Tile *tile = this->tile(row, column);
    tile->setMaterial(material);
}

void Board::addPlayerTank(int row, int column, ShootableItem *tank)
{
    Tile *tile = this->tile(row, column);
    tank->setX(tile->x());
    tank->setY(tile->y());
    playerTanks_ << tank;

    connect(tank, SIGNAL(shootEmitted(MovableItem*)), this, SLOT(addProjectile(MovableItem*)));

    emit playerTanksPropertyChanged(playerTanksProperty());
}

void Board::addEnemyTank(int row, int column, ShootableItem *tank)
{
    Tile *tile = this->tile(row, column);
    tank->setX(tile->x());
    tank->setY(tile->y());
    enemyTanks_ << tank;

    connect(tank, SIGNAL(shootEmitted(MovableItem*)), this, SLOT(addProjectile(MovableItem*)));

    emit enemyTanksPropertyChanged(enemyTanksProperty());
}

void Board::update()
{
    for (auto tank : playerTanks_) {
        tank->move();
        tank->shoot();
    }
    for (auto projectile : projectiles_)
        projectile->move();
}

void Board::addProjectile(MovableItem *projectile)
{
    projectiles_ << projectile;
    emit projectilesPropertyChanged(projectilesProperty());
}

void Board::onExplosionTimeout()
{
    BaseItem *explosion = qobject_cast<BaseItem *>(sender());
    if (explosion)
        removeExplosion(explosion);
}

void Board::initialize()
{
    setWidth(tileSize_ * colCount_);
    setHeight(tileSize_ * rowCount_);

    makeTiles();
    makeBase();
}

void Board::makeTiles()
{
    for (int row = 0, currentY = 0; row != rowCount_;
         ++row, currentY += tileSize_) {
        for (int column =0, currentX = 0; column != colCount_;
             ++column, currentX += tileSize_) {
            Tile *tile = new Tile;
            tile->setWidth(tileSize_);
            tile->setHeight(tileSize_);
            tile->setX(currentX);
            tile->setY(currentY);

            tiles_.push_back(tile);
        }
    }
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
