#include "collider.h"

#include "global.h"

Collider::Collider(QObject *parent)
    : QObject(parent)
{
}

void Collider::checkCollisions(Board *board)
{
    checkBoardBoundaries(board);
    checkTileBoundaries(board);
    checkTanksHitting(board);
    checkTanksCollisions(board);
    checkEagleHitting(board);
    checkEagleBoundaries(board);
    checkBonusBoundaries(board);
}

void Collider::checkBoardBoundaries(Board *board)
{
    QList<ShootableItem *> playerTanks = board->playerTanks();
    for (auto tank : playerTanks)
        checkBoardBoundariesForTank(board, tank);

    QList<ShootableItem *> enemyTanks = board->enemyTanks();
    for (auto tank : enemyTanks)
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
    QList<ShootableItem *> playerTanks = board->playerTanks();
    for (auto tank : playerTanks)
        checkTileBoundariesForTank(board, tank);

    QList<ShootableItem *> enemyTanks = board->enemyTanks();
    for (auto tank : enemyTanks)
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
        checkNorthDirectionCollision(tank, tile);
        break;

    case MovableItem::South:
        xOffset = tank->x() % tile->width();
        checkSouthDirectionCollision(tank, tile);
        break;

    case MovableItem::West:
        yOffset = tank->y() % tile->height();
        checkWestDirectionCollision(tank, tile);
        break;

    case MovableItem::East:
        yOffset = tank->y() % tile->height();
        checkEastDirectionCollision(tank, tile);
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
            if (checkCollision(projectile, tile)) {
                if (tile->isProjectileBreakable()
                        || projectile->property(Constants::Projectile::Property::Powerful)
                        .toBool())
                    tile->setMaterial(Tile::Free);
                board->removeProjectile(projectile);
                return;
            }
        }
    }
}

void Collider::checkTanksHitting(Board *board)
{
    QList<MovableItem *> projectiles = board->projectiles();
    for (auto projectile : projectiles) {
        if (projectile->property(Constants::Property::Belligerent).toString()
                == Constants::Belligerent::Player) {
            checkEnemyTanksHitting(board, projectile);
        } else if (projectile->property(Constants::Property::Belligerent).toString()
                   == Constants::Belligerent::Enemy) {
            checkPlayerTanksHitting(board, projectile);
        }
    }
}

void Collider::checkEnemyTanksHitting(Board *board, MovableItem *projectile)
{
    QList<ShootableItem *> tanks = board->enemyTanks();
    for (auto tank : tanks) {
        if (checkCollision(projectile, tank)) {
            if (tank->property(Constants::EnemyTank::Property::Type).toString()
                    == Constants::EnemyTank::Type::Armored) {
                const int strength = tank->property(Constants::EnemyTank::Property::Strength)
                        .toInt();
                switch (strength) {
                case 3:
                    tank->setProperty(Constants::EnemyTank::Property::Strength, strength - 1);
                    tank->setImageSource("qrc:/images/tanks/enemy/armored_1_hit.png");
                    board->removeProjectile(projectile);
                    return;
                case 2:
                    tank->setProperty(Constants::EnemyTank::Property::Strength, strength - 1);
                    tank->setImageSource("qrc:/images/tanks/enemy/armored_2_hit.png");
                    board->removeProjectile(projectile);
                    return;
                case 1:
                    tank->setProperty(Constants::EnemyTank::Property::Strength, strength - 1);
                    tank->setImageSource("qrc:/images/tanks/enemy/armored_3_hit.png");
                    board->removeProjectile(projectile);
                    return;
                case 0:
                default: break;
                }
            }
            board->removeEnemyTank(tank);
            board->removeProjectile(projectile);
            return;
        }
    }
}

void Collider::checkPlayerTanksHitting(Board *board, MovableItem *projectile)
{
    QList<ShootableItem *> tanks = board->playerTanks();
    for (auto tank : tanks) {
        if (checkCollision(projectile, tank)) {
            board->removePlayerTank(tank);
            board->removeProjectile(projectile);
            return;
        }
    }
}

