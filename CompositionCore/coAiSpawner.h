#ifndef COAISPAWNER_H
#define COAISPAWNER_H

#include "scSimulationStep.h"
#include <QString>
#include <QSharedPointer>


class gcRenderList;
typedef gcRenderList * gcRenderList_p;


class coAiSpawner : public scSimulationStep {
public:
    void runStep(scWorld &world, delta_t time);

    coAiSpawner(gcRenderList_p renderList, QString imageName,
                QSharedPointer<scWorld> worldPtr);

private:
    gcRenderList_p renderList;
    QString imageName;
    QSharedPointer<scWorld> worldPtr;

};

#endif // COAISPAWNER_H
