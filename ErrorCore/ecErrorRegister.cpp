
#include "ErrorCore.h"
#include <QFile>
#include <QObject>
#include <QIODevice>
#include <QDataStream>
#include <QtGlobal>
#include <QSet>
#include <QDebug>
#include "ecErrorDialog.h"
#include "dialogKiller.h"

const QString ecErrorRegister::ErrorLogName = "Errors.log";
QSet<ecErrorDialog *> ecErrorRegister::errorSet = QSet<ecErrorDialog *>();

ecErrorDialog *ecErrorRegister::showError(ecError *e){
    QString errorString = e->message();

    qDebug() << errorString;


    ecErrorDialog *dialog = new ecErrorDialog(0, errorString);
    errorSet.insert(dialog);
    dialogKiller *killer = new dialogKiller(dialog, errorSet);
    QObject::connect(dialog, SIGNAL(closeButtonPressed()),
                     killer, SLOT(killDialog()));
    return dialog;
}

int ecErrorRegister::outstandingErrorCount() {
    return errorSet.count();
}


void dialogKiller::killDialog()
{
    source->setVisible(false);
    bool removed = dialogSet.remove(source);
    delete source;
    Q_ASSERT(removed);
    delete this;
} //ASSUMES THIS WAS ALLOCATED JUST FOR THIS
