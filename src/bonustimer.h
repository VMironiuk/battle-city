#ifndef BONUSTIMER_H
#define BONUSTIMER_H

#include <QObject>

class BonusTimer : public QObject
{
    Q_OBJECT
public:
    BonusTimer(QObject *parent = nullptr);

    void reset();

signals:
    void showBonusRequest();
    void hideBonusRequest();

protected:
    void timerEvent(QTimerEvent *event);

private:
    int intervalId_ = 0;
    bool bonusShown_ = false;
};

#endif // BONUSTIMER_H