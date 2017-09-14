#include "gamecontroller.h"

#include <QTimerEvent>

#include <random>

static const int GAME_TIMEOUT = 25;
static const int ENEMY_TANK_APPEAR_TIMEOUT = 5000;
static const int ENEMY_DRIVER_TIMEOUT = 1000;
static const int BOARD_ROWS = 26;
static const int BOARD_COLS = 26;
static const int BOARD_TILE_SIZE = 32;

GameController &GameController::instance()
{
    static GameController gc;
    return gc;
}

void GameController::timerEvent(QTimerEvent *event)
{
    if (gameRythmId_ == event->timerId()) {
        board_->update();
        checkCollisions();
    } else if (enemyTankAppearRythmId_ == event->timerId()) {
        moveEnemyTankToBoard();
    } else if (enemyDriverRythmId_ == event->timerId()) {
        updateEnemyDrivers();
    }
}

void GameController::removeEnemyDriver()
{
    EnemyDriver *driver = qobject_cast<EnemyDriver *>(sender());
    if (driver == nullptr)
        return;
    enemyDrivers_.removeOne(driver);
    driver->deleteLater();
}

GameController::GameController(QObject *parent)
    : QObject(parent),
      board_(new Board(BOARD_ROWS, BOARD_COLS, BOARD_TILE_SIZE)),
      informationPanel_(new InformationPanel)
{
    setupRespawns();
    setupBoard();
    setupPlayerTank();
    setupEnemyTanks();
    moveEnemyTankToBoard();

    gameRythmId_ = startTimer(GAME_TIMEOUT);
    enemyTankAppearRythmId_ = startTimer(ENEMY_TANK_APPEAR_TIMEOUT);
    enemyDriverRythmId_ = startTimer(ENEMY_DRIVER_TIMEOUT);
}

GameController::~GameController()
{
    delete board_;
    delete informationPanel_;
}

void GameController::checkCollisions()
{
    collider_.checkCollisions(board_);
}

void GameController::updateEnemyDrivers()
{
    for (auto driver : enemyDrivers_)
        driver->update();
}

void GameController::setupRespawns()
{
    playerRespawn_  = QPair<int, int>(24, 9);

    enemyRespawns_ << QPair<int, int>(0, 0);
    enemyRespawns_ << QPair<int, int>(0, 12);
    enemyRespawns_ << QPair<int, int>(0, 24);
}

