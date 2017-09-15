#include "gamecontroller.h"

#include <QDebug>
#include <QFile>
#include <QTimerEvent>

#include <random>

#include "bcsreader.h"

static const int GAME_TIMEOUT = 25;
static const int ENEMY_TANK_APPEAR_TIMEOUT = 5000;
static const int ENEMY_DRIVER_TIMEOUT = 100;
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

void GameController::admitDefeat()
{
    killTimer(gameRythmId_);
    killTimer(enemyTankAppearRythmId_);
    killTimer(enemyDriverRythmId_);
}

void GameController::onPlayerTankDestroyed()
{
    if (informationPanel_->livesCount() == 0) {
        admitDefeat();
        return;
    }

    informationPanel_->setLivesCount(informationPanel_->livesCount() - 1);
    setupPlayerTank();
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

    connect(board_, SIGNAL(eagleDestroyed()), this, SLOT(admitDefeat()));
    connect(board_, SIGNAL(playerTankDestroyed()), this, SLOT(onPlayerTankDestroyed()));
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
    QFile stageFile(":/stages/stage1.xml");
    if (!stageFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open stage file";
        return;
    }

    BCSReader battleCityStageReader(this);
    battleCityStageReader.read(&stageFile);
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
    tank->setChargingInterval(250);

    board_->addPlayerTank(playerRespawn_.first, playerRespawn_.second, tank);
}

void GameController::setupEnemyTanks()
{
    // TODO: read tanks information from XML instead hardcoding
    for (int i = 0; i != 2; ++i) {
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

void GameController::setStageNo(int stageNo)
{
    informationPanel_->setStageNo(stageNo);
}

void GameController::setTile(int row, int column, Tile::Material material)
{
    board_->setupTile(row, column, material);
}
