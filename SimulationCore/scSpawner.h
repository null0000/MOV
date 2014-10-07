#ifndef SCSPAWNER_H
#define SCSPAWNER_H

#include <QSharedPointer>

#include "simulationcore_ie.h"

class scSpawner {
public:
    virtual void spawnAI(QVector2D loc) = 0;
    virtual ~scSpawner(){}

};

typedef QSharedPointer<scSpawner> scSpawner_p;

#endif // SCSPAWNER_H
