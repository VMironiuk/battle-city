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
    for (Tile *tile : board_->tiles()) {
        if (!tile->isTankTraversable()) {
            switch (movableItem->direction()) {
            case MovableItem::North:
                if (movableItem->top() > tile->top()
                        && movableItem->top() < tile->bottom()
                        && ((movableItem->left() > tile->left()
                             && movableItem->left() < tile->right())
                            || (movableItem->right() > tile->left()
                                && movableItem->right() < tile->right()))) {
                    return true;
                }
                break;

            case MovableItem::South:
                if (movableItem->bottom() < tile->bottom()
                        && movableItem->bottom() > tile->top()
                        && ((movableItem->left() > tile->left()
                             && movableItem->left() < tile->right())
                            || (movableItem->right() > tile->left()
                                && movableItem->right() < tile->right()))) {
                    return true;
                }
                break;

            case MovableItem::West:
                if (movableItem->left() > tile->left()
                        && movableItem->left() < tile->right()
                        && ((movableItem->bottom() < tile->bottom()
                             && movableItem->bottom() > tile->top())
                            || (movableItem->top() < tile->bottom()
                                && movableItem->top() > tile->top()))) {
                    return true;
                }
                break;

            case MovableItem::East:
                if (movableItem->right() < tile->right()
                        && movableItem->right() > tile->left()
                        && ((movableItem->bottom() < tile->bottom()
                             && movableItem->bottom() > tile->top())
                            || (movableItem->top() < tile->bottom()
                                && movableItem->top() > tile->top()))) {
                    return true;
                }
                break;

            default:
                break;
            }
        }
    }
    return false;
}
