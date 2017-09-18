#include "gameresult.h"

#include <QDebug>

#include "global.h"

GameResult::GameResult()
{
    stageResults_[Constants::EnemyTank::Value::Usual] = 0;
    stageResults_[Constants::EnemyTank::Value::TroopCarrier] = 0;
    stageResults_[Constants::EnemyTank::Value::Bursting] = 0;
    stageResults_[Constants::EnemyTank::Value::Armored] = 0;
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
