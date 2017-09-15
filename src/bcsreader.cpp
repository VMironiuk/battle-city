#include "bcsreader.h"

BCSReader::BCSReader(GameController *controller)
    : controller_(controller)
{
}

bool BCSReader::read(QIODevice *device)
{
    xml_.setDevice(device);

    if (xml_.readNextStartElement()) {
        if (xml_.name() == "bcs" && xml_.attributes().value("version") == "1.0")
            readBSC();
        else
            xml_.raiseError("The file is not BCS version 1.0 file");
    }
    return !xml_.error();
}

QString BCSReader::errorString() const
{
    return QString("%1.\nLine %2, column %3")
            .arg(xml_.errorString())
            .arg(xml_.lineNumber())
            .arg(xml_.columnNumber());
}

bool BCSReader::readBSC()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "bcs");

    if (xml_.readNextStartElement() && xml_.name() == "stage"
            && !xml_.attributes().value("id").isEmpty()) {
        readStageNo();
    } else {
        xml_.raiseError("Stage is empty");
        return false;
    }

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "tile")
            readTile();
        else if (xml_.name() == "tank")
            readTank();
        else
            xml_.skipCurrentElement();
    }

    return !xml_.error();
}

void BCSReader::readStageNo()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "stage");

    bool ok;
    int stageNo = xml_.attributes().value("id").toInt(&ok);

    Q_ASSERT(ok);

    controller_->setStageNo(stageNo);
}

void BCSReader::readTile()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "tile");

    int row = 0;
    int column = 0;
    Tile::Material material = Tile::Free;

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "row")
            row = readTileRow();
        else if (xml_.name() == "column")
            column = readTileColumn();
        else if (xml_.name() == "material")
            material = readTileMaterial();
        else
            xml_.skipCurrentElement();
    }

    controller_->setTile(row, column, material);
}

int BCSReader::readTileRow()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "row");

    bool ok;
    int row = xml_.readElementText().toInt(&ok);

    Q_ASSERT(ok);

    return row;
}

int BCSReader::readTileColumn()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "column");

    bool ok;
    int column = xml_.readElementText().toInt(&ok);

    Q_ASSERT(ok);

    return column;
}

Tile::Material BCSReader::readTileMaterial()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "material");

    bool ok;
    Tile::Material material;
    material = static_cast<Tile::Material>(xml_.readElementText().toInt(&ok));

    Q_ASSERT(ok);

    return material;
}

void BCSReader::readTank()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "tank");

    ShootableItem *tank = new ShootableItem;
    tank->setProperty("battleCitySide", "enemy");

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "type") {
            QString type = readTankType();
            if (type == "usual") {
                tank->setImageSource("qrc:/images/tanks/enemy/simple_tank.png");
                tank->setProperty("enemyTankType", "usual");
            } else if (type == "armored_troop_carrier") {
                tank->setImageSource("qrc:/images/tanks/enemy/fast.png");
                tank->setSpeed(6);
                tank->setProperty("enemyTankType", "armored_troop_carrier");
            } else if (type == "bursting") {
                tank->setImageSource("qrc:/images/tanks/enemy/bursting.png");
                tank->setShotMode(ShootableItem::BurstShot);
                tank->setProperty("enemyTankType", "bursting");
            } else if (type == "armored") {
                tank->setImageSource("qrc:/images/tanks/enemy/armored.png");
                tank->setProperty("enemyTankType", "armored");
            }
        } else if (xml_.name() == "strength") {
            tank->setProperty("strength", readTankStrength());
        } else {
            xml_.skipCurrentElement();
        }
    }

    controller_->addEnemyTank(tank);
}

QString BCSReader::readTankType()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "type");

    return xml_.readElementText();
}

int BCSReader::readTankStrength()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "strength");

    bool ok;
    int strength = xml_.readElementText().toInt(&ok);

    Q_ASSERT(ok);

    return strength;
}
