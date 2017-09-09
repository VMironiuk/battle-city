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
    void checkBoardBoundaries(Board *board, MovableItem *movableItem);
    void checkTileBoundaries(Board *board);
    void checkTileBoundaries(Board *board, MovableItem *movableItem);
    void checkTileBoundaries(MovableItem *movableItem, Tile *tile);
    void checkNorthDirection(MovableItem *movableItem, Tile *tile);
    void checkSouthDirection(MovableItem *movableItem, Tile *tile);
    void checkWestDirection(MovableItem *movableItem, Tile *tile);
    void checkEastDirection(MovableItem *movableItem, Tile *tile);
    void adjustMovableItemPos(MovableItem *movableItem, Tile *tile, int xOffset, int yOffset);
};

#endif // COLLIDER_H
