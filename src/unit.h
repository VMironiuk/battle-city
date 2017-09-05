#ifndef UNIT_H
#define UNIT_H

#include <QObject>

class Unit : public QObject
{
    Q_OBJECT
public:
    explicit Unit(QObject *parent = nullptr);

signals:

public slots:
};

#endif // UNIT_H