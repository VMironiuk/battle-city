#include "gameresult.h"

#include "global.h"

namespace Utils {

GameResult::GameResult()
{
    stageResults_[Base::Constants::EnemyTank::Value::Usual] = 0;
    stageResults_[Base::Constants::EnemyTank::Value::TroopCarrier] = 0;
    stageResults_[Base::Constants::EnemyTank::Value::Bursting] = 0;
    stageResults_[Base::Constants::EnemyTank::Value::Armored] = 0;
}

void GameResult::accumulate(int TankValue)
{
    ++stageResults_[TankValue];
    ++totalTanks_;
    totalPoints_ += TankValue;
}

void GameResult::appendPoints(int value)
{
    totalPoints_ += value;
}

}  // namespace Utils
