#include "collider.h"

#include <QDebug>

Collider &Collider::instance()
{
    static Collider c;
    return c;
}

void Collider::setBoard(Board *board)
{
    board_ = board;
}

bool Collider::isCollided(MovableItem *movableItem)
{
    if (isBoardCollided(movableItem))
        return true;
    if (isTileCollided(movableItem))
        return true;
    return false;
}

Collider::Collider(QObject *parent)
    : QObject(parent)
{

}

Collider::~Collider()
{

}

bool Collider::isBoardCollided(MovableItem *movableItem)
{
    switch (movableItem->direction()) {
    case MovableItem::North:
        if (movableItem->y() <= board_->y())
            return true;
        break;

    case MovableItem::South:
        if (board_->height() <= movableItem->y() + movableItem->height())
            return true;
        break;

    case MovableItem::West:
        if (movableItem->x() <= board_->x())
            return true;
        break;

    case MovableItem::East:
        if (board_->width() <= movableItem->x() + movableItem->width())
            return true;
        break;

    default:
        break;
    }
    return false;
}

bool Collider::isTileCollided(MovableItem *movableItem)
{
    int xOffset = 0;
    int yOffset = 0;

    for (Tile *tile : board_->tiles()) {
        if (!tile->isTankTraversable()) {
            switch (movableItem->direction()) {
            case MovableItem::North:
                xOffset = movableItem->x() % tile->width();
                if (movableItem->top() < tile->bottom() && movableItem->top() > tile->top()
                        && ((movableItem->left() >= tile->left() && movableItem->left() < tile->right())
                            || (movableItem->right() > tile->left() && movableItem->right() <= tile->right()))) {
                    return true;
                }
                break;

            case MovableItem::South:
                xOffset = movableItem->x() % tile->width();
                if (movableItem->bottom() > tile->top() && movableItem->bottom() < tile->bottom()
                        && ((movableItem->left() >= tile->left() && movableItem->left() < tile->right())
                            || (movableItem->right() > tile->left() && movableItem->right() <= tile->right()))) {
                    return true;
                }
                break;

            case MovableItem::West:
                yOffset = movableItem->y() % tile->height();
                if (movableItem->left() < tile->right() && movableItem->left() > tile->left()
                        && ((movableItem->bottom() <= tile->bottom() && movableItem->bottom() > tile->top())
                            || (movableItem->top() < tile->bottom() && movableItem->top() >= tile->top()))) {
                    return true;
                }
                break;

            case MovableItem::East:
                yOffset = movableItem->y() % tile->height();
                if (movableItem->right() > tile->left() && movableItem->right() < tile->right()
                        && ((movableItem->bottom() <= tile->bottom() && movableItem->bottom() > tile->top())
                            || (movableItem->top() < tile->bottom() && movableItem->top() >= tile->top()))) {
                    return true;
                }
                break;

            default:
                break;
            }
        }
    }

    const int tileSize = movableItem->width() / 2;

    if (xOffset < tileSize / 2) {
        xOffset = -xOffset;
    }
    else {
        xOffset = tileSize - xOffset;
    }

    if (yOffset < tileSize / 2) {
        yOffset = -yOffset;
    }
    else {
        yOffset = tileSize - yOffset;
    }

    movableItem->setX(movableItem->x() + xOffset);
    movableItem->setY(movableItem->y() + yOffset);

    return false;
}
