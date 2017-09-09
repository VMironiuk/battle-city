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
    QList<MovableItem *> tanks = board->tanks();
    for (auto tank : tanks)
        checkBoardBoundaries(board, tank);
}

void Collider::checkBoardBoundaries(Board *board, MovableItem *movableItem)
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

void Collider::checkTileBoundaries(Board *board)
{
    QList<MovableItem *> tanks = board->tanks();
    for (auto tank : tanks)
        checkTileBoundaries(board, tank);
}

void Collider::checkTileBoundaries(Board *board, MovableItem *movableItem)
{
    QList<Tile *> tiles = board->tiles();
    for (auto tile : tiles) {
        if (!tile->isTankTraversable())
            checkTileBoundaries(movableItem, tile);
    }
}

void Collider::checkTileBoundaries(MovableItem *movableItem, Tile *tile)
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

void Collider::checkNorthDirection(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->top() < tile->bottom() && movableItem->top() > tile->top()
            && ((movableItem->left() >= tile->left() && movableItem->left() < tile->right())
                || (movableItem->right() > tile->left() && movableItem->right() <= tile->right()))) {
        movableItem->setY(tile->bottom());
    }
}

void Collider::checkSouthDirection(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->bottom() > tile->top() && movableItem->bottom() < tile->bottom()
            && ((movableItem->left() >= tile->left() && movableItem->left() < tile->right())
                || (movableItem->right() > tile->left() && movableItem->right() <= tile->right()))) {
        movableItem->setY(tile->top() - movableItem->height());
    }
}

void Collider::checkWestDirection(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->left() < tile->right() && movableItem->left() > tile->left()
            && ((movableItem->bottom() <= tile->bottom() && movableItem->bottom() > tile->top())
                || (movableItem->top() < tile->bottom() && movableItem->top() >= tile->top()))) {
        movableItem->setX(tile->right());
    }
}

void Collider::checkEastDirection(MovableItem *movableItem, Tile *tile)
{
    if (movableItem->right() > tile->left() && movableItem->right() < tile->right()
            && ((movableItem->bottom() <= tile->bottom() && movableItem->bottom() > tile->top())
                || (movableItem->top() < tile->bottom() && movableItem->top() >= tile->top()))) {
        movableItem->setX(tile->left() - movableItem->width());
    }
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
