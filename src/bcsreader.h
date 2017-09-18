#ifndef BCSREADER_H
#define BCSREADER_H

#include <QIODevice>
#include <QXmlStreamReader>

#include "bcobject.h"
#include "gamecontroller.h"
#include "tile.h"

class BCSReader : public BCObject
{
public:
    BCSReader(GameController *controller, QObject *parent = nullptr);

    bool read(QIODevice *device);
//    QString errorString() const;

private:
    bool readBSC();
    void readStageNo();
    void readTile();
    int readTileRow();
    int readTileColumn();
    Tile::Material readTileMaterial();
    void readTank();
    QString readTankType();
    int readTankStrength();
    int readTankValue();

    GameController *controller_;
    QXmlStreamReader xml_;
};

#endif // BCSREADER_H
