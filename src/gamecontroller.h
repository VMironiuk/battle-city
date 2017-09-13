#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>

#include "board.h"
#include "collider.h"
#include "informationpanel.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController &instance();
    GameController(const GameController&) = delete;
    GameController &operator=(const GameController&) = delete;

    Board *board() { return &board_; }
    InformationPanel *informationPanel() { return &informationPanel_; }

private slots:
    void checkCollisions();

private:
    GameController(QObject *parent = nullptr);
    ~GameController();

    void setupRespawns();
    void setupBoard();
    void setupPlayerTank();
    void setupEnemyTanks();

    Board board_;
    InformationPanel informationPanel_;
    QTimer timer_;
    Collider collider_;
    QPair<int, int> playerRespawn_;
    QList<QPair<int, int>> enemyRespawns_;
};

#endif // GAMECONTROLLER_H
