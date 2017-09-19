#include "stageiterator.h"

namespace Utils {

StageIterator *StageIterator::instance_ = nullptr;

QString StageIterator::nextStageSrc()
{
    StageIterator *obj = instance();
    int index = obj->curr_++ % obj->stages_.size();
    return obj->stages_[index];
}

void StageIterator::reset()
{
    instance()->curr_ = 0;
}

bool StageIterator::isValid()
{
    return !instance()->stages_.isEmpty();
}

StageIterator *StageIterator::instance()
{
    if (instance_ == nullptr)
        instance_ = new StageIterator;
    return instance_;
}

StageIterator::StageIterator()
{
    stages_ << ":/stages/stage1.xml";
    stages_ << ":/stages/stage2.xml";
}

}  // namespace Utils
