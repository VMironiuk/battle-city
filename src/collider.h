#ifndef COLLIDER_H
#define COLLIDER_H

#include <QObject>

#include "board.h"
#include "movableitem.h"
#include "tile.h"

class Collider : public QObject
{
    friend class GameController;

    Q_OBJECT
public:
    Collider(QObject *parent = nullptr);
    Collider(const Collider&) = delete;
    Collider &operator=(const Collider&) = delete;

private:
    void checkCollisions(Board *board);

    void checkBoardBoundaries(Board *board);
    void checkBoardBoundariesForTank(Board *board, MovableItem *movableItem);
    void checkBoardBoundariesForProjectile(Board *board, MovableItem *movableItem);

    void checkTileBoundaries(Board *board);
    void checkTileBoundariesForTank(Board *board, MovableItem *movableItem);
    void checkTileBoundariesForTank(MovableItem *movableItem, Tile *tile);
    bool checkTileBoundariesForProjectile(Board *board, MovableItem *movableItem);
    bool checkTileBoundariesForProjectile(MovableItem *movableItem, Tile *tile);

    bool checkNorthDirection(MovableItem *movableItem, Tile *tile);
    bool checkSouthDirection(MovableItem *movableItem, Tile *tile);
    bool checkWestDirection(MovableItem *movableItem, Tile *tile);
    bool checkEastDirection(MovableItem *movableItem, Tile *tile);
    void adjustMovableItemPos(MovableItem *movableItem, Tile *tile, int xOffset, int yOffset);
};

#endif // COLLIDER_H
