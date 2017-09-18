#ifndef BCOBJECT_H
#define BCOBJECT_H

#include <QObject>

class BCObject : public QObject
{
    Q_OBJECT
public:
    explicit BCObject(QObject *parent = nullptr);
    ~BCObject();

    bool hasError() const { return hasError_; }
    void setHasError(bool hasError) { hasError_ = hasError; }

    QString errorString() const { return errorString_; }
    void setErrorString(const QString errorString) { errorString_ = errorString; }

private:
    bool hasError_ = false;
    QString errorString_;
};

#endif // BCOBJECT_H
