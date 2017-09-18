#ifndef BCOBJECT_H
#define BCOBJECT_H

#include <QObject>

class BCObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasError READ hasError WRITE setHasError NOTIFY hasErrorChanged)
    Q_PROPERTY(QString errorString READ errorString WRITE setErrorString NOTIFY errorStringChanged)
public:
    explicit BCObject(QObject *parent = nullptr);
    ~BCObject();

    bool hasError() const { return hasError_; }
    void setHasError(bool hasError);

    QString errorString() const { return errorString_; }
    void setErrorString(const QString errorString);

signals:
    void hasErrorChanged(bool hasError);
    void errorStringChanged(const QString &errorString);

private:
    bool hasError_ = false;
    QString errorString_;
};

#endif // BCOBJECT_H
