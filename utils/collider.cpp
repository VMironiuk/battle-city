#include "collider.h"

#include "global.h"

namespace Utils {

Collider::Collider(QObject *parent)
    : QObject(parent)
{
}

void Collider::checkCollisions(Base::Board *board)
{
    if (board == nullptr)
        return;

    checkBoardBoundaries(board);
    checkTileBoundaries(board);
    checkTanksHitting(board);
    checkTanksCollisions(board);
    checkEagleHitting(board);
    checkEagleBoundaries(board);
    checkBonusBoundaries(board);
    checkProjectiesCollisions(board);
}

void Collider::checkBoardBoundaries(Base::Board *board)
{
    if (board == nullptr)
        return;

    QList<Base::ShootableItem *> playerTanks = board->playerTanks();
    for (auto tank : playerTanks) {
        if (tank != nullptr)
            checkBoardBoundariesForTank(board, tank);
    }

    QList<Base::ShootableItem *> enemyTanks = board->enemyTanks();
    for (auto tank : enemyTanks) {
        if (tank != nullptr)
            checkBoardBoundariesForTank(board, tank);
    }

    QList<Base::MovableItem *> projectiles = board->projectiles();
    for (auto projectile : projectiles) {
        if (projectile != nullptr)
            checkBoardBoundariesForProjectile(board, projectile);
    }
}

void Collider::checkBoardBoundariesForTank(Base::Board *board, Base::MovableItem *tank)
{
    if (board == nullptr || tank == nullptr)
        return;

    switch (tank->direction()) {
    case Base::MovableItem::North:
        if (tank->top() <= board->y())
            tank->setY(board->y());
        break;
    case Base::MovableItem::South:
        if (board->height() <= tank->bottom())
            tank->setY(board->height() - tank->height());
        break;
    case Base::MovableItem::West:
        if (tank->left() <= board->x())
            tank->setX(board->x());
        break;
    case Base::MovableItem::East:
        if (board->width() <= tank->right())
            tank->setX(board->width() - tank->width());
        break;
    default:
        break;
    }
}

void Collider::checkBoardBoundariesForProjectile(Base::Board *board, Base::MovableItem *projectile)
{
    if (board == nullptr || projectile == nullptr)
        return;

    if (projectile->top() <= board->y()
            || board->height() <= projectile->bottom()
            || projectile->left() <= board->x()
            || board->width() <= projectile->right()) {
        board->removeProjectile(projectile);
    }
}

void Collider::checkTileBoundaries(Base::Board *board)
{
    if (board == nullptr)
        return;

    QList<Base::ShootableItem *> playerTanks = board->playerTanks();
    for (auto tank : playerTanks) {
        if (tank != nullptr)
            checkTileBoundariesForTank(board, tank);
    }

    QList<Base::ShootableItem *> enemyTanks = board->enemyTanks();
    for (auto tank : enemyTanks) {
        if (tank != nullptr)
            checkTileBoundariesForTank(board, tank);
    }

    QList<Base::MovableItem *> projectiles = board->projectiles();
    for (auto projectile : projectiles) {
        if (projectile != nullptr)
            checkTileBoundariesForProjectile(board, projectile);
    }
}

void Collider::checkTileBoundariesForTank(Base::Board *board, Base::MovableItem *tank)
{
    if (board == nullptr || tank == nullptr)
        return;

    QList<Base::Tile *> tiles = board->tiles();
    for (auto tile : tiles) {
        if (tile != nullptr) {
            if (!tile->isTankTraversable())
                checkTileBoundariesForTank(tank, tile);
        }
    }
}

void Collider::checkTileBoundariesForTank(Base::MovableItem *tank, Base::Tile *tile)
{
    if (tank == nullptr || tile == nullptr)
        return;

    int xOffset = 0;
    int yOffset = 0;

    switch (tank->direction()) {
    case Base::MovableItem::North:
        xOffset = tank->x() % tile->width();
        checkNorthDirectionCollision(tank, tile);
        break;

    case Base::MovableItem::South:
        xOffset = tank->x() % tile->width();
        checkSouthDirectionCollision(tank, tile);
        break;

    case Base::MovableItem::West:
        yOffset = tank->y() % tile->height();
        checkWestDirectionCollision(tank, tile);
        break;

    case Base::MovableItem::East:
        yOffset = tank->y() % tile->height();
        checkEastDirectionCollision(tank, tile);
        break;

    default:
        break;
    }
    adjustMovableItemPos(tank, tile, xOffset, yOffset);
}

void Collider::checkTileBoundariesForProjectile(Base::Board *board, Base::MovableItem *projectile)
{
    if (board == nullptr || projectile == nullptr)
        return;

    QList<Base::Tile *> tiles = board->tiles();
    for (auto tile : tiles) {
        if (tile == nullptr)
            continue;

        if (!tile->isProjectileTraversable()) {
            if (checkCollision(projectile, tile)) {
                if (tile->isProjectileBreakable()
                        || projectile->property(Base::Constants::Projectile::Property::Powerful)
                        .toBool())
                    tile->setMaterial(Base::Tile::Free);
                board->removeProjectile(projectile);
                return;
            }
        }
    }
}

void Collider::checkTanksHitting(Base::Board *board)
{
    if (board == nullptr)
        return;

    QList<Base::MovableItem *> projectiles = board->projectiles();
    for (auto projectile : projectiles) {
        if (projectile == nullptr)
            continue;

        if (projectile->property(Base::Constants::Property::Belligerent).toString()
                == Base::Constants::Belligerent::Player) {
            checkEnemyTanksHitting(board, projectile);
        } else if (projectile->property(Base::Constants::Property::Belligerent).toString()
                   == Base::Constants::Belligerent::Enemy) {
            checkPlayerTanksHitting(board, projectile);
        }
    }
}

void Collider::checkEnemyTanksHitting(Base::Board *board, Base::MovableItem *projectile)
{
    if (board == nullptr || projectile == nullptr)
        return;

    QList<Base::ShootableItem *> tanks = board->enemyTanks();
    for (auto tank : tanks) {
        if (tank == nullptr)
            continue;

        if (checkCollision(projectile, tank)) {
            if (tank->property(Base::Constants::EnemyTank::Property::Type).toString()
                    == Base::Constants::EnemyTank::Type::Armored) {
                const int strength = tank->property(Base::Constants::EnemyTank::Property::Strength)
                        .toInt();
                switch (strength) {
                case 3:
                    tank->setProperty(Base::Constants::EnemyTank::Property::Strength, strength - 1);
                    tank->setImageSource("qrc:/images/tanks/enemy/armored_1_hit.png");
                    board->removeProjectile(projectile);
                    return;
                case 2:
                    tank->setProperty(Base::Constants::EnemyTank::Property::Strength, strength - 1);
                    tank->setImageSource("qrc:/images/tanks/enemy/armored_2_hit.png");
                    board->removeProjectile(projectile);
                    return;
                case 1:
                    tank->setProperty(Base::Constants::EnemyTank::Property::Strength, strength - 1);
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

void Collider::checkPlayerTanksHitting(Base::Board *board, Base::MovableItem *projectile)
{
    if (board == nullptr || projectile == nullptr)
        return;

    QList<Base::ShootableItem *> tanks = board->playerTanks();
    for (auto tank : tanks) {
        if (tank == nullptr)
            continue;

        if (checkCollision(projectile, tank)) {
            board->removePlayerTank(tank);
            board->removeProjectile(projectile);
            return;
        }
    }
}

void Collider::checkTanksCollisions(Base::Board *board)
{
    if (board == nullptr)
        return;

    QList<Base::ShootableItem *> allTanks = board->playerTanks();
    allTanks += board->enemyTanks();
    for (int i = 0; i != allTanks.size(); ++i) {
        for (int j = 0; j != allTanks.size(); ++j) {
            if (i != j) {
                if (checkCollision(allTanks.at(i), allTanks.at(j))) {
                    // TODO: just for testing, delete later
                    if (allTanks.at(i)->property(Base::Constants::Property::Belligerent)
                            == Base::Constants::Belligerent::Enemy
                            && allTanks.at(j)->property(Base::Constants::Property::Belligerent)
                            == Base::Constants::Belligerent::Enemy) {
                        if (allTanks.at(i)->direction() == Base::MovableItem::North
                                && allTanks.at(j)->direction() == Base::MovableItem::South) {
                            allTanks.at(i)->setDirection(Base::MovableItem::South);
                        } else if (allTanks.at(i)->direction() == Base::MovableItem::South
                                   && allTanks.at(j)->direction() == Base::MovableItem::North) {
                            allTanks.at(i)->setDirection(Base::MovableItem::North);
                        } else if (allTanks.at(i)->direction() == Base::MovableItem::West
                                   && allTanks.at(j)->direction() == Base::MovableItem::East) {
                            allTanks.at(i)->setDirection(Base::MovableItem::East);
                        } else if (allTanks.at(i)->direction() == Base::MovableItem::East
                                   && allTanks.at(j)->direction() == Base::MovableItem::West) {
                            allTanks.at(i)->setDirection(Base::MovableItem::West);
                        }
                    }
                    break;
                }
            }
        }
    }
}

void Collider::checkProjectiesCollisions(Base::Board *board)
{
    if (board == nullptr)
        return;

    QList<Base::MovableItem *> projectiles = board->projectiles();
    for (int i = 0; i != projectiles.size(); ++i) {
        auto p1 = projectiles.at(i);
        if (p1 == nullptr)
            continue;

        for (int j = i + 1; j != projectiles.size(); ++j) {
            auto p2 = projectiles.at(j);
            if (p2 == nullptr)
                continue;

            if (checkCollision(p1, p2)) {
                board->removeProjectileQuietly(p1);
                board->removeProjectileQuietly(p2);
                p1 = nullptr;
                p2 = nullptr;
                break;
            }
        }
    }
}

void Collider::checkEagleHitting(Base::Board *board)
{
    if (board == nullptr)
        return;

    Base::BaseItem *eagle = board->eagle();
    if (eagle == nullptr)
        return;

    QList<Base::MovableItem *> projectiles = board->projectiles();
    for (auto projectile : projectiles) {
        if (projectile == nullptr)
            continue;

        if (checkCollision(projectile, eagle)) {
            board->removeProjectile(projectile);
            board->destroyEagle(eagle);
            return;
        }
    }
}

void Collider::checkEagleBoundaries(Base::Board *board)
{
    if (board == nullptr)
        return;

    Base::BaseItem *eagle = board->eagle();
    if (eagle == nullptr)
        return;

    QList<Base::ShootableItem *> allTanks = board->playerTanks();
    allTanks += board->enemyTanks();
    for (auto tank : allTanks) {
        if (tank != nullptr)
            checkCollision(tank, eagle);
    }
}

void Collider::checkBonusBoundaries(Base::Board *board)
{
    if (board == nullptr)
        return;

    QList<Base::ShootableItem *> tanks = board->playerTanks();
    for (auto tank : tanks) {
        if (tank == nullptr)
            continue;

        QList<Base::BaseItem *> bonuses = board->bonuses();
        for (auto bonus : bonuses) {
            if (bonus != nullptr) {
                if (checkCollision(tank, bonus))
                    board->onBonusReached(tank, bonus);
            }
        }
    }
}

bool Collider::checkNorthDirectionCollision(Base::BaseItem *source, Base::BaseItem *target)
{
    if (source == nullptr || target == nullptr)
        return false;

    if (source->top() < target->bottom() && source->top() > target->top()
            && ((source->left() >= target->left() && source->left() < target->right())
                || (source->right() > target->left() && source->right() <= target->right()))) {
        source->setY(target->bottom());
        return true;
    }
    return false;
}

bool Collider::checkSouthDirectionCollision(Base::BaseItem *source, Base::BaseItem *target)
{
    if (source == nullptr || target == nullptr)
        return false;

    if (source->bottom() > target->top() && source->bottom() < target->bottom()
            && ((source->left() >= target->left() && source->left() < target->right())
                || (source->right() > target->left() && source->right() <= target->right()))) {
        source->setY(target->top() - source->height());
        return true;
    }
    return false;
}

bool Collider::checkWestDirectionCollision(Base::BaseItem *source, Base::BaseItem *target)
{
    if (source == nullptr || target == nullptr)
        return false;

    if (source->left() < target->right() && source->left() > target->left()
            && ((source->bottom() <= target->bottom() && source->bottom() > target->top())
                || (source->top() < target->bottom() && source->top() >= target->top()))) {
        source->setX(target->right());
        return true;
    }
    return false;
}

bool Collider::checkEastDirectionCollision(Base::BaseItem *source, Base::BaseItem *target)
{
    if (source == nullptr || target == nullptr)
        return false;

    if (source->right() > target->left() && source->right() < target->right()
            && ((source->bottom() <= target->bottom() && source->bottom() > target->top())
                || (source->top() < target->bottom() && source->top() >= target->top()))) {
        source->setX(target->left() - source->width());
        return true;
    }
    return false;
}

bool Collider::checkCollision(Base::MovableItem *movable, Base::BaseItem *target)
{
    if (movable == nullptr || target == nullptr)
        return false;

    switch (movable->direction()) {
    case Base::MovableItem::North:
        if (checkNorthDirectionCollision(movable, target))
            return true;
        break;
    case Base::MovableItem::South:
        if (checkSouthDirectionCollision(movable, target))
            return true;
        break;
    case Base::MovableItem::West:
        if (checkWestDirectionCollision(movable, target))
            return true;
        break;
    case Base::MovableItem::East:
        if (checkEastDirectionCollision(movable, target))
            return true;
        break;
    default:
        break;
    }
    return false;
}

void Collider::adjustMovableItemPos(Base::MovableItem *movableItem, Base::Tile *tile, int xOffset,
                                    int yOffset)
{
    if (movableItem == nullptr || tile == nullptr)
        return;

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

}  // namespace Utils
