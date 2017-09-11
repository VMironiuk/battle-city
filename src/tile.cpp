#include "tile.h"

Tile::Tile(QObject *parent) : BaseItem(parent)
{

}

bool Tile::isTankTraversable() const
{
    // TODO: handle ice for tank
    return material_ & (Free | Bush);
}

bool Tile::isProjectileTraversable() const
{
    return material_ & (Free | Bush | Ice | Water);
}

bool Tile::isProjectileBreakable() const
{
    // TODO: handle concrete for three stars tank's bomb
    return material_ & Bricks;
}

void Tile::setMaterial(Material material)
{
    if (material_ == material)
        return;
    material_ = material;
    updateImageSource(material_);
    emit materialChanged(material_);
}

void Tile::updateImageSource(Material material)
{
    switch (material) {
    case Bricks:
        setImageSource("qrc:/images/obstacles/bricks.png");
        break;
    case Concrete:
        setImageSource("qrc:/images/obstacles/concrete.png");
        break;
        // TODO: add image source below
    case Bush:
    case Ice:
    case Water:
        // fall down
    case Free:
    default:
        setImageSource("");
    }
}
