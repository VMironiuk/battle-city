#ifndef INFORMATIONPANEL_H
#define INFORMATIONPANEL_H

#include <QQmlListProperty>

#include "baseitem.h"

class InformationPanel : public BaseItem
{
    Q_OBJECT
    Q_PROPERTY(int stageNo READ stageNo WRITE setStageNo NOTIFY stageNoChanged)
    Q_PROPERTY(int livesCount READ livesCount WRITE setLivesCount NOTIFY livesCountChanged)
    Q_PROPERTY(int maxEnemiesCount READ maxEnemiesCount WRITE setMaxEnemiesCount NOTIFY maxEnemiesCountChanged)
    Q_PROPERTY(QQmlListProperty<BaseItem> enemyMarkersProperty READ enemyMarkersProperty NOTIFY enemyMarkersPropertyChanged)
public:
    explicit InformationPanel(QObject *parent = nullptr);
    ~InformationPanel();

    int stageNo() const { return stageNo_; }
    void setStageNo(int stageNo);

    int livesCount() const { return livesCount_; }
    void setLivesCount(int livesCount);

    int maxEnemiesCount() const { return maxEnemiesCount_; }
    void setMaxEnemiesCount(int maxEnemiesCount);

    QQmlListProperty<BaseItem> enemyMarkersProperty();

signals:
    void stageNoChanged(int stageNo);
    void livesCountChanged(int livesCount);
    void maxEnemiesCountChanged(int maxEnemiesCount);
    void enemyMarkersPropertyChanged(QQmlListProperty<BaseItem>);

private:
    void removeEnemyMarker();

    int stageNo_ = 1;
    int livesCount_ = 2;
    int maxEnemiesCount_ = 0;
    QList<BaseItem *> enemyMarkers_;
};

#endif // INFORMATIONPANEL_H
