#ifndef COLLIDER_H
#define COLLIDER_H

#include <QObject>

#include "baseitem.h"
#include "board.h"
#include "movableitem.h"
#include "tile.h"

namespace Utils {

class Collider : public QObject
{
    Q_OBJECT
public:
    explicit Collider(QObject *parent = nullptr);
    Collider(const Collider&) = delete;
    Collider &operator=(const Collider&) = delete;

    void checkCollisions(Base::Board *board);

    void checkBoardBoundaries(Base::Board *board);
    void checkBoardBoundariesForTank(Base::Board *board, Base::MovableItem *tank);
    void checkBoardBoundariesForProjectile(Base::Board *board, Base::MovableItem *projectile);

    void checkTileBoundaries(Base::Board *board);
    void checkTileBoundariesForTank(Base::Board *board, Base::MovableItem *tank);
    void checkTileBoundariesForTank(Base::MovableItem *tank, Base::Tile *tile);
    void checkTileBoundariesForProjectile(Base::Board *board, Base::MovableItem *projectile);

    void checkTanksHitting(Base::Board *board);
    void checkEnemyTanksHitting(Base::Board *board, Base::MovableItem *projectile);
    void checkPlayerTanksHitting(Base::Board *board, Base::MovableItem *projectile);

    void checkTanksCollisions(Base::Board *board);
    void checkProjectiesCollisions(Base::Board *board);

    void checkEagleHitting(Base::Board *board);
    void checkEagleBoundaries(Base::Board *board);

    void checkBonusBoundaries(Base::Board *board);

    bool checkNorthDirectionCollision(Base::BaseItem *source, Base::BaseItem *target);
    bool checkSouthDirectionCollision(Base::BaseItem *source, Base::BaseItem *target);
    bool checkWestDirectionCollision(Base::BaseItem *source, Base::BaseItem *target);
    bool checkEastDirectionCollision(Base::BaseItem *source, Base::BaseItem *target);

    bool checkCollision(Base::MovableItem *movable, Base::BaseItem *target);

    void adjustMovableItemPos(Base::MovableItem *movableItem, Base::Tile *tile, int xOffset,
                              int yOffset);
};

}  // namespace Utils

#endif // COLLIDER_H
