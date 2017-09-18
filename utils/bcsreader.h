#ifndef BCSREADER_H
#define BCSREADER_H

#include <QIODevice>
#include <QXmlStreamReader>

#include "board.h"
#include "informationpanel.h"
#include "tile.h"

class BCSReader
{
public:
    BCSReader(Board *board, InformationPanel *informationPanel);

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

    Board *board_;
    InformationPanel *informationPanel_;
    QXmlStreamReader xml_;
};

#endif // BCSREADER_H
