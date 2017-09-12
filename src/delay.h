#ifndef DELAY_H
#define DELAY_H

#include <QObject>
#include <QTimer>

class Delay : public QObject
{
    Q_OBJECT
public:
    Delay(QObject *parent = nullptr);

    bool isExpired() const { return expired_; }
    void setup();
    void setInterval(int interval);

private slots:
    void reset();

private:
    bool expired_ = true;
    int interval_ = 1500;
};

#endif // DELAY_H
