#include "gamecontroller.h"

#include <QDebug>
#include <QFile>
#include <QTimerEvent>

#include "bcsreader.h"
#include "global.h"
#include "stageiterator.h"

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

void GameController::setWon(bool won)
{
    if (won_ == won)
        return;
    won_ = won;
    emit wonChanged(won_);
}

bool GameController::setupStage()
{
    QFile stageFile(StageIterator::nextStageSrc());
    if (!stageFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setHasError(true);
        setErrorString("GameController: cannot open stage file " + stageFile.fileName());
        return false;
    }

    BCSReader battleCityStageReader(this);
    if (!battleCityStageReader.read(&stageFile)) {
        setHasError(true);
        setErrorString(battleCityStageReader.errorString());
        return false;
    }

    moveEnemyTankToBoard();
    if (board_->playerTanks().isEmpty())
          setupPlayerTank();
    else
        board_->updatePlayerTankPos(playerRespawn_.first, playerRespawn_.second);

    return true;
}

void GameController::startStage()
{
    gameRythmId_ = startTimer(GAME_TIMEOUT);
    enemyTankAppearRythmId_ = startTimer(ENEMY_TANK_APPEAR_TIMEOUT);
    enemyDriverRythmId_ = startTimer(ENEMY_DRIVER_TIMEOUT);
}

void GameController::stopStage()
{
    killTimer(gameRythmId_);
    killTimer(enemyTankAppearRythmId_);
    killTimer(enemyDriverRythmId_);
}

void GameController::freeStage()
{
    if (board_ != nullptr)
        board_->clear();

    if (informationPanel_ != nullptr)
        informationPanel_->clear();
}

