#include "delay.h"

Delay::Delay(QObject *parent)
    : QObject(parent)
{
}

void Delay::setup()
{
    expired_ = false;
    QTimer::singleShot(interval_, this, SLOT(reset()));
}

void Delay::setInterval(int interval)
{
    interval_ = interval;
}

void Delay::reset()
{
    expired_ = true;
}
