#include "errorclass.h"

ErrorClass::ErrorClass(QObject *parent) : QObject(parent)
{

}

ErrorClass::~ErrorClass()
{

}

bool ErrorClass::ReturnResult(bool is_Error, const QString &Error_String )
{
    last_error_string = Error_String;
    is_error = is_Error;
    if ( isError() ) emit er_SignalError();

    return !isError();
}

bool ErrorClass::isError() const
{
    return is_error;
}

QString ErrorClass::lastError() const
{
    return last_error_string;
}
