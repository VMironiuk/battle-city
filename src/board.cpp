#include "board.h"

#include <QDebug>

const int Board::SIZE = 26;

Board::Board(QObject *parent) : QObject(parent)
{
    initialize();
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

QSharedPointer<Tile> Board::tile(int row, int column) const
{
    int index = column + row * SIZE;
    if (index < 0 || index >= tiles_.size())
        return QSharedPointer<Tile>();
    return tiles_.at(index);
}

void Board::fillTiles()
{
    const int tileWidth = width_ / SIZE;
    const int tileHeight = height_ / SIZE;

    for (int row = 0, currentY = 0; row != SIZE; ++row, currentY += tileHeight) {
        for (int column =0, currentX = 0; column != SIZE; ++column, currentX += tileWidth) {
            QSharedPointer<Tile> tile = QSharedPointer<Tile>(new Tile);
            tile->setWidth(tileWidth);
            tile->setHeight(tileHeight);
            tile->setX(currentX);
            tile->setY(currentY);

            tiles_.push_back(tile);
        }
    }
}

void Board::initialize()
{
    fillTiles();

    connect(this, SIGNAL(widthChanged(int)), this, SLOT(fillTiles()));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(fillTiles()));
}
