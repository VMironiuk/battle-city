#ifndef TILE_H
#define TILE_H

#include "baseitem.h"

class Tile : public BaseItem
{
    Q_OBJECT
public:
    enum Material {
        Free,
        Bricks,
        Concrete,
        Bush,
        Ice,
        Water
    };

    explicit Tile(QObject *parent = nullptr);

    bool isTankTraversable() const;
    bool isBombTraversable() const;
    bool isBombBreakable() const;

    Material material() const { return material_; }
    void setMaterial(Material material);

signals:
    void materialChanged(Material material);

private:
    void updateImageSource(Material material);

    Material material_ = Free;
};

#endif // TILE_H
