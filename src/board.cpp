#include "board.h"

static const int TILE_SIZE = 32;
static const int TILE_COUNT_PER_SIDE = 26;
static const int BOARD_SIZE = TILE_SIZE * TILE_COUNT_PER_SIDE;

Board::Board(QObject *parent) : BaseItem(parent)
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
    Tile *tile = this->tile(row, column);
    tile->setMaterial(material);
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
    setWidth(BOARD_SIZE);
    setHeight(BOARD_SIZE);

    makeTiles();
    makeBase();
    makeTanks();
}

void Board::makeTiles()
{
    for (int row = 0, currentY = 0; row != TILE_COUNT_PER_SIDE;
         ++row, currentY += TILE_SIZE) {
        for (int column =0, currentX = 0; column != TILE_COUNT_PER_SIDE;
             ++column, currentX += TILE_SIZE) {
            Tile *tile = new Tile;
            tile->setWidth(TILE_SIZE);
            tile->setHeight(TILE_SIZE);
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

    eagle_.setWidth(TILE_SIZE * 2);
    eagle_.setHeight(TILE_SIZE * 2);
    eagle_.setX(tile(24, 12)->x());
    eagle_.setY(tile(24, 12)->y());
    eagle_.setImageSource("qrc:/images/eagles/normal_eagle.png");
}

void Board::makeTanks()
{
    // TODO: just for testing. Update this code later

    // Player tank
    ShootableItem *tank = new ShootableItem;
    tank->setWidth(TILE_SIZE * 2);
    tank->setHeight(TILE_SIZE * 2);

    Tile *t = tile(24, 9);
    tank->setX(t->x());
    tank->setY(t->y());

    tank->setImageSource("qrc:/images/tanks/player/simple_tank.png");
    tank->setDirection(MovableItem::North);
    tank->setMovement(false);
    tank->setShooting(false);
    tank->setProperty("battleCitySide", "player");

    playerTanks_ << tank;

    connect(tank, SIGNAL(shootEmitted(MovableItem*)), this, SLOT(addProjectile(MovableItem*)));

    // Enemy tank
    tank = new ShootableItem;
    tank->setWidth(TILE_SIZE * 2);
    tank->setHeight(TILE_SIZE * 2);

    t = tile(0, 12);
    tank->setX(t->x());
    tank->setY(t->y());

    tank->setImageSource("qrc:/images/tanks/enemy/simple_tank.png");
    tank->setProperty("battleCitySide", "enemy");

    enemyTanks_ << tank;

    connect(tank, SIGNAL(shootEmitted(MovableItem*)), this, SLOT(addProjectile(MovableItem*)));
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
    int index = column + row * TILE_COUNT_PER_SIDE;
    if (index < 0 || index >= tiles_.size())
        return nullptr;
    return tiles_.at(index);
}
