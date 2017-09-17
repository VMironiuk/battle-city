#include "bonustimer.h"

#include <QTimerEvent>

static const int SHOW_INTERVAL = 30000;
static const int HIDE_INTERVAL = 15000;

BonusTimer::BonusTimer(QObject *parent)
    : QObject(parent)
{
    intervalId_ = startTimer(SHOW_INTERVAL);
}

void BonusTimer::reset()
{
    bonusShown_ = false;
    killTimer(intervalId_);
    intervalId_ = startTimer(SHOW_INTERVAL);
}

void BonusTimer::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == intervalId_) {
        if (!bonusShown_) {
            emit showBonusRequest();
            killTimer(intervalId_);
            intervalId_ = startTimer(HIDE_INTERVAL);
        } else {
            emit hideBonusRequest();
            killTimer(intervalId_);
            intervalId_ = startTimer(SHOW_INTERVAL);
        }
        bonusShown_ = !bonusShown_;
    }
}
