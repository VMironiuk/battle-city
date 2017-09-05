#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QSharedPointer>
#include <QColor>

#include "tile.h"

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
public:
    explicit Board(QObject *parent = nullptr);

    int width() const { return width_; }
    void setWidth(int width);

    int height() const { return height_; }
    void setHeight(int height);

    QSharedPointer<Tile> tile(int row, int column) const;

signals:
    void widthChanged(int width);
    void heightChanged(int height);

private slots:
    void fillTiles();

private:
    void initialize();

    int width_ = 0;
    int height_ = 0;
    QList<QSharedPointer<Tile>> tiles_;

    static const int SIZE;
};

#endif // BOARD_H
