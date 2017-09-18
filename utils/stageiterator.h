#ifndef STAGEITERATOR_H
#define STAGEITERATOR_H

#include <QList>

class StageIterator
{
public:
    static QString nextStageSrc();
    static void reset();
    static bool isValid();

private:
    static StageIterator *instance();
    StageIterator();

    static StageIterator *instance_;
    QList<QString> stages_;
    int curr_ = 0;
};

#endif // STAGEITERATOR_H
