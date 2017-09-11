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
    void checkBoardBoundariesForTank(Board *board, MovableItem *tank);
    void checkBoardBoundariesForProjectile(Board *board, MovableItem *projectile);

    void checkTileBoundaries(Board *board);
    void checkTileBoundariesForTank(Board *board, MovableItem *tank);
    void checkTileBoundariesForTank(MovableItem *tank, Tile *tile);
    void checkTileBoundariesForProjectile(Board *board, MovableItem *projectile);
    bool checkTileBoundariesForProjectile(MovableItem *projectile, Tile *tile);

    bool checkNorthDirectionAboutTile(MovableItem *movableItem, Tile *tile);
    bool checkSouthDirectionAboutTile(MovableItem *movableItem, Tile *tile);
    bool checkWestDirectionAboutTile(MovableItem *movableItem, Tile *tile);
    bool checkEastDirectionAboutTile(MovableItem *movableItem, Tile *tile);

    void adjustMovableItemPos(MovableItem *movableItem, Tile *tile, int xOffset, int yOffset);
};

#endif // COLLIDER_H
