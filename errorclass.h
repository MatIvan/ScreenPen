#ifndef ERRORCLASS_H
#define ERRORCLASS_H

#include <QObject>
//#include "error.h"

#define NO_error false
#define IS_error true

class ErrorClass : public QObject
{
    Q_OBJECT
public:
    explicit ErrorClass(QObject *parent = nullptr);
    virtual ~ErrorClass();

    bool ReturnResult(bool is_Error, const QString &Error_String = "-" );
    bool isError() const;
    QString lastError() const;

private:
    bool is_error;
    QString last_error_string;

signals:
    void er_SignalError();

public slots:
};

#endif // ERRORCLASS_H
