#ifndef COAISPAWNER_H
#define COAISPAWNER_H


#include "coWorld.h"

#include <scSimulationStep.h>


#include <QString>
#include <QSharedPointer>
class gcRenderList;
typedef QSharedPointer<gcRenderList> gcRenderList_p;


class coAiSpawner : public scSimulationStep {
public:
    void runStep(scWorld &world, delta_t time);

    coAiSpawner(QString imageName, coWorld_p world);

private:
    QString imageName;
    QSharedPointer<scWorld> worldPtr;
    coWorld_p world;

};

#endif // COAISPAWNER_H
