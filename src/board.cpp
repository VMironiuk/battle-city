#include "board.h"

#include <QDebug>

static const int TILE_SIZE = 32;
static const int TILE_COUNT_PER_SIDE = 26;
static const int BOARD_SIZE = TILE_SIZE * TILE_COUNT_PER_SIDE;

static const int SIZE = 26;

Board::Board(QObject *parent) : BaseItem(parent)
{
    initialize();
}

Board::~Board()
{
    qDeleteAll(tiles_);
    qDeleteAll(tanks_);
}

QQmlListProperty<Tile> Board::tilesProperty()
{
    return QQmlListProperty<Tile>(this, tiles_);
}

QQmlListProperty<MovableItem> Board::tanksProperty()
{
    return QQmlListProperty<MovableItem>(this, tanks_);
}

void Board::initialize()
{
    setWidth(BOARD_SIZE);
    setHeight(BOARD_SIZE);

    makeTiles();
    makeMaze();
    makeTanks();
}

void Board::makeTiles()
{
    for (int row = 0, currentY = 0; row != TILE_COUNT_PER_SIDE;
         ++row, currentY += TILE_SIZE) {
        for (int column =0, currentX = 0; column != TILE_COUNT_PER_SIDE;
             ++column, currentX += TILE_SIZE) {
            Tile *tile = new Tile;
            tile->setWidth(TILE_SIZE);
            tile->setHeight(TILE_SIZE);
            tile->setX(currentX);
            tile->setY(currentY);

            tiles_.push_back(tile);
        }
    }
}

void Board::makeMaze()
{
    Tile *currentTile;

    // Base
    currentTile = tile(25, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(25, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(24, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(24, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 12);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 13);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 1
    currentTile = tile(2, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(2, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(9, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(9, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(10, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(10, 3);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 2
    currentTile = tile(2, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(2, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(9, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(9, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(10, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(10, 7);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 3
    currentTile = tile(2, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(2, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 11);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 4
    currentTile = tile(2, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(2, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 15);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 5
    currentTile = tile(2, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(2, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(9, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(9, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(10, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(10, 19);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 6
    currentTile = tile(2, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(2, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(3, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(4, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(5, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(6, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(7, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(8, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(9, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(9, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(10, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(10, 23);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 7
    currentTile = tile(11, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(11, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(12, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(12, 11);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 8
    currentTile = tile(11, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(11, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(12, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(12, 15);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 9
    currentTile = tile(13, 4);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(14, 4);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(13, 5);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(14, 5);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(13, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(14, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(13, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(14, 7);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 10
    currentTile = tile(13, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(14, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(13, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(14, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(13, 20);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(14, 20);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(13, 21);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(14, 21);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 11
    currentTile = tile(17, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(21, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(21, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(22, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(22, 3);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 2);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 3);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 11
    currentTile = tile(17, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(21, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(21, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(22, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(22, 7);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 6);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 7);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 12
    currentTile = tile(15, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(15, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(16, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(16, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 11);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 10);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 11);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 13
    currentTile = tile(16, 12);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(16, 13);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 12);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 13);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 14
    currentTile = tile(15, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(15, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(16, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(16, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 15);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 14);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 15);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 15
    currentTile = tile(17, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(21, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(21, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(22, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(22, 19);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 18);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 19);
    currentTile->setMaterial(Tile::Bricks);

    // Wall 16
    currentTile = tile(17, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(17, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(18, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(19, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(20, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(21, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(21, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(22, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(22, 23);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 22);
    currentTile->setMaterial(Tile::Bricks);

    currentTile = tile(23, 23);
    currentTile->setMaterial(Tile::Bricks);

    // Concrete walls
    // Wall 1
    currentTile = tile(6, 12);
    currentTile->setMaterial(Tile::Concrete);

    currentTile = tile(6, 13);
    currentTile->setMaterial(Tile::Concrete);

    currentTile = tile(7, 12);
    currentTile->setMaterial(Tile::Concrete);

    currentTile = tile(7, 13);
    currentTile->setMaterial(Tile::Concrete);

    // Wall 2
    currentTile = tile(14, 0);
    currentTile->setMaterial(Tile::Concrete);

    currentTile = tile(14, 1);
    currentTile->setMaterial(Tile::Concrete);

    // Wall 3
    currentTile = tile(14, 24);
    currentTile->setMaterial(Tile::Concrete);

    currentTile = tile(14, 25);
    currentTile->setMaterial(Tile::Concrete);
}

void Board::makeTanks()
{
    MovableItem *tank = new MovableItem;
    tank->setWidth(TILE_SIZE * 2);
    tank->setHeight(TILE_SIZE * 2);

    Tile *t = tile(24, 9);
    tank->setX(t->x());
    tank->setY(t->y());

    tank->setImageSource("qrc:/images/tanks/player/simple_tank.png");

    tanks_ << tank;
}

Tile *Board::tile(int row, int column) const
{
    int index = column + row * TILE_COUNT_PER_SIDE;
    if (index < 0 || index >= tiles_.size())
        return nullptr;
    return tiles_.at(index);
}