void GameController::setupBoard()
{
    // TODO: read tiles information from XML instead hardcoding

    // Bricks walls
    // Wall 1
    board_->setupTile(2, 2, Tile::Bricks);
    board_->setupTile(2, 3, Tile::Bricks);
    board_->setupTile(3, 2, Tile::Bricks);
    board_->setupTile(3, 3, Tile::Bricks);
    board_->setupTile(4, 2, Tile::Bricks);
    board_->setupTile(4, 3, Tile::Bricks);
    board_->setupTile(5, 2, Tile::Bricks);
    board_->setupTile(5, 3, Tile::Bricks);
    board_->setupTile(6, 2, Tile::Bricks);
    board_->setupTile(6, 3, Tile::Bricks);
    board_->setupTile(7, 2, Tile::Bricks);
    board_->setupTile(7, 3, Tile::Bricks);
    board_->setupTile(8, 2, Tile::Bricks);
    board_->setupTile(8, 3, Tile::Bricks);
    board_->setupTile(9, 2, Tile::Bricks);
    board_->setupTile(9, 3, Tile::Bricks);
    board_->setupTile(10, 2, Tile::Bricks);
    board_->setupTile(10, 3, Tile::Bricks);

    // Wall 2
    board_->setupTile(2, 6, Tile::Bricks);
    board_->setupTile(2, 7, Tile::Bricks);
    board_->setupTile(3, 6, Tile::Bricks);
    board_->setupTile(3, 7, Tile::Bricks);
    board_->setupTile(4, 6, Tile::Bricks);
    board_->setupTile(4, 7, Tile::Bricks);
    board_->setupTile(5, 6, Tile::Bricks);
    board_->setupTile(5, 7, Tile::Bricks);
    board_->setupTile(6, 6, Tile::Bricks);
    board_->setupTile(6, 7, Tile::Bricks);
    board_->setupTile(7, 6, Tile::Bricks);
    board_->setupTile(7, 7, Tile::Bricks);
    board_->setupTile(8, 6, Tile::Bricks);
    board_->setupTile(8, 7, Tile::Bricks);
    board_->setupTile(9, 6, Tile::Bricks);
    board_->setupTile(9, 7, Tile::Bricks);
    board_->setupTile(10, 6, Tile::Bricks);
    board_->setupTile(10, 7, Tile::Bricks);

    // Wall 3
    board_->setupTile(2, 10, Tile::Bricks);
    board_->setupTile(2, 11, Tile::Bricks);
    board_->setupTile(3, 10, Tile::Bricks);
    board_->setupTile(3, 11, Tile::Bricks);
    board_->setupTile(4, 10, Tile::Bricks);
    board_->setupTile(4, 11, Tile::Bricks);
    board_->setupTile(5, 10, Tile::Bricks);
    board_->setupTile(5, 11, Tile::Bricks);
    board_->setupTile(6, 10, Tile::Bricks);
    board_->setupTile(6, 11, Tile::Bricks);
    board_->setupTile(7, 10, Tile::Bricks);
    board_->setupTile(7, 11, Tile::Bricks);
    board_->setupTile(8, 10, Tile::Bricks);
    board_->setupTile(8, 11, Tile::Bricks);

    // Wall 4
    board_->setupTile(2, 14, Tile::Bricks);
    board_->setupTile(2, 15, Tile::Bricks);
    board_->setupTile(3, 14, Tile::Bricks);
    board_->setupTile(3, 15, Tile::Bricks);
    board_->setupTile(4, 14, Tile::Bricks);
    board_->setupTile(4, 15, Tile::Bricks);
    board_->setupTile(5, 14, Tile::Bricks);
    board_->setupTile(5, 15, Tile::Bricks);
    board_->setupTile(6, 14, Tile::Bricks);
    board_->setupTile(6, 15, Tile::Bricks);
    board_->setupTile(7, 14, Tile::Bricks);
    board_->setupTile(7, 15, Tile::Bricks);
    board_->setupTile(8, 14, Tile::Bricks);
    board_->setupTile(8, 15, Tile::Bricks);

    // Wall 5
    board_->setupTile(2, 18, Tile::Bricks);
    board_->setupTile(2, 19, Tile::Bricks);
    board_->setupTile(3, 18, Tile::Bricks);
    board_->setupTile(3, 19, Tile::Bricks);
    board_->setupTile(4, 18, Tile::Bricks);
    board_->setupTile(4, 19, Tile::Bricks);
    board_->setupTile(5, 18, Tile::Bricks);
    board_->setupTile(5, 19, Tile::Bricks);
    board_->setupTile(6, 18, Tile::Bricks);
    board_->setupTile(6, 19, Tile::Bricks);
    board_->setupTile(7, 18, Tile::Bricks);
    board_->setupTile(7, 19, Tile::Bricks);
    board_->setupTile(8, 18, Tile::Bricks);
    board_->setupTile(8, 19, Tile::Bricks);
    board_->setupTile(9, 18, Tile::Bricks);
    board_->setupTile(9, 19, Tile::Bricks);
    board_->setupTile(10, 18, Tile::Bricks);
    board_->setupTile(10, 19, Tile::Bricks);

    // Wall 6
    board_->setupTile(2, 22, Tile::Bricks);
    board_->setupTile(2, 23, Tile::Bricks);
    board_->setupTile(3, 22, Tile::Bricks);
    board_->setupTile(3, 23, Tile::Bricks);
    board_->setupTile(4, 22, Tile::Bricks);
    board_->setupTile(4, 23, Tile::Bricks);
    board_->setupTile(5, 22, Tile::Bricks);
    board_->setupTile(5, 23, Tile::Bricks);
    board_->setupTile(6, 22, Tile::Bricks);
    board_->setupTile(6, 23, Tile::Bricks);
    board_->setupTile(7, 22, Tile::Bricks);
    board_->setupTile(7, 23, Tile::Bricks);
    board_->setupTile(8, 22, Tile::Bricks);
    board_->setupTile(8, 23, Tile::Bricks);
    board_->setupTile(9, 22, Tile::Bricks);
    board_->setupTile(9, 23, Tile::Bricks);
    board_->setupTile(10, 22, Tile::Bricks);
    board_->setupTile(10, 23, Tile::Bricks);

    // Wall 7
    board_->setupTile(11, 10, Tile::Bricks);
    board_->setupTile(11, 11, Tile::Bricks);
    board_->setupTile(12, 10, Tile::Bricks);
    board_->setupTile(12, 11, Tile::Bricks);

    // Wall 8
    board_->setupTile(11, 14, Tile::Bricks);
    board_->setupTile(11, 15, Tile::Bricks);
    board_->setupTile(12, 14, Tile::Bricks);
    board_->setupTile(12, 15, Tile::Bricks);

    // Wall 9
    board_->setupTile(13, 4, Tile::Bricks);
    board_->setupTile(14, 4, Tile::Bricks);
    board_->setupTile(13, 5, Tile::Bricks);
    board_->setupTile(14, 5, Tile::Bricks);
    board_->setupTile(13, 6, Tile::Bricks);
    board_->setupTile(14, 6, Tile::Bricks);
    board_->setupTile(13, 7, Tile::Bricks);
    board_->setupTile(14, 7, Tile::Bricks);

    // Wall 10
    board_->setupTile(13, 18, Tile::Bricks);
    board_->setupTile(14, 18, Tile::Bricks);
    board_->setupTile(13, 19, Tile::Bricks);
    board_->setupTile(14, 19, Tile::Bricks);
    board_->setupTile(13, 20, Tile::Bricks);
    board_->setupTile(14, 20, Tile::Bricks);
    board_->setupTile(13, 21, Tile::Bricks);
    board_->setupTile(14, 21, Tile::Bricks);

    // Wall 11
    board_->setupTile(17, 2, Tile::Bricks);
    board_->setupTile(17, 3, Tile::Bricks);
    board_->setupTile(18, 2, Tile::Bricks);
    board_->setupTile(18, 3, Tile::Bricks);
    board_->setupTile(19, 2, Tile::Bricks);
    board_->setupTile(19, 3, Tile::Bricks);
    board_->setupTile(20, 2, Tile::Bricks);
    board_->setupTile(20, 3, Tile::Bricks);
    board_->setupTile(21, 2, Tile::Bricks);
    board_->setupTile(21, 3, Tile::Bricks);
    board_->setupTile(22, 2, Tile::Bricks);
    board_->setupTile(22, 3, Tile::Bricks);
    board_->setupTile(23, 2, Tile::Bricks);
    board_->setupTile(23, 3, Tile::Bricks);

    // Wall 11
    board_->setupTile(17, 6, Tile::Bricks);
    board_->setupTile(17, 7, Tile::Bricks);
    board_->setupTile(18, 6, Tile::Bricks);
    board_->setupTile(18, 7, Tile::Bricks);
    board_->setupTile(19, 6, Tile::Bricks);
    board_->setupTile(19, 7, Tile::Bricks);
    board_->setupTile(20, 6, Tile::Bricks);
    board_->setupTile(20, 7, Tile::Bricks);
    board_->setupTile(21, 6, Tile::Bricks);
    board_->setupTile(21, 7, Tile::Bricks);
    board_->setupTile(22, 6, Tile::Bricks);
    board_->setupTile(22, 7, Tile::Bricks);
    board_->setupTile(23, 6, Tile::Bricks);
    board_->setupTile(23, 7, Tile::Bricks);

    // Wall 12
    board_->setupTile(15, 10, Tile::Bricks);
    board_->setupTile(15, 11, Tile::Bricks);
    board_->setupTile(16, 10, Tile::Bricks);
    board_->setupTile(16, 11, Tile::Bricks);
    board_->setupTile(17, 10, Tile::Bricks);
    board_->setupTile(17, 11, Tile::Bricks);
    board_->setupTile(18, 10, Tile::Bricks);
    board_->setupTile(18, 11, Tile::Bricks);
    board_->setupTile(19, 10, Tile::Bricks);
    board_->setupTile(19, 11, Tile::Bricks);
    board_->setupTile(20, 10, Tile::Bricks);
    board_->setupTile(20, 11, Tile::Bricks);

    // Wall 13
    board_->setupTile(16, 12, Tile::Bricks);
    board_->setupTile(16, 13, Tile::Bricks);
    board_->setupTile(17, 12, Tile::Bricks);
    board_->setupTile(17, 13, Tile::Bricks);

    // Wall 14
    board_->setupTile(15, 14, Tile::Bricks);
    board_->setupTile(15, 15, Tile::Bricks);
    board_->setupTile(16, 14, Tile::Bricks);
    board_->setupTile(16, 15, Tile::Bricks);
    board_->setupTile(17, 14, Tile::Bricks);
    board_->setupTile(17, 15, Tile::Bricks);
    board_->setupTile(18, 14, Tile::Bricks);
    board_->setupTile(18, 15, Tile::Bricks);
    board_->setupTile(19, 14, Tile::Bricks);
    board_->setupTile(19, 15, Tile::Bricks);
    board_->setupTile(20, 14, Tile::Bricks);
    board_->setupTile(20, 15, Tile::Bricks);

    // Wall 15
    board_->setupTile(17, 18, Tile::Bricks);
    board_->setupTile(17, 19, Tile::Bricks);
    board_->setupTile(18, 18, Tile::Bricks);
    board_->setupTile(18, 19, Tile::Bricks);
    board_->setupTile(19, 18, Tile::Bricks);
    board_->setupTile(19, 19, Tile::Bricks);
    board_->setupTile(20, 18, Tile::Bricks);
    board_->setupTile(20, 19, Tile::Bricks);
    board_->setupTile(21, 18, Tile::Bricks);
    board_->setupTile(21, 19, Tile::Bricks);
    board_->setupTile(22, 18, Tile::Bricks);
    board_->setupTile(22, 19, Tile::Bricks);
    board_->setupTile(23, 18, Tile::Bricks);
    board_->setupTile(23, 19, Tile::Bricks);

    // Wall 16
    board_->setupTile(17, 22, Tile::Bricks);
    board_->setupTile(17, 23, Tile::Bricks);
    board_->setupTile(18, 22, Tile::Bricks);
    board_->setupTile(18, 23, Tile::Bricks);
    board_->setupTile(19, 22, Tile::Bricks);
    board_->setupTile(19, 23, Tile::Bricks);
    board_->setupTile(20, 22, Tile::Bricks);
    board_->setupTile(20, 23, Tile::Bricks);
    board_->setupTile(21, 22, Tile::Bricks);
    board_->setupTile(21, 23, Tile::Bricks);
    board_->setupTile(22, 22, Tile::Bricks);
    board_->setupTile(22, 23, Tile::Bricks);
    board_->setupTile(23, 22, Tile::Bricks);
    board_->setupTile(23, 23, Tile::Bricks);

    // Concrete walls
    // Wall 1
    board_->setupTile(6, 12, Tile::Concrete);
    board_->setupTile(6, 13, Tile::Concrete);
    board_->setupTile(7, 12, Tile::Concrete);
    board_->setupTile(7, 13, Tile::Concrete);

    // Wall 2
    board_->setupTile(14, 0, Tile::Concrete);
    board_->setupTile(14, 1, Tile::Concrete);

    // Wall 3
    board_->setupTile(14, 24, Tile::Concrete);
    board_->setupTile(14, 25, Tile::Concrete);
}

