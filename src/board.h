#ifndef BOARD_H
#define BOARD_H

#include <QQmlListProperty>

#include "baseitem.h"
#include "tile.h"

class Board : public BaseItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Tile> tiles READ tiles CONSTANT)
public:
    explicit Board(QObject *parent = nullptr);
    ~Board();

    QQmlListProperty<Tile> tiles();

private slots:
    void updateTiles();

private:
    void initialize();
    void fillTiles();
    void makeMaze();
    Tile *tile(int row, int column) const;

    QList<Tile *> tiles_;
};

#endif // BOARD_H
