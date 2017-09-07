#include "board.h"

#include <QDebug>

const int Board::SIZE = 26;

Board::Board(QObject *parent) : QObject(parent)
{
    initialize();
}

Board::~Board()
{
    qDeleteAll(tiles_);
}

void Board::setWidth(qreal width)
{
//    qDebug() << Q_FUNC_INFO << width;

    if (width_ != width) {
        width_ = width;
        emit widthChanged(width);
    }
}

void Board::setHeight(qreal height)
{
//    qDebug() << Q_FUNC_INFO << height;

    if (height_ !=  height) {
        height_ = height;
        emit heightChanged(height);
    }
}

Tile *Board::tile(int row, int column) const
{
    int index = column + row * SIZE;
    if (index < 0 || index >= tiles_.size())
        return nullptr;
    return tiles_.at(index);
}

QQmlListProperty<Tile> Board::tiles()
{
    return QQmlListProperty<Tile>(this, tiles_);
}

void Board::updateTiles()
{
    const int tileWidth = width_ / SIZE;
    const int tileHeight = height_ / SIZE;

    for (int row = 0, currentY = 0; row != SIZE; ++row, currentY += tileHeight) {
        for (int column =0, currentX = 0; column != SIZE; ++column, currentX += tileWidth) {
            Tile *currentTile = tile(row, column);
            currentTile->setWidth(tileWidth);
            currentTile->setHeight(tileHeight);
            currentTile->setX(currentX);
            currentTile->setY(currentY);
        }
    }
}

void Board::makeMaze()
{
    Tile *currentTile;

    // Base
    currentTile = tile(25, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(25, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(24, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(24, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 12);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 13);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 1
    currentTile = tile(2, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(2, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(9, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(9, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(10, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(10, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 2
    currentTile = tile(2, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(2, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(9, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(9, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(10, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(10, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 3
    currentTile = tile(2, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(2, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 4
    currentTile = tile(2, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(2, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 5
    currentTile = tile(2, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(2, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(9, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(9, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(10, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(10, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 6
    currentTile = tile(2, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(2, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(3, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(4, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(5, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(6, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(7, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(8, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(9, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(9, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(10, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(10, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 7
    currentTile = tile(11, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(11, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(12, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(12, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 8
    currentTile = tile(11, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(11, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(12, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(12, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 9
    currentTile = tile(13, 4);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(14, 4);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(13, 5);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(14, 5);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(13, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(14, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(13, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(14, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 10
    currentTile = tile(13, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(14, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(13, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(14, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(13, 20);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(14, 20);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(13, 21);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(14, 21);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 11
    currentTile = tile(17, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(21, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(21, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(22, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(22, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 2);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 3);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 11
    currentTile = tile(17, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(21, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(21, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(22, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(22, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 6);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 7);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 12
    currentTile = tile(15, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(15, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(16, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(16, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 10);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 11);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");


    // Wall 13
    currentTile = tile(16, 12);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(16, 13);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 12);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 13);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 14
    currentTile = tile(15, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(15, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(16, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(16, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 14);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 15);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");


    // Wall 15
    currentTile = tile(17, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(21, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(21, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(22, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(22, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 18);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 19);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Wall 16
    currentTile = tile(17, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(17, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(18, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(19, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(20, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(21, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(21, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(22, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(22, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 22);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    currentTile = tile(23, 23);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");

    // Concrete walls
    // Wall 1
    currentTile = tile(6, 12);
    currentTile->setImagePath("qrc:/images/obstacles/concrete.png");

    currentTile = tile(6, 13);
    currentTile->setImagePath("qrc:/images/obstacles/concrete.png");

    currentTile = tile(7, 12);
    currentTile->setImagePath("qrc:/images/obstacles/concrete.png");

    currentTile = tile(7, 13);
    currentTile->setImagePath("qrc:/images/obstacles/concrete.png");

    // Wall 2
    currentTile = tile(14, 0);
    currentTile->setImagePath("qrc:/images/obstacles/concrete.png");

    currentTile = tile(14, 1);
    currentTile->setImagePath("qrc:/images/obstacles/concrete.png");

    // Wall 3
    currentTile = tile(14, 24);
    currentTile->setImagePath("qrc:/images/obstacles/concrete.png");

    currentTile = tile(14, 25);
    currentTile->setImagePath("qrc:/images/obstacles/concrete.png");
}

void Board::initialize()
{
    fillTiles();
    makeMaze();

    connect(this, SIGNAL(widthChanged(int)), this, SLOT(updateTiles()));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(updateTiles()));
}

void Board::fillTiles()
{
    const int tileWidth = width_ / SIZE;
    const int tileHeight = height_ / SIZE;

    for (int row = 0, currentY = 0; row != SIZE; ++row, currentY += tileHeight) {
        for (int column =0, currentX = 0; column != SIZE; ++column, currentX += tileWidth) {
            Tile *tile = new Tile;
            tile->setWidth(tileWidth);
            tile->setHeight(tileHeight);
            tile->setX(currentX);
            tile->setY(currentY);

            tiles_.push_back(tile);
        }
    }
}
