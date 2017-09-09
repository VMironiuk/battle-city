#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>

#include "board.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController &instance();
    GameController(const GameController&) = delete;
    GameController &operator=(const GameController&) = delete;

    Board *board() { return &board_; }

private:
    GameController(QObject *parent = nullptr);
    ~GameController();

    Board board_;
    QTimer timer_;
};

#endif // GAMECONTROLLER_H
