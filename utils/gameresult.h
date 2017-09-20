#ifndef GAMERESULT_H
#define GAMERESULT_H

#include <QMap>
#include <QObject>

namespace Utils {

class GameResult : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int totalPoints READ totalPoints CONSTANT)
public:
    typedef int TanksCount;

    enum TankValue {
        Usual = 100,
        TroopCarrier = 200,
        Bursting = 300,
        Armored = 400
    };
    Q_ENUMS(TankValue)

    GameResult();

    void accumulateEnemyTanks(int tankValue);
    void appendPointsForBonus(int value);

    Q_INVOKABLE void resetAll();
    Q_INVOKABLE int tankCount(TankValue tankValue) const;
    Q_INVOKABLE int tankPoints(TankValue tankValue) const;
    Q_INVOKABLE int totalTankCount() const;
    Q_INVOKABLE void resetStage();
    int totalPoints() const { return totalPoints_; }

private:
    QMap<TankValue, TanksCount> stageResults_;
    int totalPoints_ = 0;
};

}  // namespace Utils

#endif // GAMERESULT_H