void GameController::setupPlayerTank()
{
    ShootableItem *tank = new ShootableItem;
    tank->setWidth(BOARD_TILE_SIZE * 2);
    tank->setHeight(BOARD_TILE_SIZE * 2);
    tank->setImageSource("qrc:/images/tanks/player/simple_tank.png");
    tank->setDirection(MovableItem::North);
    tank->setMovement(false);
    tank->setShooting(false);
    tank->setProperty("battleCitySide", "player");

    board_->addPlayerTank(playerRespawn_.first, playerRespawn_.second, tank);
}

void GameController::setupEnemyTanks()
{
    // TODO: read tanks information from XML instead hardcoding
    for (int i = 0; i != 20; ++i) {
        ShootableItem *tank = new ShootableItem;
        tank->setWidth(BOARD_TILE_SIZE * 2);
        tank->setHeight(BOARD_TILE_SIZE * 2);
        tank->setImageSource("qrc:/images/tanks/enemy/simple_tank.png");
        tank->setProperty("battleCitySide", "enemy");

        informationPanel_->addTank(tank);
    }
}

void GameController::moveEnemyTankToBoard()
{
    static const int high = enemyRespawns_.count() - 1;
    static const int low = 0;

    if (!informationPanel_->hasNextTank())
        return;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(low, high);
    int index = dist(rng);

    int respawnX = enemyRespawns_.at(index).first;
    int respawnY = enemyRespawns_.at(index).second;

    ShootableItem *tank = informationPanel_->nextTank();
    EnemyDriver *driver = new EnemyDriver(tank);
    connect(driver, SIGNAL(wannaDie()), this, SLOT(removeEnemyDriver()));
    enemyDrivers_ << driver;
    board_->addEnemyTank(respawnX, respawnY, tank);
}