void Collider::checkTanksCollisions(Board *board)
{
    QList<ShootableItem *> allTanks = board->playerTanks();
    allTanks += board->enemyTanks();
    for (int i = 0; i != allTanks.size(); ++i) {
        for (int j = 0; j != allTanks.size(); ++j) {
            if (i != j) {
                if (checkCollision(allTanks.at(i), allTanks.at(j))) {
                    // TODO: just for testing, delete later
                    if (allTanks.at(i)->property(Constants::Property::Belligerent)
                            == Constants::Belligerent::Enemy
                            && allTanks.at(j)->property(Constants::Property::Belligerent)
                            == Constants::Belligerent::Enemy) {
                        if (allTanks.at(i)->direction() == MovableItem::North
                                && allTanks.at(j)->direction() == MovableItem::South) {
                            allTanks.at(i)->setDirection(MovableItem::South);
                        } else if (allTanks.at(i)->direction() == MovableItem::South
                                   && allTanks.at(j)->direction() == MovableItem::North) {
                            allTanks.at(i)->setDirection(MovableItem::North);
                        } else if (allTanks.at(i)->direction() == MovableItem::West
                                   && allTanks.at(j)->direction() == MovableItem::East) {
                            allTanks.at(i)->setDirection(MovableItem::East);
                        } else if (allTanks.at(i)->direction() == MovableItem::East
                                   && allTanks.at(j)->direction() == MovableItem::West) {
                            allTanks.at(i)->setDirection(MovableItem::West);
                        }
                    }
                    break;
                }
            }
        }
    }
}

void Collider::checkEagleHitting(Board *board)
{
    BaseItem *eagle = board->eagle();
    QList<MovableItem *> projectiles = board->projectiles();
    for (auto projectile : projectiles) {
        if (checkCollision(projectile, eagle)) {
            board->removeProjectile(projectile);
            board->destroyEagle(eagle);
            return;
        }
    }
}

void Collider::checkEagleBoundaries(Board *board)
{
    BaseItem *eagle = board->eagle();
    QList<ShootableItem *> allTanks = board->playerTanks();
    allTanks += board->enemyTanks();
    for (auto tank : allTanks)
        checkCollision(tank, eagle);
}

void Collider::checkBonusBoundaries(Board *board)
{
    QList<ShootableItem *> tanks = board->playerTanks();
    for (auto tank : tanks) {
        QList<BaseItem *> bonuses = board->bonuses();
        for (auto bonus : bonuses) {
            if (checkCollision(tank, bonus))
                board->onBonusReached(tank, bonus);
        }
    }
}

bool Collider::checkNorthDirectionCollision(BaseItem *source, BaseItem *target)
{
    if (source->top() < target->bottom() && source->top() > target->top()
            && ((source->left() >= target->left() && source->left() < target->right())
                || (source->right() > target->left() && source->right() <= target->right()))) {
        source->setY(target->bottom());
        return true;
    }
    return false;
}

bool Collider::checkSouthDirectionCollision(BaseItem *source, BaseItem *target)
{
    if (source->bottom() > target->top() && source->bottom() < target->bottom()
            && ((source->left() >= target->left() && source->left() < target->right())
                || (source->right() > target->left() && source->right() <= target->right()))) {
        source->setY(target->top() - source->height());
        return true;
    }
    return false;
}

bool Collider::checkWestDirectionCollision(BaseItem *source, BaseItem *target)
{
    if (source->left() < target->right() && source->left() > target->left()
            && ((source->bottom() <= target->bottom() && source->bottom() > target->top())
                || (source->top() < target->bottom() && source->top() >= target->top()))) {
        source->setX(target->right());
        return true;
    }
    return false;
}

bool Collider::checkEastDirectionCollision(BaseItem *source, BaseItem *target)
{
    if (source->right() > target->left() && source->right() < target->right()
            && ((source->bottom() <= target->bottom() && source->bottom() > target->top())
                || (source->top() < target->bottom() && source->top() >= target->top()))) {
        source->setX(target->left() - source->width());
        return true;
    }
    return false;
}

bool Collider::checkCollision(MovableItem *movable, BaseItem *target)
{
    switch (movable->direction()) {
    case MovableItem::North:
        if (checkNorthDirectionCollision(movable, target))
            return true;
        break;
    case MovableItem::South:
        if (checkSouthDirectionCollision(movable, target))
            return true;
        break;
    case MovableItem::West:
        if (checkWestDirectionCollision(movable, target))
            return true;
        break;
    case MovableItem::East:
        if (checkEastDirectionCollision(movable, target))
            return true;
        break;
    default:
        break;
    }
    return false;
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
