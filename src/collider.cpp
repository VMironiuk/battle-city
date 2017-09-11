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

void Collider::checkBoardBoundariesForTank(Board *board, MovableItem *movableItem)
{
    switch (movableItem->direction()) {
    case MovableItem::North:
        if (movableItem->top() <= board->y())
            movableItem->setY(board->y());
        break;
    case MovableItem::South:
        if (board->height() <= movableItem->bottom())
            movableItem->setY(board->height() - movableItem->height());
        break;
    case MovableItem::West:
        if (movableItem->left() <= board->x())
            movableItem->setX(board->x());
        break;
    case MovableItem::East:
        if (board->width() <= movableItem->right())
            movableItem->setX(board->width() - movableItem->width());
        break;
    default:
        break;
    }
}

void Collider::checkBoardBoundariesForProjectile(Board *board, MovableItem *movableItem)
{
    switch (movableItem->direction()) {
    case MovableItem::North:
        if (movableItem->top() <= board->y())
            board->removeProjectile(movableItem);
        break;
    case MovableItem::South:
        if (board->height() <= movableItem->bottom())
            board->removeProjectile(movableItem);
        break;
    case MovableItem::West:
        if (movableItem->left() <= board->x())
            board->removeProjectile(movableItem);
        break;
    case MovableItem::East:
        if (board->width() <= movableItem->right())
            board->removeProjectile(movableItem);
        break;
    default:
        break;
    }
}

void Collider::checkTileBoundaries(Board *board)
{
    QList<ShootableItem *> tanks = board->playerTanks();
    for (auto tank : tanks)
        checkTileBoundariesForTank(board, tank);

    QList<MovableItem *> projectiles = board->projectiles();
    QList<MovableItem *> projectilesToRemove;
    for (auto projectile : projectiles) {
        if (!checkTileBoundariesForProjectile(board, projectile))
            projectilesToRemove << projectile;
    }

    for (auto projectile : projectilesToRemove)
        board->removeProjectile(projectile);
}

void Collider::checkTileBoundariesForTank(Board *board, MovableItem *movableItem)
{
    QList<Tile *> tiles = board->tiles();
    for (auto tile : tiles) {
        if (!tile->isTankTraversable())
            checkTileBoundariesForTank(movableItem, tile);
    }
}

void Collider::checkTileBoundariesForTank(MovableItem *movableItem, Tile *tile)
{
    int xOffset = 0;
    int yOffset = 0;

    switch (movableItem->direction()) {
    case MovableItem::North:
        xOffset = movableItem->x() % tile->width();
        checkNorthDirection(movableItem, tile);
        break;

    case MovableItem::South:
        xOffset = movableItem->x() % tile->width();
        checkSouthDirection(movableItem, tile);
        break;

    case MovableItem::West:
        yOffset = movableItem->y() % tile->height();
        checkWestDirection(movableItem, tile);
        break;

    case MovableItem::East:
        yOffset = movableItem->y() % tile->height();
        checkEastDirection(movableItem, tile);
        break;

    default:
        break;
    }
    adjustMovableItemPos(movableItem, tile, xOffset, yOffset);
}

bool Collider::checkTileBoundariesForProjectile(Board *board, MovableItem *movableItem)
{
    QList<Tile *> tiles = board->tiles();
    for (auto tile : tiles) {
        if (!tile->isTankTraversable()) {
            if (!checkTileBoundariesForProjectile(movableItem, tile)) {
                if (tile->material() == Tile::Bricks)
                    tile->setMaterial(Tile::Free);
                return false;
            }
        }
    }
    return true;
}

bool Collider::checkTileBoundariesForProjectile(MovableItem *movableItem, Tile *tile)
{
    switch (movableItem->direction()) {
    case MovableItem::North:
        if (!checkNorthDirection(movableItem, tile))
            return false;
        break;

    case MovableItem::South:
        if (!checkSouthDirection(movableItem, tile))
            return false;
        break;

    case MovableItem::West:
        if (!checkWestDirection(movableItem, tile))
            return false;
        break;

    case MovableItem::East:
        if (!checkEastDirection(movableItem, tile))
            return false;
        break;

    default:
        break;
    }
    return true;
}

bool Collider::checkNorthDirection(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->top() < tile->bottom() && movableItem->top() > tile->top()
            && ((movableItem->left() >= tile->left() && movableItem->left() < tile->right())
                || (movableItem->right() > tile->left() && movableItem->right() <= tile->right()))) {
        movableItem->setY(tile->bottom());
        return false;
    }
    return true;
}

bool Collider::checkSouthDirection(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->bottom() > tile->top() && movableItem->bottom() < tile->bottom()
            && ((movableItem->left() >= tile->left() && movableItem->left() < tile->right())
                || (movableItem->right() > tile->left() && movableItem->right() <= tile->right()))) {
        movableItem->setY(tile->top() - movableItem->height());
        return false;
    }
    return true;
}

bool Collider::checkWestDirection(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->left() < tile->right() && movableItem->left() > tile->left()
            && ((movableItem->bottom() <= tile->bottom() && movableItem->bottom() > tile->top())
                || (movableItem->top() < tile->bottom() && movableItem->top() >= tile->top()))) {
        movableItem->setX(tile->right());
        return false;
    }
    return true;
}

bool Collider::checkEastDirection(MovableItem *movableItem, Tile *tile)
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
