#ifndef TILE_H
#define TILE_H

#include "baseitem.h"

class Tile : public BaseItem
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = nullptr);
};

#endif // TILE_H
