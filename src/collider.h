#ifndef COLLIDER_H
#define COLLIDER_H

#include <QObject>

#include "baseitem.h"
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

    void checkTanksHitting(Board *board);
    void checkEnemyTanksHitting(Board *board, MovableItem *projectile);
    void checkPlayerTanksHitting(Board *board, MovableItem *projectile);

    void checkTanksCollisions(Board *board);

    void checkEagleHitting(Board *board);
    void checkEagleBoundaries(Board *board);

    void checkBonusBoundaries(Board *board);

    bool checkNorthDirectionCollision(BaseItem *source, BaseItem *target);
    bool checkSouthDirectionCollision(BaseItem *source, BaseItem *target);
    bool checkWestDirectionCollision(BaseItem *source, BaseItem *target);
    bool checkEastDirectionCollision(BaseItem *source, BaseItem *target);

    bool checkCollision(MovableItem *movable, BaseItem *target);

    void adjustMovableItemPos(MovableItem *movableItem, Tile *tile, int xOffset, int yOffset);
};

#endif // COLLIDER_H
