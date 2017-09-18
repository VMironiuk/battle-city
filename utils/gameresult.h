#ifndef GAMERESULT_H
#define GAMERESULT_H

#include <QMap>

class GameResult
{
public:
    typedef int TankValue;
    typedef int TanksCount;

    GameResult();

    void accumulate(int TankValue);
    void appendPoints(int value);

private:
    QMap<TankValue, TanksCount> stageResults_;
    int totalTanks_ = 0;
    int totalPoints_ = 0;
};

#endif // GAMERESULT_H
