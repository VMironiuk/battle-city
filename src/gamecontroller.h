#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

#include "board.h"
#include "collider.h"
#include "enemydriver.h"
#include "informationpanel.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController &instance();
    GameController(const GameController&) = delete;
    GameController &operator=(const GameController&) = delete;

    Board *board() { return board_; }
    InformationPanel *informationPanel() { return informationPanel_; }

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void removeEnemyDriver();

private:
    GameController(QObject *parent = nullptr);
    ~GameController();

    void checkCollisions();
    void updateEnemyDrivers();
    void setupRespawns();
    void setupBoard();
    void setupPlayerTank();
    void setupEnemyTanks();
    void moveEnemyTankToBoard();

    Board *board_;
    InformationPanel *informationPanel_;
    Collider collider_;
    QPair<int, int> playerRespawn_;
    QList<QPair<int, int>> enemyRespawns_;
    QList<EnemyDriver *> enemyDrivers_;
    int gameRythmId_;
    int enemyTankAppearRythmId_;
    int enemyDriverRythmId_;
};

#endif // GAMECONTROLLER_H
