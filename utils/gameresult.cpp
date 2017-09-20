#include "gameresult.h"

#include "global.h"

#include <QDebug>

namespace Utils {

GameResult::GameResult()
{
    resetStage();
}

void GameResult::accumulateEnemyTanks(int tankValue)
{
    if (!stageResults_.contains(static_cast<TankValue>(tankValue))) {
        qDebug() << "invalid tank value";
        return;
    }

    ++stageResults_[static_cast<TankValue>(tankValue)];
    totalPoints_ += tankValue;
}

void GameResult::appendPointsForBonus(int value)
{
    totalPoints_ += value;
}

void GameResult::resetAll()
{
    totalPoints_ = 0;
}

int GameResult::tankCount(TankValue tankValue) const
{
    return stageResults_.value(tankValue, -1);
}

int GameResult::tankPoints(TankValue tankValue) const
{
    auto it = stageResults_.find(tankValue);
    if (it == stageResults_.end())
        return -1;

    return tankCount(tankValue) * static_cast<int>(it.key());
}

int GameResult::totalTankCount() const
{
    auto b = stageResults_.constBegin();
    auto e = stageResults_.constEnd();
    int total = 0;
    for (; b != e; ++b)
        total += b.value();
    return total;
}

void GameResult::resetStage()
{
    stageResults_[Usual] = 0;
    stageResults_[TroopCarrier] = 0;
    stageResults_[Bursting] = 0;
    stageResults_[Armored] = 0;
}

}  // namespace Utils
