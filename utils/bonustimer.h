#ifndef BONUSTIMER_H
#define BONUSTIMER_H

#include <QObject>

namespace Utils {

class BonusTimer : public QObject
{
    Q_OBJECT
public:
    explicit BonusTimer(QObject *parent = nullptr);

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

}  // namespace Utils

#endif // BONUSTIMER_H
