#include "informationpanel.h"

InformationPanel::InformationPanel(QObject *parent)
    : BaseItem(parent)
{
}

InformationPanel::~InformationPanel()
{
    qDeleteAll(enemyMarkers_);
    qDeleteAll(tanks_);
}

void InformationPanel::clear()
{
    removeAllEnemyMarkers();

    qDeleteAll(tanks_);
    tanks_.clear();

    setLivesCount(2);
}

void InformationPanel::setStageNo(int stageNo)
{
    if (stageNo_ == stageNo)
        return;
    stageNo_ = stageNo;
    emit stageNoChanged(stageNo_);
}

void InformationPanel::setLivesCount(int livesCount)
{
    if (livesCount_ == livesCount)
        return;
    livesCount_ = livesCount;
    emit livesCountChanged(livesCount_);
}

void InformationPanel::setMaxEnemiesCount(int maxEnemiesCount)
{
    if (maxEnemiesCount_ == maxEnemiesCount)
        return;
    maxEnemiesCount_ = maxEnemiesCount;
    emit maxEnemiesCountChanged(maxEnemiesCount_);
}

bool InformationPanel::hasNextTank() const
{
    return !tanks_.isEmpty();
}

ShootableItem *InformationPanel::nextTank()
{
    if (tanks_.isEmpty())
        return nullptr;
    removeEnemyMarker();
    return tanks_.dequeue();
}

void InformationPanel::addTank(ShootableItem *tank)
{
    tanks_.enqueue(tank);
    createEnemyMarker();
}

QQmlListProperty<BaseItem> InformationPanel::enemyMarkersProperty()
{
    return QQmlListProperty<BaseItem>(this, enemyMarkers_);
}

void InformationPanel::createEnemyMarker()
{
    BaseItem *marker = new BaseItem;
    marker->setImageSource("qrc:/images/control_panel/enemy_marker.png");
    enemyMarkers_ << marker;
    maxEnemiesCount_ = enemyMarkers_.count();
    emit enemyMarkersPropertyChanged(enemyMarkersProperty());
}

void InformationPanel::removeEnemyMarker()
{
    if (enemyMarkers_.isEmpty())
        return;

    BaseItem *marker = enemyMarkers_.last();
    enemyMarkers_.removeLast();
    emit enemyMarkersPropertyChanged(enemyMarkersProperty());
    delete marker;
}

void InformationPanel::removeAllEnemyMarkers()
{
    while (!enemyMarkers_.isEmpty())
        removeEnemyMarker();
}
