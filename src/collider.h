#ifndef COLLIDER_H
#define COLLIDER_H

#include <QObject>

#include "board.h"
#include "movableitem.h"
#include "baseitem.h"

class Collider : public QObject
{
    Q_OBJECT
public:
    static Collider &instance();
    Collider(const Collider&) = delete;
    Collider &operator=(const Collider&) = delete;

    Board *board() const { return board_; }
    void setBoard(Board *board);

    bool isCollided(MovableItem *movableItem);

private:
    Collider(QObject *parent = nullptr);
    ~Collider();
    bool isBoardCollided(MovableItem *movableItem);
    bool isTileCollided(MovableItem *movableItem);

    Board *board_;
};

#endif // COLLIDER_H
