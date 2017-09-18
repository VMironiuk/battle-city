#ifndef BCSREADER_H
#define BCSREADER_H

#include <QIODevice>
#include <QXmlStreamReader>

#include "gamecontroller.h"
#include "tile.h"

class BCSReader
{
public:
    BCSReader(GameController *controller);

    bool read(QIODevice *device);
    QString errorString() const;

private:
    bool readBSC();
    bool readStageNo();
    bool readTile();
    int readTileRow(bool *ok);
    int readTileColumn(bool *ok);
    Tile::Material readTileMaterial(bool *ok);
    bool readTank();
    QString readTankType(bool *ok);
    int readTankStrength(bool *ok);
    int readTankValue(bool *ok);

    GameController *controller_;
    QXmlStreamReader xml_;
};

#endif // BCSREADER_H
