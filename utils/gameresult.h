#ifndef GAMERESULT_H
#define GAMERESULT_H

#include <QMap>

namespace Utils {

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

}  // namespace Utils

#endif // GAMERESULT_H
