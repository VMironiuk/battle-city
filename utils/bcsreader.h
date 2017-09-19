#ifndef BCSREADER_H
#define BCSREADER_H

#include <QIODevice>
#include <QXmlStreamReader>

#include "board.h"
#include "informationpanel.h"
#include "tile.h"

namespace Utils {

class BCSReader
{
public:
    BCSReader(Base::Board *board, Base::InformationPanel *informationPanel);

    bool read(QIODevice *device);
    QString errorString() const;

private:
    bool readBSC();
    bool readStageNo();
    bool readTile();
    int readTileRow(bool *ok);
    int readTileColumn(bool *ok);
    Base::Tile::Material readTileMaterial(bool *ok);
    bool readTank();
    QString readTankType(bool *ok);
    int readTankStrength(bool *ok);
    int readTankValue(bool *ok);

    Base::Board *board_;
    Base::InformationPanel *informationPanel_;
    QXmlStreamReader xml_;
};

}  // namespace Utils

#endif // BCSREADER_H
