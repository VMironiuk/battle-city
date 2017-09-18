#include "bcsreader.h"

#include "global.h"

BCSReader::BCSReader(GameController *controller)
    : controller_(controller)
{
}

bool BCSReader::read(QIODevice *device)
{
    xml_.setDevice(device);

    if (xml_.readNextStartElement()) {
        if (xml_.name() == "bcs" && xml_.attributes().value("version") == "1.0")
            return readBSC();
        else
            xml_.raiseError("BCSReader: the file is not BCS version 1.0 file");
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
    if (!readStageNo())
        return false;

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "tile") {
            if (!readTile())
                return false;
        } else if (xml_.name() == "tank") {
            if (!readTank())
                return false;
        } else {
            xml_.skipCurrentElement();
        }
    }

    return !xml_.error();
}

bool BCSReader::readStageNo()
{
    static const QString errStr = "BCSReader: stage number is invalid";

    if (!xml_.readNextStartElement()
            || xml_.name() != "stage"
            || xml_.attributes().value("id").isEmpty()) {
        xml_.raiseError(errStr);
        return false;
    }

    bool ok;
    int stageNo = xml_.attributes().value("id").toInt(&ok);

    if (!ok) {
        xml_.raiseError(errStr);
        return false;
    }

    controller_->setStageNo(stageNo);
    return true;
}

bool BCSReader::readTile()
{
    int row = 0;
    int column = 0;
    Tile::Material material = Tile::Free;

    bool ok = true;
    while (xml_.readNextStartElement()) {
        if (xml_.name() == "row") {
            row = readTileRow(&ok);
            if (!ok) {
                xml_.raiseError("BCSReader: cannot read 'row' element for tile");
                return false;
            }
        } else if (xml_.name() == "column") {
            column = readTileColumn(&ok);
            if (!ok) {
                xml_.raiseError("BCSReader: cannot read 'column' element for tile");
                return false;
            }
        } else if (xml_.name() == "material") {
            material = readTileMaterial(&ok);
            if (!ok) {
                xml_.raiseError("BCSReader: cannot read 'material' element for tile");
                return false;
            }
        } else {
            xml_.skipCurrentElement();
        }
    }

    if (!controller_->setTile(row, column, material)) {
        xml_.raiseError("BCSreader: row or column value is invalid");
        return false;
    }
    return true;
}

int BCSReader::readTileRow(bool *ok)
{
    if (!xml_.isStartElement() || xml_.name() != "row") {
        *ok = false;
        return -1;
    }

    return xml_.readElementText().toInt(ok);
}

int BCSReader::readTileColumn(bool *ok)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "column");
    if (!xml_.isStartElement() || xml_.name() != "column") {
        *ok = false;
        return  -1;
    }

    return xml_.readElementText().toInt(ok);
}

Tile::Material BCSReader::readTileMaterial(bool *ok)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "material");
    if (!xml_.isStartElement() || xml_.name() != "material") {
        *ok = false;
        return Tile::Free;
    }

    return static_cast<Tile::Material>(xml_.readElementText().toInt(ok));
}

bool BCSReader::readTank()
{
    static const QString errStr = "BCSReader: tank reading error";

    if (!xml_.isStartElement() || xml_.name() != "tank") {
        xml_.raiseError(errStr);
        return false;
    }

    ShootableItem *tank = new ShootableItem;
    if (tank == nullptr) {
        xml_.raiseError(errStr);
        return false;
    }
    tank->setProperty(Constants::Property::Belligerent, Constants::Belligerent::Enemy);

    bool ok = true;
    while (xml_.readNextStartElement()) {
        if (xml_.name() == Constants::EnemyTank::Property::Type) {
            QString type = readTankType(&ok);
            if (!ok) {
                xml_.raiseError("BCSreader: cannot read 'type' element for tank");
                delete tank;
                return false;
            }
            if (type == Constants::EnemyTank::Type::Usual) {
                tank->setImageSource("qrc:/images/tanks/enemy/simple_tank.png");
                tank->setProperty(Constants::EnemyTank::Property::Type,
                                  Constants::EnemyTank::Type::Usual);
            } else if (type == Constants::EnemyTank::Type::TroopCarrier) {
                tank->setImageSource("qrc:/images/tanks/enemy/fast.png");
                tank->setSpeed(6);
                tank->setProperty(Constants::EnemyTank::Property::Type,
                                  Constants::EnemyTank::Type::TroopCarrier);
            } else if (type == Constants::EnemyTank::Type::Bursting) {
                tank->setImageSource("qrc:/images/tanks/enemy/bursting.png");
                tank->setShotMode(ShootableItem::BurstShot);
                tank->setProperty(Constants::EnemyTank::Property::Type,
                                  Constants::EnemyTank::Type::Bursting);
            } else if (type == Constants::EnemyTank::Type::Armored) {
                tank->setImageSource("qrc:/images/tanks/enemy/armored.png");
                tank->setProperty(Constants::EnemyTank::Property::Type,
                                  Constants::EnemyTank::Type::Armored);
            } else {
                xml_.raiseError("BCSReader: invalid type of tank");
                delete tank;
                return false;
            }
        } else if (xml_.name() == Constants::EnemyTank::Property::Strength) {
            tank->setProperty(Constants::EnemyTank::Property::Strength, readTankStrength(&ok));
            if (!ok) {
                xml_.raiseError("BCSreader: cannot read 'strength' element for tank");
                delete tank;
                return false;
            }
        } else if (xml_.name() == Constants::EnemyTank::Property::Value) {
            tank->setProperty(Constants::EnemyTank::Property::Value, readTankValue(&ok));
            if (!ok) {
                xml_.raiseError("BCSreader: cannot read 'value' element for tank");
                delete tank;
                return false;
            }
        } else {
            xml_.skipCurrentElement();
        }
    }

    controller_->addEnemyTank(tank);
    return true;
}

QString BCSReader::readTankType(bool *ok)
{
    if (!xml_.isStartElement() || xml_.name() !="type") {
        *ok = false;
        return QString();
    }

    return xml_.readElementText();
}

int BCSReader::readTankStrength(bool *ok)
{
    if (!xml_.isStartElement() || xml_.name() != "strength") {
        *ok = false;
        return -1;
    }

    return xml_.readElementText().toInt(ok);
}

int BCSReader::readTankValue(bool *ok)
{
    if (!xml_.isStartElement() || xml_.name() != "value") {
        *ok = false;
        return -1;
    }

    return xml_.readElementText().toInt(ok);
}
