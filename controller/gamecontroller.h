#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "bcobject.h"
#include "board.h"
#include "bonustimer.h"
#include "collider.h"
#include "enemydriver.h"
#include "gameresult.h"
#include "informationpanel.h"

namespace Controller {

class GameController : public Base::BCObject
{
    Q_OBJECT
    Q_PROPERTY(bool won READ won WRITE setWon NOTIFY wonChanged)
public:
    static GameController &instance();
    GameController(const GameController&) = delete;
    GameController &operator=(const GameController&) = delete;

    Base::Board *board() { return board_; }
    Base::InformationPanel *informationPanel() { return informationPanel_; }

    bool won() const { return won_; }
    void setWon(bool won);

    Q_INVOKABLE bool setupStage();
    Q_INVOKABLE void startStage();
    Q_INVOKABLE void stopStage();
    Q_INVOKABLE void freeStage();

signals:
    void stageFinished();
    void wonChanged(bool won);

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void removeEnemyDriver();
    void admitDefeat();
    void onPlayerTankDestroyed();
    void onEnemyTankDestroyed(int tankValue);
    void onShowBonusRequest();
    void onHideBonusRequest();
    void onBonusReached(Base::ShootableItem *playerTank,
                        Base::Constants::Bonus::BonusType bonusType);

private:
    explicit GameController(QObject *parent = nullptr);
    ~GameController();

    bool check();
    void checkCollisions();
    void checkStageFinished();
    void updateEnemyDrivers();
    void setupRespawns();
    void setupPlayerTank();
    void moveEnemyTankToBoard();
    void improvePlayerTank(Base::ShootableItem *tank);

    Base::Board *board_;
    Base::InformationPanel *informationPanel_;
    Utils::Collider collider_;
    QPair<int, int> playerRespawn_;
    QList<QPair<int, int>> enemyRespawns_;
    QList<EnemyDriver *> enemyDrivers_;
    int gameRythmId_;
    int enemyTankAppearRythmId_;
    int enemyDriverRythmId_;
    Utils::GameResult gameResult_;
    Utils::BonusTimer bonusTimer_;
    bool won_;
};

}  // namespace Controller

#endif // GAMECONTROLLER_H
