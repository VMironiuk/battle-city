#include "collider.h"

Collider::Collider(QObject *parent)
    : QObject(parent)
{
}

void Collider::checkCollisions(Board *board)
{
    checkBoardBoundaries(board);
    checkTileBoundaries(board);
}

void Collider::checkBoardBoundaries(Board *board)
{
    QList<ShootableItem *> tanks = board->playerTanks();
    for (auto tank : tanks)
        checkBoardBoundariesForTank(board, tank);

    QList<MovableItem *> projectiles = board->projectiles();
    for (auto projectile : projectiles)
        checkBoardBoundariesForProjectile(board, projectile);
}

void Collider::checkBoardBoundariesForTank(Board *board, MovableItem *tank)
{
    switch (tank->direction()) {
    case MovableItem::North:
        if (tank->top() <= board->y())
            tank->setY(board->y());
        break;
    case MovableItem::South:
        if (board->height() <= tank->bottom())
            tank->setY(board->height() - tank->height());
        break;
    case MovableItem::West:
        if (tank->left() <= board->x())
            tank->setX(board->x());
        break;
    case MovableItem::East:
        if (board->width() <= tank->right())
            tank->setX(board->width() - tank->width());
        break;
    default:
        break;
    }
}

void Collider::checkBoardBoundariesForProjectile(Board *board, MovableItem *projectile)
{
    if (projectile->top() <= board->y()
            || board->height() <= projectile->bottom()
            || projectile->left() <= board->x()
            || board->width() <= projectile->right()) {
        board->removeProjectile(projectile);
    }
}

void Collider::checkTileBoundaries(Board *board)
{
    QList<ShootableItem *> tanks = board->playerTanks();
    for (auto tank : tanks)
        checkTileBoundariesForTank(board, tank);

    QList<MovableItem *> projectiles = board->projectiles();
    for (auto projectile : projectiles)
        checkTileBoundariesForProjectile(board, projectile);
}

void Collider::checkTileBoundariesForTank(Board *board, MovableItem *tank)
{
    QList<Tile *> tiles = board->tiles();
    for (auto tile : tiles) {
        if (!tile->isTankTraversable())
            checkTileBoundariesForTank(tank, tile);
    }
}

void Collider::checkTileBoundariesForTank(MovableItem *tank, Tile *tile)
{
    int xOffset = 0;
    int yOffset = 0;

    switch (tank->direction()) {
    case MovableItem::North:
        xOffset = tank->x() % tile->width();
        checkNorthDirectionAboutTile(tank, tile);
        break;

    case MovableItem::South:
        xOffset = tank->x() % tile->width();
        checkSouthDirectionAboutTile(tank, tile);
        break;

    case MovableItem::West:
        yOffset = tank->y() % tile->height();
        checkWestDirectionAboutTile(tank, tile);
        break;

    case MovableItem::East:
        yOffset = tank->y() % tile->height();
        checkEastDirectionAboutTile(tank, tile);
        break;

    default:
        break;
    }
    adjustMovableItemPos(tank, tile, xOffset, yOffset);
}

void Collider::checkTileBoundariesForProjectile(Board *board, MovableItem *projectile)
{
    QList<Tile *> tiles = board->tiles();
    for (auto tile : tiles) {
        if (!tile->isProjectileTraversable()) {
            if (!checkTileBoundariesForProjectile(projectile, tile)) {
                board->removeProjectile(projectile);
                if (tile->isProjectileBreakable())
                    tile->setMaterial(Tile::Free);
                return;
            }
        }
    }
}

bool Collider::checkTileBoundariesForProjectile(MovableItem *projectile, Tile *tile)
{
    switch (projectile->direction()) {
    case MovableItem::North:
        if (!checkNorthDirectionAboutTile(projectile, tile))
            return false;
        break;
    case MovableItem::South:
        if (!checkSouthDirectionAboutTile(projectile, tile))
            return false;
        break;
    case MovableItem::West:
        if (!checkWestDirectionAboutTile(projectile, tile))
            return false;
        break;
    case MovableItem::East:
        if (!checkEastDirectionAboutTile(projectile, tile))
            return false;
        break;
    default:
        break;
    }
    return true;
}

bool Collider::checkNorthDirectionAboutTile(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->top() < tile->bottom() && movableItem->top() > tile->top()
            && ((movableItem->left() >= tile->left() && movableItem->left() < tile->right())
                || (movableItem->right() > tile->left() && movableItem->right() <= tile->right()))) {
        movableItem->setY(tile->bottom());
        return false;
    }
    return true;
}

bool Collider::checkSouthDirectionAboutTile(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->bottom() > tile->top() && movableItem->bottom() < tile->bottom()
            && ((movableItem->left() >= tile->left() && movableItem->left() < tile->right())
                || (movableItem->right() > tile->left() && movableItem->right() <= tile->right()))) {
        movableItem->setY(tile->top() - movableItem->height());
        return false;
    }
    return true;
}

bool Collider::checkWestDirectionAboutTile(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->left() < tile->right() && movableItem->left() > tile->left()
            && ((movableItem->bottom() <= tile->bottom() && movableItem->bottom() > tile->top())
                || (movableItem->top() < tile->bottom() && movableItem->top() >= tile->top()))) {
        movableItem->setX(tile->right());
        return false;
    }
    return true;
}

bool Collider::checkEastDirectionAboutTile(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->right() > tile->left() && movableItem->right() < tile->right()
            && ((movableItem->bottom() <= tile->bottom() && movableItem->bottom() > tile->top())
                || (movableItem->top() < tile->bottom() && movableItem->top() >= tile->top()))) {
        movableItem->setX(tile->left() - movableItem->width());
        return false;
    }
    return true;
}

void Collider::adjustMovableItemPos(MovableItem *movableItem, Tile *tile, int xOffset, int yOffset)
{
    if (xOffset < tile->width() / 2)
        xOffset = -xOffset;
    else
        xOffset = tile->width() - xOffset;

    if (yOffset < tile->height() / 2)
        yOffset = -yOffset;
    else
        yOffset = tile->height() - yOffset;

    movableItem->setX(movableItem->x() + xOffset);
    movableItem->setY(movableItem->y() + yOffset);
}
