#ifndef ERRORCORE_H
#define ERRORCORE_H

#include <exception>
#include <QString>
#include <QDataStream>
#include <map>
#include <vector>

class ecErrorDialog;

class ecError : public std::exception
{
public:

    virtual QString message() const = 0;
    ecError(){}
    virtual ~ecError() throw() {}
};


class ecErrorRegister {
public:
    static ecErrorDialog *showError(ecError *e);

    static QDataStream *debugStreamRead();
    static QDataStream *debugStreamWrite();

    static int outstandingErrorCount();

private:
    static void openDebugFileRead();
    static void openDebugFileWrite();


    static QSet<ecErrorDialog *> errorSet;
    static const QString ErrorLogName;
};

#endif // ERRORCORE_H
