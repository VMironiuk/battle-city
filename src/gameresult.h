#ifndef GAMERESULT_H
#define GAMERESULT_H

#include <QMap>

class GameResult
{
    typedef int TankValue;
    typedef int TanksCount;
public:
    GameResult();

    void accumulate(int value);

private:
    QMap<TankValue, TanksCount> stageResults_;
    int totalTanks_ = 0;
    int totalPoints_ = 0;
};

#endif // GAMERESULT_H
