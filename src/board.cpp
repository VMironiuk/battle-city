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

void Board::setWidth(int width)
{
//    qDebug() << Q_FUNC_INFO << width;

    if (width_ != width) {
        width_ = width;
        emit widthChanged(width);
    }
}

void Board::setHeight(int height)
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
    Tile *currentTile = tile(0, 0);
    currentTile->setImagePath("qrc:/images/obstacles/bricks.png");
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
