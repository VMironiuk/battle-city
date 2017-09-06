#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QSharedPointer>
#include <QColor>
#include <QQmlListProperty>

#include "tile.h"

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QQmlListProperty<Tile> tiles READ tiles CONSTANT)
public:
    explicit Board(QObject *parent = nullptr);
    ~Board();

    qreal width() const { return width_; }
    void setWidth(qreal width);

    qreal height() const { return height_; }
    void setHeight(qreal height);

    Tile *tile(int row, int column) const;
    QQmlListProperty<Tile> tiles();

signals:
    void widthChanged(int width);
    void heightChanged(int height);

private slots:
    void updateTiles();
    void makeMaze();

private:
    void initialize();
    void fillTiles();

    qreal width_ = 0;
    qreal height_ = 0;
    QList<Tile *> tiles_;

    static const int SIZE;
};

#endif // BOARD_H
