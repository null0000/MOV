#ifndef DIALOGKILLER_H
#define DIALOGKILLER_H
//NOTE: Private hack class for ecErrorDialog.cpp. Reuse  at your own peril.
//Fucking QObject requirements.
#include <QObject>
#include <QSet>
class ecErrorDialog;


class dialogKiller : public QObject {
private:
    Q_OBJECT

private:
    ecErrorDialog *source;
    QSet<ecErrorDialog *>  &dialogSet;
public:
    dialogKiller(ecErrorDialog *dialog, QSet<ecErrorDialog *> &set) : source(dialog), dialogSet(set){}

    ~dialogKiller(){}

public slots:
    void killDialog();
};

#endif // DIALOGKILLER_H