void GameController::timerEvent(QTimerEvent *event)
{
    if (gameRythmId_ == event->timerId()) {
        if (board_ != nullptr)
            board_->update();
        checkCollisions();
        checkStageFinished();
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
    won_ = false;
    if (informationPanel_ != nullptr)
        informationPanel_->setLivesCount(0);
    StageIterator::reset();
    emit stageFinished();
}

void GameController::onPlayerTankDestroyed()
{
    if (informationPanel_ == nullptr)
        return;

    if (informationPanel_->livesCount() == 0) {
        admitDefeat();
        return;
    }

    informationPanel_->setLivesCount(informationPanel_->livesCount() - 1);
    setupPlayerTank();
}

void GameController::onEnemyTankDestroyed(int tankValue)
{
    gameResult_.accumulate(tankValue);
}

void GameController::onShowBonusRequest()
{
    BaseItem *bonus = new BaseItem;
    if (bonus == nullptr)
        return;

    Constants::Bonus::BonusType bonusType
            = static_cast<Constants::Bonus::BonusType>(randomNumber(0, 5));
    bonus->setProperty(Constants::Bonus::Property::Type, bonusType);

    switch (bonusType) {
    case Constants::Bonus::Grenade:
        bonus->setImageSource("qrc:/images/bonuses/grenade.png");
        break;
    case Constants::Bonus::Helmet:
        bonus->setImageSource("qrc:/images/bonuses/helmet.png");
        break;
    case Constants::Bonus::Shovel:
        bonus->setImageSource("qrc:/images/bonuses/shovel.png");
        break;
    case Constants::Bonus::Star:
        bonus->setImageSource("qrc:/images/bonuses/star.png");
        break;
    case Constants::Bonus::Tank:
        bonus->setImageSource("qrc:/images/bonuses/tank.png");
        break;
    case Constants::Bonus::Timer:
        bonus->setImageSource("qrc:/images/bonuses/timer.png");
        break;
    default:
        // TODO: error occurs
        break;
    }

    int row = randomNumber(0, 21);
    int column = randomNumber(0, 24);
    if (board_ != nullptr)
        board_->addBonus(row, column, bonus);
}

void GameController::onHideBonusRequest()
{
    if (board_ != nullptr)
        board_->removeFirstBonus();
}

void GameController::onBonusReached(ShootableItem *playerTank,
                                    Constants::Bonus::BonusType bonusType)
{
    if (playerTank == nullptr)
        return;

    static const int bonusValue = 500;
    switch (bonusType) {
    case Constants::Bonus::Grenade:
        gameResult_.appendPoints(bonusValue);
        if (board_ != nullptr)
            board_->removeAllEnemyTanks();
        break;
    case Constants::Bonus::Helmet:
        gameResult_.appendPoints(bonusValue);
        // TODO: add implementation
        qDebug() << "This bonus not implemented yet";
        break;
    case Constants::Bonus::Shovel:
        gameResult_.appendPoints(bonusValue);
        // TODO: add implementation
        qDebug() << "This bonus not implemented yet";
        break;
    case Constants::Bonus::Star:
        gameResult_.appendPoints(bonusValue);
        improvePlayerTank(playerTank);
        break;
    case Constants::Bonus::Tank:
        gameResult_.appendPoints(bonusValue);
        if (informationPanel_ != nullptr)
            informationPanel_->setLivesCount(informationPanel_->livesCount() + 1);
        break;
    case Constants::Bonus::Timer:
        gameResult_.appendPoints(bonusValue);
        // TODO: add implementation
        qDebug() << "This bonus not implemented yet";
        break;
    default:
        break;
    }
}

GameController::GameController(QObject *parent)
    : BCObject(parent),
      board_(new Board(BOARD_ROWS, BOARD_COLS, BOARD_TILE_SIZE)),
      informationPanel_(new InformationPanel)
{
    if (!check())
        return;

    setupRespawns();

    connect(board_, SIGNAL(eagleDestroyed()), this, SLOT(admitDefeat()));
    connect(board_, SIGNAL(playerTankDestroyed()), this, SLOT(onPlayerTankDestroyed()));
    connect(board_, SIGNAL(enemyTankDestroyed(int)), this, SLOT(onEnemyTankDestroyed(int)));
    connect(board_, SIGNAL(bonusReached(ShootableItem*,Constants::Bonus::BonusType)),
            this, SLOT(onBonusReached(ShootableItem*,Constants::Bonus::BonusType)));
    connect(&bonusTimer_, SIGNAL(showBonusRequest()), this, SLOT(onShowBonusRequest()));
    connect(&bonusTimer_, SIGNAL(hideBonusRequest()), this, SLOT(onHideBonusRequest()));
}

GameController::~GameController()
{
    delete board_;
    delete informationPanel_;
}

bool GameController::check()
{
    if (board_ == nullptr) {
        setHasError(true);
        setErrorString("GameController: cannot create Board object");
        return false;
    }

    if (board_->hasError()) {
        setHasError(board_->hasError());
        setErrorString(board_->errorString());
        delete board_;
        return false;
    }

    if (informationPanel_ == nullptr) {
        setHasError(true);
        setErrorString("GameController: cannot create InformationPanel object");
        delete board_;
        return false;
    }

    return true;
}

void GameController::checkCollisions()
{
    collider_.checkCollisions(board_);
}

void GameController::checkStageFinished()
{
    if (informationPanel_ == nullptr || board_ == nullptr)
        return;

    if (informationPanel_->isEmpty() && board_->enemyTanks().isEmpty()) {
        won_ = true;
        board_->clearMap();
        emit stageFinished();
    }
}

void GameController::updateEnemyDrivers()
{
    for (auto driver : enemyDrivers_) {
        if (driver != nullptr)
            driver->update();
    }
}

void GameController::setupRespawns()
{
    playerRespawn_  = QPair<int, int>(24, 9);

    enemyRespawns_ << QPair<int, int>(0, 0);
    enemyRespawns_ << QPair<int, int>(0, 12);
    enemyRespawns_ << QPair<int, int>(0, 24);
}

void GameController::setupPlayerTank()
{
    ShootableItem *tank = new ShootableItem;
    if (tank == nullptr)
        return;

    tank->setWidth(BOARD_TILE_SIZE * 2);
    tank->setHeight(BOARD_TILE_SIZE * 2);
    tank->setImageSource("qrc:/images/tanks/player/simple_tank.png");
    tank->setDirection(MovableItem::North);
    tank->setMovement(false);
    tank->setShooting(false);
    tank->setChargingInterval(250);
    tank->setProperty(Constants::Property::Belligerent, Constants::Belligerent::Player);
    tank->setProperty(Constants::PlayerTank::Property::Improvement,
                      Constants::PlayerTank::Improvement::NoStars);

    board_->addPlayerTank(playerRespawn_.first, playerRespawn_.second, tank);
}

void GameController::moveEnemyTankToBoard()
{
    if (informationPanel_ == nullptr || board_ == nullptr)
        return;

    static const int high = enemyRespawns_.count() - 1;
    static const int low = 0;

    if (!informationPanel_->hasNextTank())
        return;

    int index = randomNumber(low, high);
    int respawnX = enemyRespawns_.at(index).first;
    int respawnY = enemyRespawns_.at(index).second;

    ShootableItem *tank = informationPanel_->nextTank();
    if (tank == nullptr)
        return;

    tank->setWidth(BOARD_TILE_SIZE * 2);
    tank->setHeight(BOARD_TILE_SIZE * 2);

    EnemyDriver *driver = new EnemyDriver(tank);
    if (driver != nullptr) {
        connect(driver, SIGNAL(wannaDie()), this, SLOT(removeEnemyDriver()));
        enemyDrivers_ << driver;
    }
    board_->addEnemyTank(respawnX, respawnY, tank);
}

void GameController::setStageNo(int stageNo)
{
    if (informationPanel_ != nullptr)
        informationPanel_->setStageNo(stageNo);
}

bool GameController::setTile(int row, int column, Tile::Material material)
{
    return board_->setupTile(row, column, material);
}

void GameController::addEnemyTank(ShootableItem *tank)
{
    if (informationPanel_ != nullptr)
        informationPanel_->addTank(tank);
}

void GameController::improvePlayerTank(ShootableItem *tank)
{
    if (tank == nullptr)
        return;

    if (tank->property(Constants::PlayerTank::Property::Improvement).toString()
            == Constants::PlayerTank::Improvement::NoStars) {
        tank->setProperty(Constants::PlayerTank::Property::Improvement,
                          Constants::PlayerTank::Improvement::OneStar);
        tank->setImageSource("qrc:/images/tanks/player/one_star_tank.png");
        tank->setShotMode(ShootableItem::FastShot);
    } else if (tank->property(Constants::PlayerTank::Property::Improvement).toString()
               == Constants::PlayerTank::Improvement::OneStar) {
        tank->setProperty(Constants::PlayerTank::Property::Improvement,
                          Constants::PlayerTank::Improvement::TwoStars);
        tank->setImageSource("qrc:/images/tanks/player/two_stars_tank.png");
        tank->setShotMode(ShootableItem::BurstShot);
    } else if (tank->property(Constants::PlayerTank::Property::Improvement).toString()
               == Constants::PlayerTank::Improvement::TwoStars) {
        tank->setProperty(Constants::PlayerTank::Property::Improvement,
                          Constants::PlayerTank::Improvement::ThreeStars);
        tank->setImageSource("qrc:/images/tanks/player/three_stars_tank.png");
        tank->setShotMode(ShootableItem::PowerfulShot);
    }
}
