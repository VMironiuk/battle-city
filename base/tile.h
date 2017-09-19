#ifndef TILE_H
#define TILE_H

#include "baseitem.h"

namespace Base {

class Tile : public BaseItem
{
    Q_OBJECT
public:
    enum Material {
        Free = 0x2,
        Bricks = 0x4,
        Concrete = 0x8,
        Bush = 0x10,
        Ice = 0x20,
        Water = 0x40
    };

    explicit Tile(QObject *parent = nullptr);

    bool isTankTraversable() const;
    bool isProjectileTraversable() const;
    bool isProjectileBreakable() const;

    Material material() const { return material_; }
    void setMaterial(Material material);

signals:
    void materialChanged(Material material);

private:
    void updateImageSource(Material material);

    Material material_ = Free;
};

}  // namespace Base

#endif // TILE_H
