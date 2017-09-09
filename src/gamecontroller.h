#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>

#include "board.h"
#include "collider.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController &instance();
    GameController(const GameController&) = delete;
    GameController &operator=(const GameController&) = delete;

    Board *board() { return &board_; }

private slots:
    void checkCollisions();

private:
    GameController(QObject *parent = nullptr);
    ~GameController();

    Board board_;
    QTimer timer_;
    Collider collider_;
};

#endif // GAMECONTROLLER_H
