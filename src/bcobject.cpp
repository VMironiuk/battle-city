#include "bcobject.h"

BCObject::BCObject(QObject *parent)
    : QObject(parent)
{
}

BCObject::~BCObject()
{
}

void BCObject::setHasError(bool hasError)
{
    if (hasError_ == hasError)
        return;
    hasError_ = hasError;
    emit hasErrorChanged(hasError_);
}

void BCObject::setErrorString(const QString errorString)
{
    if (errorString_ == errorString)
        return;
    errorString_ = errorString;
    emit errorStringChanged(errorString_);
}
